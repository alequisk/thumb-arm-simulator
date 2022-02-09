#include "Decoder.h"
#include "Constants.h"
#include "Implementation.h"
#include <iostream>
#include <limits.h>

void Decoder::decode(signed short int instruction, int* psr, int *reg) {
  int instruction_code = (instruction >> 12) & 0b1111;
  
  if (instruction_code == 0b0000) {
    int rm = (instruction >> 3) & 0b111;
    int rd = instruction & 0b111;
    int immed = (instruction >> 6) & 0b11111; // immed5
    
    int op = (instruction >> 11) & 0b1;
    if (op == 0b0) {
      LSR_immed(reg, psr, rd, rm, immed);
      return;  
    } else {
      LSR_immed(reg, psr, rd, rm, immed);
      return;
    }
  }

  if (instruction_code == 0b0001 && Tbit(instruction, 11) == 0b0) {
    int immed = (instruction >> 6) & 0b11111;
    int rm = (instruction >> 3) & 0b111;
    int rd = instruction & 0b111;
    ASR_immed(reg, psr, rd, rm, immed);
    return;
  }

  if (instruction_code == 0b0001 && Tbit(instruction, 11) == 0b1 && Tbit(instruction, 10) == 0b0) {
    int op = (instruction >> 9) & 0b1;
    int rm = (instruction >> 6) & 0b111;
    int rn = (instruction >> 3) & 0b111;
    int rd = instruction & 0b111;
    if (op == 0b0) {
      ADD_regs(reg, rd, rn, rm);
      return;
    } else {
      SUB_regs(reg, rd, rn, rm);
      return;
    }
  }

  if (instruction_code == 0b0001 && Tbit(instruction, 11) == 0b1 && Tbit(instruction, 10) == 0b1) {
    int op = (instruction >> 9) & 0b1;
    int immed = (instruction >> 6) & 0b111;
    int rn = (instruction >> 3) & 0b111;
    int rd = instruction & 0b111;
    if (op == 0b0) {
      ADD_immed(reg, rd, rn, immed);
      return;
    } else {
      SUB_immed(reg, rd, rn, immed);
      return;
    }
  }

  if (instruction_code == 0b0010) {
    int op = (instruction >> 11) & 0b1;
    int immed = instruction & 0b11111111;
    int rd = (instruction >> 8) & 0b111;
    if (op == 0b0) {
      MOV_immed(reg, rd, immed);
      return;
    } else {
      CMP_immed(reg, psr, rd, immed);
      return;
    }
  }

  if (instruction_code == 0b0011) {
    int op = (instruction >> 11) & 0b1;
    int rd = (instruction >> 8) & 0b111;
    int immed = instruction & 0b11111111;  
    if (op == 0b0) {
      ADD_immed(reg, rd, immed);
      return;
    } else {
      SUB_immed(reg, rd, immed);
      return;
    }
  }

  if (instruction_code == 0b0100 && Tbit(instruction, 11) == 0b0) {
    int next_three = (instruction >> 8) & 0b111;
    if (next_three == 0b000) {
      int op = (instruction >> 6) & 0b11;
      int rm = (instruction >> 3) & 0b111;
      int rd = instruction & 0b111;
      if (op == 0b00) {
        AND(reg, rd, rm);
        return;
      } else if (op == 0b01) {
        EOR(reg, rd, rm);
        return;
      } else if (op == 0b10) {
        LSL_reg(reg, psr, rd, rm);
        return;
      } else {
        LSR_reg(reg, psr, rd, rm);
        return;
      }
    } else if (next_three == 0b001) {
      int op = (instruction >> 6) & 0b11;
      int rm = (instruction >> 3) & 0b111;
      int rd = instruction & 0b111;
      if (op == 0b00) {
        ASR_regs(reg, psr, rd, rm);
        return;
      } else if (op == 0b01) {
        ADC(reg, psr, rd, rm);
        return;
      } else if (op == 0b10) {
        SBC(reg, psr, rd, rm);
        return;
      } else {
        ROR(reg, psr, rd, rm);
        return;
      }
    } else if (next_three == 0b010) {
      int op = (instruction >> 6) & 0b11;
      int rm = (instruction >> 3) & 0b111;
      int rd = instruction & 0b111;
      if (op == 0b00) {
        TST(reg, psr, rd, rm);
        return;
      } else if (op == 0b01) {
        NEG(reg, rd, rm);
        return;
      } else if (op == 0b10) {
        CMP_regs(reg, psr, rd, rm);
        return;
      } else {
        CMN(reg, psr, rd, rm);
        return;
      }
    } else if (next_three == 0b011) {
      int op = (instruction >> 6) & 0b11;
      int rm = (instruction >> 3) & 0b111;
      int rd = instruction & 0b111;
      if (op == 0b00) {
        ORR(reg, rd, rm);
        return;
      } else if (op == 0b01) {
        MUL(reg, rd, rm);
        return;
      } else if (op == 0b10) {
        BIC(reg, rd, rm);
        return;
      } else {
        MVN(reg, rd, rm);
        return;
      }
    } else if (next_three == 0b110 && Tbit(instruction, 7) == 0b0 && Tbit(instruction, 6) == 0b0) {
      int rm = (instruction >> 3) & 0b111;
      int rd = instruction & 0b111;
      CPY(reg, rd, rm);
      return;
    } else {
      int other_three = (instruction >> 6) & 0b111;
      if (other_three == 0b001) {
        int hm = (instruction >> 3) & 0b111;
        int ld = instruction & 0b111;
        int op = (instruction >> 9) & 0b1;
        if (op == 0b0) {
          ADD_regs(reg, ld, hm + 8);
          return;
        } else {
          MOV_regs(reg, ld, hm + 8);
          return;
        }
      } else if (other_three == 0b010) {
        int lm = (instruction >> 3) & 0b111;
        int hd = instruction & 0b111;
        int op = (instruction >> 9) & 0b1;
        if (op == 0b0) {
          ADD_regs(reg, hd + 8, lm);
          return;
        } else {
          MOV_regs(reg, hd + 8, lm);
          return;
        }
      } else if (other_three == 0b011) {
        int hm = (instruction >> 3) & 0b111;
        int hd = instruction & 0b111;
        int op = (instruction >> 9) & 0b1;
        if (op == 0b0) {
          ADD_regs(reg, hd + 8, hm + 8);
          return;
        } else {
          MOV_regs(reg, hd + 8, hm + 8);
          return;
        }
      } else if (other_three == 0b101 && Tbit(instruction, 9) == 0b0) {
        int hm = (instruction >> 3) & 0b111;
        int ln = instruction & 0b111;
        CMP_regs(reg, psr, hm + 8, ln);
        return;
      } else if (other_three == 0b110 && Tbit(instruction, 9) == 0b0) {
        int lm = (instruction >> 3) & 0b111;
        int hn = instruction & 0b111;
        CMP_regs(reg, psr, lm, hn + 8);
        return;
      } else if (other_three == 0b111 && Tbit(instruction, 9) == 0b0) {
        int hm = (instruction >> 3) & 0b111;
        int hn = instruction & 0b111;
        CMP_regs(reg, psr, hm + 8, hn + 8);
        return;
      } else {
        //int op = (instruction >> 7) & 0b1;
        //int rm = (instruction >> 3) & 0b1111;
        //TODO: make BLX and BL instructions
      }
    }
  }

  std::cout << "Undefined instruction to decode" << std::endl;

  //throw "Undefined instruction to decode."; // return Error of instruction
}

bool Decoder::checkOverflow(int a, int b, OPERATORS op) {
  if (op == ADD) {
    if ((b > 0) && (a > INT_MAX - b))  return true; /* `a + x` would overflow */;
    if ((b < 0) && (a < INT_MIN - b))  return true; /* `a + x` would underflow */;
  }

  if (op == SUB) {
    if ((b < 0) && (a > INT_MAX + b)) return true; /* `a - x` would overflow */;
    if ((b > 0) && (a < INT_MIN + b)) return true; /* `a - x` would underflow */;
  }

  return false;
}