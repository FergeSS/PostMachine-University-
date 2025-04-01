#ifndef POSTMACHINE_H
#define POSTMACHINE_H

#include <fstream>
#include <iostream>
#include <cstring>
#include <string>

struct Program {
  int number_of_command_;
  char command_;
  int next_command_;
  int next_command_two_;
};

class PostMachine {
private:
    int size_;
    int size_of_commands_;
    Program* commands_;
public:
    PostMachine(int size, char* program);
    std::string calc(std::string const& init, int maxsteps);
    ~PostMachine() { 
        delete[] commands_;
    }
};
#endif  // !POSTMACHINE_H
