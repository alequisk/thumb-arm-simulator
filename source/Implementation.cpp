#include "Constants.h"
#include "Implementation.h"

#include <cstdint>

void ADC(int* regs, int* psr, int rd, int rm) {
  regs[rd] = regs[rd] + regs[rm] + ((psr[0] & CARRY_FLAG) != 0);
}

void ADD_regs(int* regs, int rd, int rm) {
  regs[rd] = regs[rd] + regs[rm];
}

void ADD_regs(int* regs, int rd, int rn, int rm) {
  regs[rd] = regs[rn] + regs[rm];
}

void ADD_immed(int* regs, int rd, int immed) {
  regs[rd] = regs[rd] + immed;
}

void ADD_immed(int* regs, int rd, int rm, int immed) {
  regs[rd] = regs[rm] + immed;
}

//TODO: needs to terminate adds.

void AND(int* regs, int rd, int rm) {
  regs[rd] = regs[rd] & regs[rm];  
}

void ASR_immed(int* regs, int* psr, int rd, int rm, int immed) {
  regs[rd] = regs[rm] >> immed;
  if ((regs[rm] >> (immed - 1)) & 0b1) {
    psr[0] |= CARRY_FLAG;
  } else {
    psr[0] &= ~CARRY_FLAG;
  }
}

void ASR_regs(int* regs, int* psr, int rd, int rs) {
  regs[rd] = regs[rd] >> regs[rs];
  if ((regs[rd] >> (regs[rs] - 1)) & 0b1) {
    psr[0] |= CARRY_FLAG;
  } else {
    psr[0] &= ~CARRY_FLAG;
  }
}

void BIC(int* regs, int rd, int rm) {
  regs[rd] &= ~regs[rm];
}

void CMN(int* regs, int* psr, int rn, int rm) {
  //TODO: set flags by sum values;
}

void CMP_regs(int* regs, int* psr, int rn, int rm) {
  //TODO: set flags by subtract values;
}

void CMP_immed(int* regs, int* psr, int rn, int immed) {
  //TODO: set flags by subtract values;
}

void CPY(int* regs, int rd, int rm) {
  regs[rd] = regs[rm];
}

void EOR(int* regs, int rd, int rm) {
  regs[rd] ^= regs[rm];
}

void LSL_immed(int* regs, int* psr, int rd, int rm, int immed) {
  regs[rd] = regs[rm] << immed;
  if ((regs[rm] >> (32 - immed)) & 0b1) {
    psr[0] |= CARRY_FLAG;
  } else {
    psr[0] &= ~CARRY_FLAG;
  }
}

void LSL_reg(int* regs, int* psr, int rd, int rs) {
  regs[rd] = regs[rd] << regs[rs];
  if ((regs[rd] >> (32 - regs[rs])) & 0b1) {
    psr[0] |= CARRY_FLAG;
  } else {
    psr[0] &= ~CARRY_FLAG;
  }
}

void LSR_immed(int* regs, int* psr, int rd, int rm, int immed) {
  regs[rd] = regs[rm] >> immed;
  if ((regs[rd] >> (immed - 1)) & 0b1) {
    psr[0] |= CARRY_FLAG;
  } else {
    psr[0] &= ~CARRY_FLAG;
  }
}

void LSR_reg(int* regs, int* psr, int rd, int rs) {
  regs[rd] = regs[rd] >> regs[rs];
  if ((regs[rd] >> (regs[rs] - 1)) & 0b1) {
    psr[0] |= CARRY_FLAG;
  } else {
    psr[0] &= ~CARRY_FLAG;
  }
}

void MOV_immed(int* regs, int rd, int immed) {
  regs[rd] = immed;
}

void MOV_regs(int* regs, int rd, int rm) {
  regs[rd] = regs[rm];
}

void MUL(int* regs, int rd, int rm) {
  int64_t a = regs[rd];
  int64_t b = regs[rm];
  
  int64_t result = a * b;
  regs[rd] = result & 0xffffffff;
}

void MVN(int* regs, int rd, int rm) {
  regs[rd] = ~regs[rm];
}

void NEG(int* regs, int rd, int rm) {
  regs[rd] = 0 - regs[rm];
}

void ORR(int* regs, int rd, int rm) {
  regs[rd] = regs[rd] | regs[rm];
}

void ROR(int* regs, int* psr, int rd, int rm) {
  regs[rd] = (regs[rd] >> regs[rm])|(regs[rd] << (32 - regs[rm]));
  if ((regs[rd] >> (regs[rm] - 1)) & 0b1) {
    psr[0] |= CARRY_FLAG;
  } else {
    psr[0] &= ~CARRY_FLAG;
  }
}

void SBC(int* regs, int* psr, int rd, int rm) {
  regs[rd] = regs[rd] - regs[rm] - !((psr[0] & CARRY_FLAG) != 0);
}

void SUB_immed(int* regs, int rd, int immed) {
  regs[rd] = regs[rd] - immed;
}

void SUB_immed(int* regs, int rd, int rm, int immed) {
  regs[rd] = regs[rm] - immed;
}

void SUB_regs(int* regs, int rd, int rm) {
  regs[rd] = regs[rd] - regs[rm];
}

void SUB_regs(int* regs, int rd, int rn, int rm) {
  regs[rd] = regs[rn] - regs[rm];
}

void TST(int* regs, int* psr, int rd, int rm) {
  //TODO: set flags of and
  int And = regs[rd] & regs[rm];
}

int Tbit(int a, int b) {
  return (a >> b) & 0b1;
}

void LDR(int* regs, int* mem, int rd, int addr) {
  regs[rd] = mem[addr];
}

void STR(int* regs, int* mem, int rd, int addr) {
  mem[addr] = regs[rd];
}

void LDRB(int* regs, int* mem, int rd, int addr) {
  regs[rd] = mem[addr] & 0xff;
}

void STRB(int* regs, int* mem, int rd, int addr) {
  mem[addr] = regs[rd] & 0xff;
}

void LDRH(int* regs, int* mem, int rd, int addr) {
  regs[rd] = mem[addr] & 0xffff;
}

void STRH(int* regs, int* mem, int rd, int addr) {
  mem[addr] = regs[rd] & 0xffff;
}

void LDRSB(int* regs, int* mem, int* psr, int rd, int addr) {
  //TODO: implement signal extend
  regs[rd] = mem[addr];
}

void STRSB(int* regs, int* mem, int* psr,int rd, int addr) {
  //TODO: implement signal extend
  mem[addr] = regs[rd];
}

