#ifndef DECODER_THUMB_H
#define DECODER_THUMB_H

enum OPERATORS {
  ADD,
  SUB
};

class Decoder {
  public:
    void decode(signed short int, int*, int*);
    bool checkOverflow(int, int, OPERATORS);
};

#endif