#include "postmachine.h"

PostMachine::PostMachine(int size, char* program) {
  std::ifstream inp(program);

  size_ = size;
  size_of_commands_ = 0;
  int size_of_comments = 0;
  std::string line;
  std::string num;
  std::streampos startPos = inp.tellg();
  while (std::getline(inp, line)) {
    if (line[0] == '%') {
      ++size_of_comments;
      continue;
    }
    ++size_of_commands_;
  }
  inp.clear();
  inp.seekg(startPos, std::ios::beg);

  commands_ = new Program[size_of_commands_ - 1];

  for (int i = 0; i < size_of_comments; ++i) {
    std::getline(inp, line);
  }


  for (int i = 0; i < size_of_commands_; ++i) {
    char ch;
    int command;
    inp >> command; //number of command
    commands_[i].number_of_command_ = command;
    inp >> ch; // dot
    inp >> ch; //command

    commands_[i].command_ = ch;
    switch(ch) {
      case '?':
        inp >> command;
        commands_[i].next_command_ = command;
        inp >> command;
        commands_[i].next_command_two_ = command;
        break;
      case '!':
        break;
      default: 
        inp >> command;
        commands_[i].next_command_ = command;
        commands_[i].next_command_two_ = -1;
        break;        
    }    
  }
}

std::string PostMachine::calc(std::string const& init, int maxsteps) {
    int* line = new int[this->size_];
    int size_init = static_cast<int>(init.size());
    
    for (int i = 0; i < size_init; ++i) {
        line[i] = init[i] - '0';
    }
    for (int i = size_init; i < this->size_; ++i) {
        line[i] = 0;
    }

    int pointer = 0;
    int pointer_of_command = -1;
    int index_of_command = 0;
    int step = 0;
    int min = 2147483647;
    bool flag = false;
    while (step <= maxsteps) {
        flag = false;

        for (int i = 0; i < size_of_commands_ ; ++i) {
            if (pointer_of_command == -1) {
                for (int k = 0; k < size_of_commands_; ++k) {
                    min = std::min(min, commands_[k].number_of_command_);
                }
                pointer_of_command = min;
            }
            if (commands_[i].number_of_command_ == pointer_of_command) {
                index_of_command = i;
                pointer_of_command = commands_[i].next_command_;
                flag = true;
                break;
            }
        }
        if (!flag) {
            delete[] line;
            return "Error";
        }

        if (commands_[index_of_command].command_ == 'V') {
            line[pointer] = 1;
        }
        if (commands_[index_of_command].command_ == 'X') {
            line[pointer] = 0;
        }
        if (commands_[index_of_command].command_ == 'L') {
            if (pointer == 0) {
                pointer = this->size_ - 1;
            } else {
                --pointer;
            }
        }
        if (commands_[index_of_command].command_ == 'R') {
            if (pointer == this->size_ - 1) {
                pointer = 0;
            } else {
                ++pointer;
            }
        }
        if (commands_[index_of_command].command_ == '?') {
            if (line[pointer] == 0) {
                pointer_of_command = commands_[index_of_command].next_command_;
            } else {
                pointer_of_command = commands_[index_of_command].next_command_two_;
            }
        }
        if (commands_[index_of_command].command_ == '!') {
            std::string res;
            int last_one;
            int i = pointer;
            do {
                if (line[i] == 1) {
                    last_one = i;
                }
                if (i == this->size_ - 1) {
                    i = 0;
                } else {
                    ++i;
                }
            } while (i != pointer);
            
            do {
                res += std::to_string(line[pointer]);
                if (pointer == this->size_ - 1) {
                    pointer = 0;
                } else {
                    ++pointer;
                }                
            } while (pointer != last_one + 1);                
            
            delete[] line;
            return res;
        }
        ++step;
    }
    delete[] line;
    return "Not applicable";
}  