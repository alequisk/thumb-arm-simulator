#include "Decoder.h"
#include "Constants.h"
#include <iostream>

void Decoder::decode(signed short int instruction, int& psr, int *reg) {
  int instruction_code = (instruction >> 12) & 0b1111;

  /*** First line ***/
  if (instruction_code == 0b0000) {
    int op = (instruction >> 11) & 0b1;
    int ld = instruction & 0b111;
    int lm = (instruction >> 3) & 0b111;
    int immed5 = (instruction >> 6) & 0b11111;

    if (op == 0b0) {
      /*** LSL | immed5 Lm Ld ***/
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
    
    } else {
      /*** LSR | immed5 Lm Ld ***/
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
    /*** Second line ***/

    if (((instruction >> 11) & 0b1) == 0b0) {
      /*** ASR | immed5 Lm Ld ***/
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
    } else {
      
      if (((instruction >> 10) & 0b1) == 0b0) {
        /*** Third line **/

        int op = ((instruction) >> 9) & 0b1;
        int ld = instruction & 0b111;
        int ln = (instruction >> 3) & 0b111;
        int lm = (instruction >> 6) & 0b111;

        /*** ADD | SUB ***/
        if (op == 0b0) {
          /*** ADD | Lm, Ln, Ld ***/
#ifdef DEBUG 
          std::cout << "(Decoder) ADD | Lm, Ln, Ld" << std::endl;
#endif
          reg[ld] = reg[ln] + reg[lm];
          return;
        } else {

          /*** SUB | Lm, Ln, Ld ***/
#ifdef DEBUG 
          std::cout << "(Decoder) SUB | Lm, Ln, Ld" << std::endl;
#endif
          reg[ld] = reg[ln] - reg[lm];
          return;
        }
      } else {
        /*** Fourth line **/
        
        int op = ((instruction) >> 9) & 0b1;
        int ld = instruction & 0b111;
        int ln = (instruction >> 3) & 0b111;
        int immed3 = (instruction >> 6) & 0b111;

        if (op == 0b0) {
          /*** ADD | immed3, Ln, Ld ***/
#ifdef DEBUG 
          std::cout << "(Decoder) ADD | immed3, Ln, Ld" << std::endl;
#endif
          reg[ld] = immed3 + reg[ln];
          return;
        } else {
          /*** SUB | immed3, Ln, Ld ***/
#ifdef DEBUG 
          std::cout << "(Decoder) SUB | immed3, Ln, Ld" << std::endl;
#endif
          reg[ld] = reg[ln] - immed3;
          return;
        }
      }
    }
  }

  throw "Undefined instruction to decode."; // return Error of instruction
}