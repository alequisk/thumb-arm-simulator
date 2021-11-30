#include "Core.h"
#include "FileParser.h"
#include "Decoder.h"

#include <iostream>

int main (int argc, char** argv) {

  if ( argc > 2 ) {
    std::cerr << "You must o pass **only** the filename with extension to run!" << std::endl;
    return (1);
  } else if ( argc == 1 ) {
    std::cerr << "You must o pass the filename with extension to run!" << std::endl;
    return (1);
  }
  
  FileParser file_parser( argv[1] );
  Decoder decoder;
  Core core;

  file_parser.handle();
  // core.describe();
  int instruction = file_parser.get_program_mapped()[0].second;
  int left_instruction = (instruction >> 16) & 65535;
  int right_instruction = instruction & 65535;

  std::cout << "left: " << decoder.decode(left_instruction) << std::endl; 
  std::cout << "right: " << decoder.decode(right_instruction) << std::endl; 

  return (0);
}