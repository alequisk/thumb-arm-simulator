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
    int r[7];

  public:
    Core();
    void run();
    void load_program();
    void describe();
    std::string ps_to_string(int);
  
};

#endif