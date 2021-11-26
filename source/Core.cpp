#include "Core.h"

#include <iostream>
#include <iomanip>

void Core::describe() {
  std::cout << std::setw(6) << "pc: "   << "0x" << std::hex << pc << std::endl;
  std::cout << std::setw(6) << "r0: "   << "0x" << std::hex << r0 << std::endl;
  std::cout << std::setw(6) << "r1: "   << "0x" << std::hex << r1 << std::endl;
  std::cout << std::setw(6) << "r2: "   << "0x" << std::hex << r2 << std::endl;
  std::cout << std::setw(6) << "r3: "   << "0x" << std::hex << r3 << std::endl;
  std::cout << std::setw(6) << "r4: "   << "0x" << std::hex << r4 << std::endl;
  std::cout << std::setw(6) << "r5: "   << "0x" << std::hex << r5 << std::endl;
  std::cout << std::setw(6) << "r6: "   << "0x" << std::hex << r6 << std::endl;
  std::cout << std::setw(6) << "r7: "   << "0x" << std::hex << r7 << std::endl;
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