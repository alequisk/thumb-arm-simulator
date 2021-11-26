#include "Core.h"
#include "FileParser.h"

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
  Core core;

  file_parser.handle();
  core.describe();

  return (0);
}