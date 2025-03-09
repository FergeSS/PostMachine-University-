#include "postmachine.h"

PostMachine::PostMachine(int size, char* program) {
  std::ifstream inp(program);

  size_ = size;
  int size_of_commands = 0;
  std::string line;
  std::string num;
  std::streampos startPos = inp.tellg();
  while (std::getline(inp, line)) {
    ++size_of_commands;
  }
  inp.clear();
  inp.seekg(startPos, std::ios::beg);

  commands_ = new Program[size_of_commands];

  int i = 0;
  while (std::getline(inp, line)) {
    if (line[0] == '%') {
      delete[] commands_;
      commands_ = new Program[size_of_commands - 1];
      continue;
    }
    int k = 0;
    while (line[k] != '.') {
      num += line[k];
      ++k;
    }
    ++k;
    commands_[i].number_of_command_ = std::stoi(num);
    while (line[k] == ' ') {
      ++k;
    }
    commands_[i].command_ = line[k];
    if (line[k] == '!') {
      num = "";
      ++i;
      continue;
    }
    ++k;
    while (line[k] == ' ') {
      ++k;
    }
    num = "";
    while (line[k] != ' ' && line[k] != '\n' && line[k] != '\0') {
      num += line[k];
      ++k;
    }
    commands_[i].next_command_ = std::stoi(num);
    if (commands_[i].command_ == '?') {
      while (line[k] == ' ') {
        ++k;
      }
      num = "";
      while (line[k] != ' ' && line[k] != '\n' && line[k] != '\0') {
        num += line[k];
        ++k;
      }
      commands_[i].next_command_two_ = std::stoi(num);
    } else {
      commands_[i].next_command_two_ = -1;
    }
    num = "";
    ++i;
  }
  size_of_commands_ = i;
}
