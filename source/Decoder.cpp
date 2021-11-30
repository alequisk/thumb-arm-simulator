#include "Decoder.h"

std::string Decoder::decode(int instruction) {
  if (((instruction >> 12) & 0b1111) == 0b0000) {
    if (((instruction >> 11) & 0b1) == 0b0) {
      return "LSL";
    } else {
      return "LSR";
    }
  }

  return "undefined";
}