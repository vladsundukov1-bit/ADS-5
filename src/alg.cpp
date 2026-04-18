// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

using std::string;

int getPriority(char opr) {
  if (opr == '+' || opr == '-')
  return 1;
  if (opr == '*' || opr == '/')
  return 2;
  return 0;
}

bool isOperator(char d) {
  return d == '+' || d == '-' || d == '*' || d == '/';
}

int doOperation(int a, int b, char opr) {
  if (opr == '+') return a + b;
  if (opr == '-') return a - b;
  if (opr == '*') return a * b;
  if (opr == '/') return a / b;
  return 0;
}

string infx2pstfx(const string& inf) {
  TStack<char, 100> stack;
  string result;
  for (int i = 0; i < inf.length(); i++) {
    char d = inf[i];
    if (isdigit(d)) {
      while (i < inf.length() && isdigit(inf[i])) {
        result += inf[i];
        i++;
      }
      result += ' ';
      i--;
    } else if (d == '(') {
      stack.push(d);
    } else if (d == ')') {
      while (!stack.is_empty() && stack.top() != '(') {
        result += stack.pop();
        result += ' ';
      }
      if (!stack.is_empty() && stack.top() == '(') {
        stack.pop();
      }
    } else if (isOperator(d)) {
      while (!stack.is_empty() && stack.top() != '(' &&
        getPriority(stack.top()) >= getPriority(d)) {
        result += stack.pop();
        result += ' ';
      }
      stack.push(d);
    }
  }
  while (!stack.is_empty()) {
    result += stack.pop();
    result += ' ';
  }
  if (!result.empty() && result.back() == ' ') {
    result.pop_back();
  }
  return result;
}

int eval(const string& post) {
  TStack<int, 100> stack;
  for (int i = 0; i < post.length(); i++) {
    char d = post[i];
    if (d == ' ') continue;
    if (isdigit(d)) {
      int number = 0;
      while (i < post.length() && isdigit(post[i])) {
        number = number * 10 + (post[i] - '0');
        i++;
      }
      stack.push(number);
      i--;
    } else if (isOperator(d)) {
      int b = stack.pop();
      int a = stack.pop();
      int result = doOperation(a, b, d);
      stack.push(result);
    }
  }
  return stack.pop();
}
