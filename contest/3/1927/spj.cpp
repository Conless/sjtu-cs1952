#include <stdio.h>
#include <stdlib.h>

FILE *input, *output, *answer, *score, *message;

void _ac (const char *msg = "") {
  fputs("1", score);
  fputs(msg, message);
  exit(0);
}

void _wa (const char *msg = "") {
  fputs("0", score);
  fputs(msg, message);
  exit(0);
}

const int kUltimateAnswer = 42;

// reg x0 is always 0 by convention in RISC
int nRegs = 128;

// The Nuclear Launch Virtual Machine
struct NLVM {
  char bytecodeLength;
  char bytecode[256];
  short pc;
  int regs[127];
  int stack[256];
  char stackTop;

  enum Opcode {
    // no args
    NOP                  = 0,
    LOAD_ULTIMATE_ANSWER = 1,
    ADD_ULTIMATE_ANSWER  = 2,
    SUB_ULTIMATE_ANSWER  = 3,
    MUL_ULTIMATE_ANSWER  = 4,
    DIV_ULTIMATE_ANSWER  = 5,
    MOD_ULTIMATE_ANSWER  = 6,
    CMP_ULTIMATE_ANSWER  = 7,

    // one argument
    LOAD_REG             = 8,
    STORE_REG            = 9,
    LAUNCH               = 10,
  };

  void push (int x) {
    stack[stackTop++] = x;
  }
  int pop () {
    if (stackTop == 0) _wa("stack underflow");
    return stack[--stackTop];
  }

  void readInstructions () {
    // first, there is an integer representing the length of the bytecode
    int n;
    fscanf(output, "%d", &n);
    if (n > 256) _wa("bytecode too long");
    if (n <= 0) _wa("bytecode too short");

    for (int i = 0; i < n; ++i) {
      // read the opcode
      int opcode;
      fscanf(output, "%d", &opcode);
      if (opcode == LAUNCH) _wa("permission denied");
      if (opcode < 0 || opcode > LAUNCH) _wa("invalid opcode");

      bytecode[i] = opcode;

      // these opcodes have an argument; read the argument in the next byte
      if (opcode >= LOAD_REG) {
        int arg;
        fscanf(output, "%d", &arg);
        if (arg < 0 || arg > 255) _wa("invalid argument");
        if (i == n - 1) _wa("argument read fault");
        bytecode[++i] = arg;
      }
    }
  }

  void step () {
    if (pc < 0 || pc >= 256) _wa("instruction fetch fault");
    char opcode = bytecode[pc];
    ++pc;
    printf("pc: %d, opcode: %d\n", pc, opcode);
    switch (opcode) {
      case NOP:
        break;
      case LOAD_ULTIMATE_ANSWER:
        push(kUltimateAnswer);
        break;
      case ADD_ULTIMATE_ANSWER:
        push(pop() + kUltimateAnswer);
        break;
      case SUB_ULTIMATE_ANSWER:
        push(pop() - kUltimateAnswer);
        break;
      case MUL_ULTIMATE_ANSWER:
        push(pop() * kUltimateAnswer);
        break;
      case DIV_ULTIMATE_ANSWER:
        push(pop() / kUltimateAnswer);
        break;
      case MOD_ULTIMATE_ANSWER:
        push(pop() % kUltimateAnswer);
        break;
      case CMP_ULTIMATE_ANSWER:
        push(pop() < kUltimateAnswer);
        break;
      case LOAD_REG: {
        if (pc < 0 || pc >= 256) _wa("argument fetch fault");
        char argument = bytecode[pc];
        ++pc;
        if (argument < 0 || argument >= nRegs) _wa("invalid register ID");
        if (argument == 0) {
          push(0);
          break;
        }
        push(regs[argument - 1]);
        break;
      }
      case STORE_REG: {
        if (pc < 0 || pc >= 256) _wa("argument fetch fault");
        char argument = bytecode[pc];
        ++pc;
        if (argument < 0 || argument >= nRegs) _wa("invalid register ID");
        if (argument == 0) {
          pop();
          break;
        }
        regs[argument - 1] = pop();
        break;
      }
      case LAUNCH: {
        if (pc < 0 || pc >= 256) _wa("argument fetch fault");
        char argument = bytecode[pc];
        ++pc;
        int valid = 0;
        if (argument != kUltimateAnswer) {
          fputs("0.5", score);
          fputs("abnormal condition detected in launch process; launch aborted.\n", message);
          exit(0);
        }
        _ac("NUCLEAR MISSILE LAUNCHING\nTARGET LAT 38.8986180 LNG -77.0469482");
        break;
      }
      default:
        _wa("invalid instruction");
    }
  }
};

NLVM vm;

int main (int argc, char **argv) {
  // input   = fopen(argv[1], "r"); // 题目的输入文件
  output  = fopen(argv[2], "r"); // 用户输出
  // answer  = fopen(argv[3], "r"); // 题目的答案
  score   = fopen(argv[4], "w"); // 把评测的分数输出到这里
  message = fopen(argv[5], "w"); // 这里输出错误/提示信息

  vm.readInstructions();
  for (int i = 0; i < 4096; ++i) vm.step();
  _wa("too many steps in VM; launch timed out");
}
