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
  int result = regs[rn] - immed;
  
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

void LDR(int* regs, MemoryMap* mem, int rd, int addr) {
  regs[rd] = mem->fecthData(addr);
}

void STR(int* regs, MemoryMap* mem, int rd, int addr) {
  mem->setData(addr, regs[rd]);
}

void LDRB(int* regs, MemoryMap* mem, int rd, int addr) {
  regs[rd] = mem->fecthData(addr) & 0xff;
}

void STRB(int* regs, MemoryMap* mem, int rd, int addr) {
  mem->setData(addr, regs[rd] & 0xff);
}

void LDRH(int* regs, MemoryMap* mem, int rd, int addr) {
  regs[rd] = mem->fecthData(addr) & 0xffff;
}

void STRH(int* regs, MemoryMap* mem, int rd, int addr) {
  mem->setData(addr, regs[rd] & 0xffff);
}

void LDRSB(int* regs, MemoryMap* mem, int* psr, int rd, int addr) {
  //TODO: implement signal extend
  regs[rd] = mem->fecthData(addr);
}

void STRSB(int* regs, MemoryMap* mem, int* psr,int rd, int addr) {
  //TODO: implement signal extend
  mem->setData(addr, regs[rd]);
}

void BX(int* regs, int* psr, int rm) {
  regs[15] = regs[rm] & 0xfffffffe;
  if ((regs[rm] & 0b1) == 0b1) {
    psr[0] |= THUMB_MODE;
  } else {
    psr[0] &= ~THUMB_MODE;
  }
}

void BLX_regs(int* regs, int* psr, int rm) {
  regs[15] = regs[rm] & 0xfffffffe;
  regs[14] = regs[15] + 2;
  if ((regs[rm] & 0b1) == 0b1) {
    psr[0] |= THUMB_MODE;
  } else {
    psr[0] &= ~THUMB_MODE;
  }
}

void BHI(int *regs, int* psr, int offset) {
  if ((psr[0] & ZERO_FLAG) == 0 && (psr[0] & CARRY_FLAG) != 0) {
    regs[15] = regs[15] + 4 + offset * 2;
  }
}

void BLS(int* regs, int* psr, int offset) {
  if ((psr[0] & ZERO_FLAG) != 0 || (psr[0] & CARRY_FLAG) == 0) {
    regs[15] = regs[15] + 4 + offset * 2;
  }
}

void BGE(int* regs, int* psr, int offset) {
  if (((psr[0] & NEGATIVE_FLAG) != 0 && (psr[0] & OVERFLOW_FLAG) != 0) || ((psr[0] & NEGATIVE_FLAG) == 0 && (psr[0] & OVERFLOW_FLAG) == 0)) {
    regs[15] = regs[15] + 4 + offset * 2;
  }
}

void BLT(int* regs, int* psr, int offset) {
  if (((psr[0] & NEGATIVE_FLAG) != 0 && (psr[0] & OVERFLOW_FLAG) == 0) || ((psr[0] & NEGATIVE_FLAG) == 0 && (psr[0] & OVERFLOW_FLAG) != 0)) {
    regs[15] = regs[15] + 4 + offset * 2;
  }
}

void BGT(int* regs, int* psr, int offset) {
  if (((psr[0] & NEGATIVE_FLAG) != 0 && (psr[0] & OVERFLOW_FLAG) != 0 && (psr[0] & ZERO_FLAG) == 0) || ((psr[0] & NEGATIVE_FLAG) == 0 && (psr[0] & OVERFLOW_FLAG) == 0 && (psr[0] & ZERO_FLAG) == 0)) {
    regs[15] = regs[15] + 4 + offset * 2;
  }
}

void BLE(int* regs, int* psr, int offset) {
  if ((psr[0] & ZERO_FLAG) != 0 || ((psr[0] & NEGATIVE_FLAG) != 0 && (psr[0] & OVERFLOW_FLAG) == 0) || ((psr[0] & NEGATIVE_FLAG) == 0 && (psr[0] & OVERFLOW_FLAG) != 0)) {
    regs[15] = regs[15] + 4 + offset * 2;
  }
}

void BAL(int* regs, int* psr, int offset) {
  regs[15] = regs[15] + 4 + offset * 2;
}

void BEQ(int* regs, int* psr, int offset) {
  if ((psr[0] & ZERO_FLAG) != 0) {
    regs[15] = regs[15] + 4 + offset * 2;
  }
}

void BNE(int* regs, int* psr, int offset) {
  if ((psr[0] & ZERO_FLAG) == 0) {
    regs[15] = regs[15] + 4 + offset * 2;
  }
}

void BHS(int* regs, int* psr, int offset) {
  if ((psr[0] & CARRY_FLAG) != 0) {
    regs[15] = regs[15] + 4 + offset * 2;
  }
}

void BLO(int* regs, int* psr, int offset) {
  if ((psr[0] & CARRY_FLAG) == 0) {
    regs[15] = regs[15] + 4 + offset * 2;
  }
}

void BMI(int* regs, int* psr, int offset) {
  if ((psr[0] & NEGATIVE_FLAG) != 0) {
    regs[15] = regs[15] + 4 + offset * 2;
  }
}

void BPL(int* regs, int* psr, int offset) {
  if ((psr[0] & NEGATIVE_FLAG) == 0) {
    regs[15] = regs[15] + 4 + offset * 2;
  }
}

void BVS(int* regs, int* psr, int offset) {
  if ((psr[0] & OVERFLOW_FLAG) != 0) {
    regs[15] = regs[15] + 4 + offset * 2;
  }
}

void BVC(int* regs, int* psr, int offset) {
  if ((psr[0] & OVERFLOW_FLAG) == 0) {
    regs[15] = regs[15] + 4 + offset * 2;
  }
}

