#ifndef THUMB_CORE_H
#define THUMB_CORE_H

#include <string>
#include "Decoder.h"

class Core {
   private:
    /** current program status register */
    int cpsr;

    /** save program status register */
    int spsr;
    
    /** general purpose registers */
    int r[16];

    /** Decoder */
    Decoder decoder;
    
  public:
    Core();
    void run();
    void run_instruction(short int);
    void load_program();
    void describe();
    std::string ps_to_string(int);
  
};

#endif