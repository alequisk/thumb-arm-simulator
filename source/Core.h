#ifndef THUMB_CORE_H
#define THUMB_CORE_H

#include <string>

#define STACK_POINTER_ADDRESS   0x82000000

#define PROGRAM_MEM_ADDRESS     0x80000000
#define PROGRAM_MEM_SIZE        2048

#define DATA_MEM_ADDRESS        0x00000000

#define SUPERVISOR_MODE         0x00000013
#define THUMB_MODE              0x00000020
#define JAZEL_MODE              0x00800000
#define FAST_INTERRUPTION_MODE  0x00000040
#define INTERRUPTION_MODE       0x00000080

#define NEGATIVE_FLAG           0x80000000
#define ZERO_FLAG               0x40000000
#define CARRY_FLAG              0x20000000
#define OVERFLOW_FLAG           0x10000000
#define SATURATED_FLAG          0x08000000

class Core {
   private:
    /** program count */
    int pc;

    /** link register */
    int lr;

    /** stack pointer */
    int sp;

    /** current program status register */
    int cpsr;

    /** save program status register */
    int spsr;
    
    /** general purpose registers */
    int r0, r1, r2, r3, r4, r5, r6, r7;

  public:
    Core():
      pc(PROGRAM_MEM_ADDRESS), lr(0), sp(STACK_POINTER_ADDRESS), cpsr(SUPERVISOR_MODE | THUMB_MODE),
      spsr(0), r0(0), r1(0), r2(0), r3(0), r4(0), r5(0), r6(0), r7(0) {}
    
    void run();
    void load_program();
    void describe();
    std::string ps_to_string(int);
  
};

#endif