#ifndef THUMB_IMPLEMENTATION_H
#define THUMB_IMPLEMENTATION_H

#include "MemoryMap.h"

/*** ARITHMETRICS ***/
void ADC(int* regs, int* psr, int rd, int rm);
void ADD_regs(int* regs, int rd, int rm);
void ADD_regs(int* regs, int rd, int rn, int rm);
void ADD_immed(int* regs, int rd, int immed);
void ADD_immed(int* regs, int rd, int rm, int immed);
void AND(int* regs, int rd, int rm);
void ASR_immed(int* regs, int* psr, int rd, int rm, int immed);
void ASR_regs(int* regs, int* psr, int rd, int rs);
void BIC(int* regs, int rd, int rm);
void CMN(int* regs, int* psr, int rn, int rm);
void CMP_regs(int* regs, int* psr, int rn, int rm);
void CMP_immed(int* regs, int* psr, int rn, int immed);
void CPY(int* regs, int rd, int rm);
void EOR(int* regs, int rd, int rm);
void LSL_immed(int* regs, int* psr, int rd, int rm, int immed);
void LSL_reg(int* regs, int* psr, int rd, int rs);
void LSR_immed(int* regs, int* psr, int rd, int rm, int immed);
void LSR_reg(int* regs, int* psr, int rd, int rs);
void MOV_immed(int* regs, int rd, int immed);
void MOV_regs(int* regs, int rd, int rm);
void MUL(int* regs, int rd, int rm);
void MVN(int* regs, int rd, int rm);
void NEG(int* regs, int rd, int rm);
void ORR(int* regs, int rd, int rm);
void ROR(int* regs, int* psr, int rd, int rm);
void SBC(int* regs, int* psr, int rd, int rm);
void SUB_immed(int* regs, int rd, int immed);
void SUB_immed(int* regs, int rd, int rm, int immed);
void SUB_regs(int* regs, int rd, int rm);
void SUB_regs(int* regs, int rd, int rn, int rm);
void TST(int* regs, int* psr, int rd, int rm);
int Tbit(int a, int b);

/*** LOAD/STORE ***/
void LDR(int* regs, MemoryMap* mem, int rd, int addr);
void STR(int* regs, MemoryMap* mem, int rd, int addr);
void LDRB(int* regs, MemoryMap* mem, int rd, int addr);
void STRB(int* regs, MemoryMap* mem, int rd, int addr);
void LDRH(int* regs, MemoryMap* mem, int rd, int addr);
void STRH(int* regs, MemoryMap* mem, int rd, int addr);
void LDRSB(int* regs, MemoryMap* mem, int* psr, int rd, int addr);
void STRSB(int* regs, MemoryMap* mem, int* psr,int rd, int addr);

void BX(int* regs, int* psr, int rm);
void BLX_regs(int* regs, int* psr, int rm);
void BHI(int *regs, int* psr, int offset);
void BLS(int* regs, int* psr, int offset);
void BGE(int* regs, int* psr, int offset);
void BLT(int* regs, int* psr, int offset);
void BGT(int* regs, int* psr, int offset);
void BLE(int* regs, int* psr, int offset);
void BAL(int* regs, int* psr, int offset);
void BEQ(int* regs, int* psr, int offset);
void BNE(int* regs, int* psr, int offset);
void BHS(int* regs, int* psr, int offset);
void BLO(int* regs, int* psr, int offset);

void BMI(int* regs, int* psr, int offset);
void BPL(int* regs, int* psr, int offset);
void BVS(int* regs, int* psr, int offset);
void BVC(int* regs, int* psr, int offset);

#endif