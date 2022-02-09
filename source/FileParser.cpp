#include "FileParser.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

FileParser::FileParser( std::string fn ) {
  file_name = fn;
}

int FileParser::string_to_hex( std::string str ) {
  int converted = 0;
  for (char c: str) {
    converted <<= 4;
    if (c >= '0' && c <= '9') {
      converted += (int)(c - '0');
    } else {
      if (c == 'a' || c == 'A') converted += 10;
      if (c == 'b' || c == 'B') converted += 11;
      if (c == 'c' || c == 'C') converted += 12;
      if (c == 'd' || c == 'D') converted += 13;
      if (c == 'e' || c == 'E') converted += 14;
      if (c == 'f' || c == 'F') converted += 15;
    }
  }
  return converted;
}

void FileParser::handle() {
  std::ifstream file( file_name );

  if ( file.is_open() ) {
    std::string line;
    while ( getline(file, line) ) {
      size_t comma = line.find( ':' );
      std::string address = line.substr( 0, comma );
      std::string instruction = line.substr(comma + 1);

      address.erase(std::remove(address.begin(), address.end(), ' '), address.end());
      instruction.erase(std::remove(instruction.begin(), instruction.end(), ' '), instruction.end());

      int address_hex = string_to_hex(address);
      int instruction_hex = string_to_hex(instruction);

      program_parsed.emplace_back(address_hex, instruction_hex);
    }
  } else {
    std::cout << "unable to open file!" << std::endl;
    exit(1);
  }
}

std::vector< std::pair<int, int>> FileParser::get_program_mapped() {
  return program_parsed;
}