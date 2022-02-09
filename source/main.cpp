#include "Core.h"
#include "FileParser.h"
#include "Decoder.h"
#include "Constants.h"

#include <iostream>

int main (int argc, char** argv) {

  if ( argc > 2 ) {
    std::cerr << "You must o pass **only** the filename with extension to run!" << std::endl;
    return (1);
  } else if ( argc == 1 ) {
    std::cerr << "You must o pass the filename with extension to run!" << std::endl;
    return (1);
  }
  
  Core core = Core(argv[1]);

  while (true) {
    core.run();
  }
  
  core.describe();

  
  return (0);
}