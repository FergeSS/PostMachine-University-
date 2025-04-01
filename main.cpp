#include "postmachine.h"

int main(int argc, char* argv[]){
  if (argc < 4) {
    std::cout << "Not enough arguments!";
    return -1;
  }
  std::ifstream string(argv[2]);
  if (!string) {
    std::cout << "No file with string!";
    return -1;
  }
  std::ifstream program(argv[1]);
  if (!program) {
    std::cout << "No file with program!";
    return -1;
  }
  program.close();
  std::ofstream otp(argv[3]);
  if (!otp) {
    std::cout << "Can not open output file!";
    return -1;
  }
  
  int size_line = 0;
  int cycle = 0;
  std::string init;
  string >> size_line >> cycle >> init;
  string.close();

  PostMachine programm(size_line, argv[1]); 
  otp << programm.calc(init, cycle);  
  otp.close();
  
  return 0;
}
