#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <stack>

#include "lang.h"
#include "transform.h"

namespace conless {
std::map<std::string, std::string> funcNameMap;
std::stack<std::map<std::string, std::string>> varNameMap;
std::set<std::string> buildInNameMap;
std::map<std::string, std::pair<std::vector<Variable *>, CallExpression *>> newFuncMap;

std::string randomFunction() {
  static int cntStr[8] = {0};
  for (int i = 7; i >= 0; i--) {
    cntStr[i]++;
    if (cntStr[i] == 26) {
      cntStr[i] = 0;
    } else {
      break;
    }
  }
  char str[8];
  for (int i = 0; i < 8; i++) {
    str[i] = cntStr[i] + 'A';
  }
  return "Function" + std::string(str);
}
std::string randomVariable() {
  static int cntStr[8] = {0};
  for (int i = 7; i >= 0; i--) {
    cntStr[i]++;
    if (cntStr[i] == 26) {
      cntStr[i] = 0;
    } else {
      break;
    }
  }
  char str[8];
  for (int i = 0; i < 8; i++) {
    str[i] = cntStr[i] + 'A';
  }
  return "Variable" + std::string(str);
}
FunctionDeclaration *builtInFunction(std::string name) {
  std::string funcName = "Function" + name;
  std::vector<Variable *> params;
  Statement *stmt;

  funcNameMap[name] = funcName;
  buildInNameMap.insert(funcName);
  params.push_back(new Variable("VariableA"));
  params.push_back(new Variable("VariableB"));
  Variable *result = new Variable("VariableC");
  stmt = new BlockStatement(
      {new SetStatement(result, new CallExpression(name, {params[0], params[1]})), new ReturnStatement(result)});
  return new FunctionDeclaration(funcName, params, stmt);
}

}  // namespace conless

class Cheat : public Transform {
 public:
  Program *transformProgram(Program *node) override {
    std::vector<FunctionDeclaration *> body;
    {
      body.push_back(transformFunctionDeclaration(new FunctionDeclaration("+", {}, nullptr)));
      body.push_back(transformFunctionDeclaration(new FunctionDeclaration("-", {}, nullptr)));
      body.push_back(transformFunctionDeclaration(new FunctionDeclaration("*", {}, nullptr)));
      body.push_back(transformFunctionDeclaration(new FunctionDeclaration("/", {}, nullptr)));
      body.push_back(transformFunctionDeclaration(new FunctionDeclaration("%", {}, nullptr)));
      body.push_back(transformFunctionDeclaration(new FunctionDeclaration("<", {}, nullptr)));
      body.push_back(transformFunctionDeclaration(new FunctionDeclaration(">", {}, nullptr)));
      body.push_back(transformFunctionDeclaration(new FunctionDeclaration("<=", {}, nullptr)));
      body.push_back(transformFunctionDeclaration(new FunctionDeclaration(">=", {}, nullptr)));
      body.push_back(transformFunctionDeclaration(new FunctionDeclaration("==", {}, nullptr)));
      body.push_back(transformFunctionDeclaration(new FunctionDeclaration("!=", {}, nullptr)));
      body.push_back(transformFunctionDeclaration(new FunctionDeclaration("||", {}, nullptr)));
      body.push_back(transformFunctionDeclaration(new FunctionDeclaration("&&", {}, nullptr)));
    }

    conless::varNameMap.push({});
    for (auto decl : node->body) {
      body.push_back(transformFunctionDeclaration(decl));
    }
    conless::varNameMap.pop();
    return new Program(body);
  }

  FunctionDeclaration *transformFunctionDeclaration(FunctionDeclaration *node) override {
    if (node->body == nullptr) {
      return conless::builtInFunction(node->name);
    }

    std::string funcName;
    std::vector<Variable *> params;
    Statement *stmt;

    if (node->name == "main") {
      funcName = node->name;
    } else {
      funcName = conless::randomFunction();
    }
    conless::funcNameMap[node->name] = funcName;

    for (auto param : node->params) {
      params.push_back(transformVariable(param));
    }

    stmt = transformStatement(node->body);

    return new FunctionDeclaration(funcName, params, stmt);
  }

  void getAllParams(CallExpression *node, std::map<std::string, bool> &result) {
  for (auto arg : node->args) {
    if (arg->is<Variable>()) {
      arg = transformVariable(arg->as<Variable>());
      result.insert({arg->as<Variable>()->name, true});
    } else if (arg->is<CallExpression>()) {
      getAllParams(arg->as<CallExpression>(), result);
    }
  }
  }
  Statement *transformSetStatement(SetStatement *node) override {
    std::map<std::string, bool> result;
    node->name = transformVariable(node->name);
    result.insert({node->name->name + "Array", true});
    if (node->value->is<CallExpression>()) {
      std::string callFuncName = node->value->as<CallExpression>()->func;
      if (callFuncName.size() > 5 && callFuncName.substr(0, 5) == "array") {
        return new SetStatement(transformVariable(node->name), transformExpression(node->value));
      }
      getAllParams(node->value->as<CallExpression>(), result);
    }
    std::vector<Variable *> args;
    std::vector<Expression *> params;
    for (auto kv : result) {
      args.push_back(new Variable(kv.first));
      params.push_back(new Variable(kv.first));
    }
    std::string funcName = conless::randomFunction();
    auto arrayGetExpr = new CallExpression("array.set", {new Variable(node->name->name + "Array"), new IntegerLiteral(0), node->value});
    conless::newFuncMap.insert({funcName, {args, arrayGetExpr}});
    return new BlockStatement({
        new SetStatement(new Variable(node->name->name + "Array"),
                         new CallExpression("array.create", {new IntegerLiteral(1)})),
        new ExpressionStatement(new CallExpression(funcName, params)),
        new SetStatement(new Variable(node->name->name), new CallExpression("array.get", {new Variable(node->name->name + "Array"), new IntegerLiteral(0)}))
    });
  }

  Statement *transformBlockStatement(BlockStatement *node) override {
    std::vector<Statement *> body;
    auto nextLayer = conless::varNameMap.top();
    conless::varNameMap.push(nextLayer);
    for (auto stmt : node->body) {
      std::cout << "Visiting: " << stmt->toString() << '\n';
      if (stmt->is<SetStatement>()) {
        auto returnStmt = transformSetStatement(stmt->as<SetStatement>());
        if (returnStmt->is<BlockStatement>()) {
          for (auto blockedStmt : returnStmt->as<BlockStatement>()->body) {
            body.push_back(blockedStmt);
            // std::cout << blockedStmt->toString() << '\n';
          }
          continue;
        }
      }
      body.push_back(transformStatement(stmt));
    }
    conless::varNameMap.pop();
    return new BlockStatement(body);
  }

  Variable *transformVariable(Variable *node) override {
    if (conless::varNameMap.top().find(node->name) != conless::varNameMap.top().end()) {
      return new Variable(conless::varNameMap.top()[node->name]);
    }
    std::string varName = conless::randomVariable();
    conless::varNameMap.top()[node->name] = varName;
    return new Variable(varName);
  }
};

class Fix : public Transform {
 public:
  Program *transformProgram(Program *node) override {
    std::vector<FunctionDeclaration *> body;
    for (auto decl : node->body) {
      body.push_back(transformFunctionDeclaration(decl));
    }
    for (auto newFunc : conless::newFuncMap) {
      body.push_back(new FunctionDeclaration(newFunc.first, newFunc.second.first, new ExpressionStatement(newFunc.second.second)));
    }
    return new Program(body);
  }
  FunctionDeclaration *transformFunctionDeclaration(FunctionDeclaration *node) override {
    if (conless::buildInNameMap.find(node->name) != conless::buildInNameMap.end()) {
      return node;
    }
    std::vector<Variable *> params;
    for (auto param : node->params) {
      params.push_back(transformVariable(param));
    }
    return new FunctionDeclaration(node->name, params, transformStatement(node->body));
  }
  Expression *transformCallExpression(CallExpression *node) override {
    std::vector<Expression *> args;
    for (auto arg : node->args) {
      args.push_back(transformExpression(arg));
    }
    std::string funcName;
    if (conless::funcNameMap.find(node->func) == conless::funcNameMap.end()) {
      funcName = node->func;
    } else {
      funcName = conless::funcNameMap[node->func];
    }
    return new CallExpression(funcName, args);
  }
};

int main() {
  time_t t;
  srand(time(&t));
  auto code = scanProgram(std::cin);
  auto cheat = Cheat().transformProgram(code);
  // printf("\n\n\n\n\n\n\n\n\n\n");
  auto program = Fix().transformProgram(cheat);
  std::cout << program->toString();
  return 0;
}
