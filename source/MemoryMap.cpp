#include "Constants.h"
#include "MemoryMap.h"
#include <iostream>
#include <stdlib.h>

int MemoryMap::fetchProgramInstruction(int pc) {
  int gap = pc % 4;
  pc = pc - gap;
  if (pc % 4 == 2) {
    /*** right instruction ***/
    return (program_map[pc] >> 16) & 0xffff;
  } else {
    /*** left instruction ***/
    return program_map[pc] & 0xffff;
  }
}

MemoryMap::MemoryMap(std::map<int, int> program_map) {
  this->program_map = program_map;
}

int MemoryMap::fecthData(int addr) {
  return program_map[addr];
}

MemoryMap::MemoryMap() {}

void MemoryMap::setData(int addr, int value) {
  program_map[addr] = value;
}