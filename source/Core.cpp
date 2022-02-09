#include "Core.h"

#include <iostream>
#include <iomanip>
#include "Constants.h"

Core::Core(std::string filename) : cpsr(SUPERVISOR_MODE | THUMB_MODE), spsr(0) {
  r[0] = r[1] = r[2] = r[3] = r[4] = r[5] = r[6] = r[7] = 0; /** THUMB full access registers */
  r[8] = r[9] = r[10] = r[11] = r[12] = 0; /** ARM registers */
  r[13] = STACK_POINTER_ADDRESS; /** stack pointer */
  r[14] = 0; /** link register */
  r[15] = 0; /** program count */

  file_parser = FileParser(filename);
  file_parser.handle();

  std::map<int, int> prog_mem;

  for (std::pair<int, int> cell: file_parser.get_program_mapped()) {
    prog_mem[cell.first] = cell.second;
  }
  
  memory = MemoryMap(prog_mem);
}

void Core::describe() {
  std::cout << "#####################" << std::endl;
  std::cout << "------CORE STATS-----" << std::endl;
  std::cout << std::hex; /** show registers values in hex format */
  std::cout << std::setw(6) << "pc: " << "0x" << r[15] << std::endl;
  /** show thumb registers */
  for (int index = 0; index < 8; ++index)
    std::cout << std::setw(6) << "r" << index << ": " << "0x" << r[index] << std::endl;
  std::cout << std::setw(6) << "cpsr: " << std::setw(13) << ps_to_string(cpsr) << std::endl;
  std::cout << std::setw(6) << "spsr: " << std::setw(13) << ps_to_string(spsr) << std::endl;
  std::cout << std::dec; /** restore default values format */

  std::cout << "#####################" << std::endl;
  std::cout << "------MEMORY MAP-----" << std::endl;
  for (auto f: memory.program_map) {
    std::cout << std::hex;
    std::cout << "0x" << f.first << ":" << f.second << std::endl;
    std::cout << std::dec;
  }
}

std::string Core::ps_to_string(int psr) {
  if (psr == 0) {
    return "--------- ---";
  }
  std::string r = "";
  r += (NEGATIVE_FLAG & psr) ? "N" : "n";
  r += (ZERO_FLAG & psr) ? "Z" : "z";
  r += (CARRY_FLAG & psr) ? "C" : "c";
  r += (OVERFLOW_FLAG & psr) ? "V" : "v";
  r += (SATURATED_FLAG & psr) ? "Q" : "q";
  r += (JAZEL_MODE & psr) ? "J" : "j";
  r += (INTERRUPTION_MODE & psr) ? "I" : "i";
  r += (FAST_INTERRUPTION_MODE & psr) ? "F" : "f";
  r += (THUMB_MODE & psr) ? "T" : "t";
  r += "_";
  psr &= 0b11111;
  r += psr == 0b10111 ? "abt" : psr == 0b10001 ? "fiq" : psr == 0b10010 ? "irq" : psr == 0b10011 ? "svc" : psr == 0b11111 ?
    "sys" : psr == 0b11011 ? "und" : psr == 0b10000 ? "usr" : "ERR";
  return r;
}

void Core::run() {
  int instruction = memory.fetchProgramInstruction(r[15]);

  if (instruction == 0) {
    // no fetch data
    std::cout << "Data abort. Unhandle instruction or unavaliable." << std::endl;
    describe();
    exit(0);
  }

  int status = decoder.decode(instruction, &cpsr, r, &memory);
  if (status == 2) {
    std::cout << std::hex << instruction << std::dec << std::endl;
  }

  if (status == 1) {
    describe();
  }

  r[15] += 2; // next instruction
}