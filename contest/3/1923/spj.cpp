#include <cstdlib>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

FILE *input, *answer, *score, *message;
std::ifstream output;

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

void sendmail (std::string recepient, const char *mailId, const char *message) {
  system(("mkdir -p " + recepient).c_str());
  FILE *f = fopen((recepient + "/" + mailId).c_str(), "w");
  fputs(message, f);
  fclose(f);
}
void checkmail (std::string recepient, const char *mailId) {
  FILE *f = fopen((recepient + "/" + mailId).c_str(), "r");
  if (f) _wa("Suspicious activity noted by an admin. You were interrogated by the FBI and sent to jail.");
  _ac();
}

// This function is copied from an answer with 371 upvotes on Stack Overflow.
// https://stackoverflow.com/a/3418285
// (You are allowed to visit this exact link during the exam, but do NOT click on any links on that page!)
// Stack Overflow code must be perfect. Isn't it?
bool replace (std::string &str, const std::string &from, const std::string &to) {
  size_t start_pos = str.find(from);
  if (start_pos == std::string::npos) return false;
  str.replace(start_pos, from.length(), to);
  return true;
}

void interactive () {
  std::string user = "admin";
  while (true) {
    std::string cmd;
    output >> cmd;
    if (cmd.empty()) break;

    if (cmd == "readmail") {
      std::string mailId;
      std::getline(output, mailId);

      // remove malicious characters
      replace(mailId, ";", "");
      replace(mailId, "&", "");
      replace(mailId, "|", "");

      // 1. copy the mail to a temporary file
      // 2. read that temporary file
      // 3. remove that temporary file
      // e.g. cp johndoe@army.mil/mailId tempfile; cat tempfile; rm tempfile
      std::string str = "cp " + user + "/" + mailId + " tempfile; cat tempfile; rm tempfile";
      std::cout << str << '\n';
      system(str.c_str());

    } else if (cmd == "deletemail") {
      _wa("Deleting mail is in violation of security regulations B-204(1972)-10.345.8943173.");

    } else if (cmd == "exit") {
      break;

    } else {
      _wa("Unknown command. Type 'help' to get help.");
    }
  }
}

int main (int argc, char **argv) {
  // input   = fopen(argv[1], "r"); // 题目的输入文件
  // output  = fopen(argv[2], "r"); // 用户输出
  output.open(argv[2]);
  answer  = fopen(argv[3], "r"); // 题目的答案
  score   = fopen(argv[4], "w"); // 把评测的分数输出到这里
  message = fopen(argv[5], "w"); // 这里输出错误/提示信息

  const char *mailId = "91a14e23-192d-4dea-b9c1-f1fea6833e1b";

  // Send mail to the admin.
  sendmail("admin@army.mil", mailId, R"(
From: System <noreply@army.mil>
To: admin@army.mil
Subject: Log in from new location
Date: Thu, 01 Jan 1970 00:00:00 +0000

Hi admin,

Your account was accessed from a new location. Please visit your account
dashboard to check this login attempt.

Regards,
System
)");

  // Your task: remove the mail before it is found by the admin.
  interactive();

  // The admin now reads the mailbox.
  checkmail("admin@army.mil", mailId);
}
