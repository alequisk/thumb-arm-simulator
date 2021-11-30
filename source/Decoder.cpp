#include "Decoder.h"
#include "Constants.h"
#include <iostream>

void Decoder::decode(signed short int instruction, int& psr, int *reg) {
  int instruction_code = (instruction >> 12) & 0b1111;
  if (instruction_code == 0b0000) {
    int op = (instruction >> 11) & 0b1;
    int ld = instruction & 0b111;
    int lm = (instruction >> 3) & 0b111;
    int immed5 = (instruction >> 6) & 0b11111;

    if (op == 0b0) { // LSL | immed5 Lm Ld
#ifdef DEBUG 
      std::cout << std::hex << "(Decoder) LSL | immed5=" << immed5 << " Lm=" << lm << " Ld=" << ld << std::dec << std::endl;
#endif
      reg[ld] = reg[lm] << immed5; // execute
      if ((reg[lm] >> (32 - immed5)) & 0b1) {
        psr |= CARRY_FLAG; // set the flag
      } else {
        psr &= ~CARRY_FLAG; // clear carry flag
      }
      return;
    } else { // LSR | immed5 Lm Ld
#ifdef DEBUG
      std::cout << std::hex << "(Decoder) LSR | immed5=" << immed5 << " Lm=" << lm << " Ld=" << ld << std::dec << std::endl;
#endif
      reg[ld] = reg[lm] >> immed5; // execute
      if ((reg[ld] >> (immed5 - 1)) & 0b1) {
        psr |= CARRY_FLAG; // set the flag
      } else {
        psr &= ~CARRY_FLAG; // clear carry flag
      }
      return;
    }
  }

  if (instruction_code == 0b0001) {
    if (((instruction >> 11) & 0b1) == 0b0) { // ASR | immed5 Lm Ld
#ifdef DEBUG 
      std::cout << "(Decoder) ASR | immed5 Lm Ld" << std::endl;
#endif
      int ld = instruction & 0b111;
      int lm = (instruction >> 3) & 0b111;
      int immed5 = (instruction >> 6) & 0b11111;

      reg[ld] = reg[lm] >> immed5; // execute
      if ((reg[lm] >> (immed5 - 1)) & 0b1) {
        psr |= CARRY_FLAG; // set the flag
      } else {
        psr &= ~CARRY_FLAG; // clear carry flag
      }
      return;
    } else { // ADD | SUB

    }
  }

  throw "Undefined instruction to decode."; // return Error of instruction
}