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
  
  std::string line;
  std::getline(string, line);
  int size_line = 0;
  std::string size_line_s;
  int cycle = 0;
  std::string cycle_s;
  int i = 0;
  while (line[i] != ' ') {
    size_line_s += line[i];
    ++i;
  }
  size_line = std::stoi(size_line_s);
  while (line[i] == ' ') {
    ++i;
  }
  while (line[i] != ' ') {
    cycle_s += line[i];
    ++i;
  }
  cycle = std::stoi(cycle_s);
  std::string init;
  while (line[i] == ' ') {
    ++i;
  }
  while (line[i] != ' ' && line[i] != '\0' && line[i] != '\n') {
    init += line[i];
    ++i;
  }
  PostMachine programm(size_line, argv[1]); 
  otp << programm.calc(init, cycle);
  string.close();
  otp.close();
  return 0;
}
