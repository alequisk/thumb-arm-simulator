#ifndef DECODER_THUMB_H
#define DECODER_THUMB_H

#include "MemoryMap.h"
enum OPERATORS {
  ADD,
  SUB
};


class Decoder {
  public:
    int decode(signed short int, int*, int*, MemoryMap*);
    bool checkOverflow(int, int, OPERATORS);
};

#endif