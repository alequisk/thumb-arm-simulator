#include "Core.h"

#include <iostream>
#include <iomanip>
#include <string.h>

Core::Core() :
  pc(PROGRAM_MEM_ADDRESS), lr(0), sp(STACK_POINTER_ADDRESS), cpsr(SUPERVISOR_MODE | THUMB_MODE), spsr(0) {
  memset(r, 0, sizeof (r));
}

void Core::describe() {
  std::cout << std::setw(6) << "pc: "   << "0x" << std::hex << pc << std::endl;
  for (int index = 0; index < 7; ++index) {
    std::cout << std::setw(6) << "r" << index << ": "   << "0x" << std::hex << r[index] << std::endl;
  }
  std::cout << std::setw(6) << "cpsr: " << std::setw(13) << ps_to_string(cpsr) << std::endl;
  std::cout << std::setw(6) << "spsr: " << std::setw(13) << ps_to_string(spsr) << std::endl;
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