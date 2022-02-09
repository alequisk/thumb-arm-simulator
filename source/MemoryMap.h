#ifndef THUMB_MEMORY_H
#define THUMB_MEMORY_H

#include <map>
class MemoryMap {
  private:
    std::map<int, int> program_map;
    
  public:
    int fetchProgramInstruction(int pc);
    int fecthData(int addr);
    void setData(int addr, int value);
    MemoryMap(std::map<int, int> program_map);
    MemoryMap();
};

#endif