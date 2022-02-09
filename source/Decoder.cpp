#include "Decoder.h"
#include "Constants.h"
#include "Implementation.h"
#include <iostream>
#include <limits.h>

int Decoder::decode(signed short int instruction, int* psr, int *reg, MemoryMap* mem) {
  int instruction_code = (instruction >> 12) & 0b1111;
  
  if (instruction_code == 0b0000) {
    int rm = (instruction >> 3) & 0b111;
    int rd = instruction & 0b111;
    int immed = (instruction >> 6) & 0b11111; // immed5
    
    int op = (instruction >> 11) & 0b1;
    if (op == 0b0) {
      LSR_immed(reg, psr, rd, rm, immed);
      return 0;  
    } else {
      LSR_immed(reg, psr, rd, rm, immed);
      return 0;
    }
  }

  if (instruction_code == 0b0001 && Tbit(instruction, 11) == 0b0) {
    int immed = (instruction >> 6) & 0b11111;
    int rm = (instruction >> 3) & 0b111;
    int rd = instruction & 0b111;
    ASR_immed(reg, psr, rd, rm, immed);
    return 0;
  }

  if (instruction_code == 0b0001 && Tbit(instruction, 11) == 0b1 && Tbit(instruction, 10) == 0b0) {
    int op = (instruction >> 9) & 0b1;
    int rm = (instruction >> 6) & 0b111;
    int rn = (instruction >> 3) & 0b111;
    int rd = instruction & 0b111;
    if (op == 0b0) {
      ADD_regs(reg, rd, rn, rm);
      return 0;
    } else {
      SUB_regs(reg, rd, rn, rm);
      return 0;
    }
  }

  if (instruction_code == 0b0001 && Tbit(instruction, 11) == 0b1 && Tbit(instruction, 10) == 0b1) {
    int op = (instruction >> 9) & 0b1;
    int immed = (instruction >> 6) & 0b111;
    int rn = (instruction >> 3) & 0b111;
    int rd = instruction & 0b111;
    if (op == 0b0) {
      ADD_immed(reg, rd, rn, immed);
      return 0;
    } else {
      SUB_immed(reg, rd, rn, immed);
      return 0;
    }
  }

  if (instruction_code == 0b0010) {
    int op = (instruction >> 11) & 0b1;
    int immed = instruction & 0b11111111;
    int rd = (instruction >> 8) & 0b111;
    if (op == 0b0) {
      MOV_immed(reg, rd, immed);
      return 0;
    } else {
      CMP_immed(reg, psr, rd, immed);
      return 0;
    }
  }

  if (instruction_code == 0b0011) {
    int op = (instruction >> 11) & 0b1;
    int rd = (instruction >> 8) & 0b111;
    int immed = instruction & 0b11111111;  
    if (op == 0b0) {
      ADD_immed(reg, rd, immed);
      return 0;
    } else {
      SUB_immed(reg, rd, immed);
      return 0;
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
        return 0;
      } else if (op == 0b01) {
        EOR(reg, rd, rm);
        return 0;
      } else if (op == 0b10) {
        LSL_reg(reg, psr, rd, rm);
        return 0;
      } else {
        LSR_reg(reg, psr, rd, rm);
        return 0;
      }
    } else if (next_three == 0b001) {
      int op = (instruction >> 6) & 0b11;
      int rm = (instruction >> 3) & 0b111;
      int rd = instruction & 0b111;
      if (op == 0b00) {
        ASR_regs(reg, psr, rd, rm);
        return 0;
      } else if (op == 0b01) {
        ADC(reg, psr, rd, rm);
        return 0;
      } else if (op == 0b10) {
        SBC(reg, psr, rd, rm);
        return 0;
      } else {
        ROR(reg, psr, rd, rm);
        return 0;
      }
    } else if (next_three == 0b010) {
      int op = (instruction >> 6) & 0b11;
      int rm = (instruction >> 3) & 0b111;
      int rd = instruction & 0b111;
      if (op == 0b00) {
        TST(reg, psr, rd, rm);
        return 0;
      } else if (op == 0b01) {
        NEG(reg, rd, rm);
        return 0;
      } else if (op == 0b10) {
        CMP_regs(reg, psr, rd, rm);
        return 0;
      } else {
        CMN(reg, psr, rd, rm);
        return 0;
      }
    } else if (next_three == 0b011) {
      int op = (instruction >> 6) & 0b11;
      int rm = (instruction >> 3) & 0b111;
      int rd = instruction & 0b111;
      if (op == 0b00) {
        ORR(reg, rd, rm);
        return 0;
      } else if (op == 0b01) {
        MUL(reg, rd, rm);
        return 0;
      } else if (op == 0b10) {
        BIC(reg, rd, rm);
        return 0;
      } else {
        MVN(reg, rd, rm);
        return 0;
      }
    } else if (next_three == 0b110 && Tbit(instruction, 7) == 0b0 && Tbit(instruction, 6) == 0b0) {
      int rm = (instruction >> 3) & 0b111;
      int rd = instruction & 0b111;
      CPY(reg, rd, rm);
      return 0;
    } else {
      int other_three = (instruction >> 6) & 0b111;
      if (other_three == 0b001) {
        int hm = (instruction >> 3) & 0b111;
        int ld = instruction & 0b111;
        int op = (instruction >> 9) & 0b1;
        if (op == 0b0) {
          ADD_regs(reg, ld, hm + 8);
          return 0;
        } else {
          MOV_regs(reg, ld, hm + 8);
          return 0;
        }
      } else if (other_three == 0b010) {
        int lm = (instruction >> 3) & 0b111;
        int hd = instruction & 0b111;
        int op = (instruction >> 9) & 0b1;
        if (op == 0b0) {
          ADD_regs(reg, hd + 8, lm);
          return 0;
        } else {
          MOV_regs(reg, hd + 8, lm);
          return 0;
        }
      } else if (other_three == 0b011) {
        int hm = (instruction >> 3) & 0b111;
        int hd = instruction & 0b111;
        int op = (instruction >> 9) & 0b1;
        if (op == 0b0) {
          ADD_regs(reg, hd + 8, hm + 8);
          return 0;
        } else {
          MOV_regs(reg, hd + 8, hm + 8);
          return 0;
        }
      } else if (other_three == 0b101 && Tbit(instruction, 9) == 0b0) {
        int hm = (instruction >> 3) & 0b111;
        int ln = instruction & 0b111;
        CMP_regs(reg, psr, hm + 8, ln);
        return 0;
      } else if (other_three == 0b110 && Tbit(instruction, 9) == 0b0) {
        int lm = (instruction >> 3) & 0b111;
        int hn = instruction & 0b111;
        CMP_regs(reg, psr, lm, hn + 8);
        return 0;
      } else if (other_three == 0b111 && Tbit(instruction, 9) == 0b0) {
        int hm = (instruction >> 3) & 0b111;
        int hn = instruction & 0b111;
        CMP_regs(reg, psr, hm + 8, hn + 8);
        return 0;
      } else {
        int op = (instruction >> 7) & 0b1;
        int rm = (instruction >> 3) & 0b1111;
        if (op == 0b0) {
          BX(reg, psr, rm);
          return 0;
        } else {
          BLX_regs(reg, psr, rm);
          return 0;
        }
      }
    }
  }

  if (instruction_code == 0b1011 && ((instruction >> 8) & 0b1111) == 0b1110) {
    return 1;
  }

  if (instruction_code == 0b0100 && Tbit(instruction, 11) == 0b1) {
    int immed = instruction & 0b11111111; // immed8
    int ld = (instruction >> 8) & 0b111;
    LDR(reg, mem, ld, reg[15] + immed * 4);
    return 0;
  }

  if (instruction_code == 0b1101) {
    int next_four = (instruction >> 8) & 0b1111;
    
    if (next_four == 0b0000) {
      int offset = instruction & 0b11111111;
      BEQ(reg, psr, offset);
      return 0;
    } else if (next_four == 0b0001) {
      int offset = instruction & 0b11111111;
      BNE(reg, psr, offset);
      return 0;
    } else if (next_four == 0b0010) {
      int offset = instruction & 0b11111111;
      BHS(reg, psr, offset);
      return 0;
    } else if (next_four == 0b0011) {
      int offset = instruction & 0b11111111;
      BLO(reg, psr, offset);
      return 0;
    } else if (next_four == 0b0100) {
      int offset = instruction & 0b11111111;
      BMI(reg, psr, offset);
      return 0;
    } else if (next_four == 0b0101) {
      int offset = instruction & 0b11111111;
      BPL(reg, psr, offset);
      return 0;
    } else if (next_four == 0b0110) {
      int offset = instruction & 0b11111111;
      BVS(reg, psr, offset);
      return 0;
    } else if (next_four == 0b0111) {
      int offset = instruction & 0b11111111;
      BVC(reg, psr, offset);
      return 0;
    } else if (next_four == 0b1000) {
      int offset = instruction & 0b11111111;
      BHI(reg, psr, offset);
      return 0;
    } else if (next_four == 0b1001) {
      int offset = instruction & 0b11111111;
      BLS(reg, psr, offset);
      return 0;
    } else if (next_four == 0b1010){
      int offset = instruction & 0b11111111;
      BGE(reg, psr, offset);
      return 0;
    } else if (next_four == 0b1011) {
      int offset = instruction & 0b11111111;
      BLT(reg, psr, offset);
      return 0;
    } else if (next_four == 0b1100) {
      int offset = instruction & 0b11111111;
      BGT(reg, psr, offset);
      return 0;
    } else if (next_four == 0b1101) {
      int offset = instruction & 0b11111111;
      BLE(reg, psr, offset);
      return 0;
    } else if (next_four == 0b1110) {
      int offset = instruction & 0b11111111;
      BAL(reg, psr, offset);
      return 0;
    } else if (next_four == 0b1110) {
      std::cout << "Unlist instruction" << std::endl;
      return 0;
    } else if (next_four == 0b1111) {
      std::cout << "Call to SWI: " << (instruction & 0b11111111) << std::endl;
      return 0;
    }
  }

  std::cout << "Undefined instruction to decode" << std::endl;
  return 2;

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