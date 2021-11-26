#ifndef THUMB_FILE_PARSER_H
#define THUMB_FILE_PARSER_H

#include <string>
#include <vector>

class FileParser {
  private:
    /** the filename of file to be read */
    std::string file_name;
    
    /** vector with address and instruction parsed */
    std::vector< std::pair<int, int> > program_parsed;

  public:
    FileParser( std::string );
    
    void handle();
    int string_to_hex( std::string );
    std::vector< std::pair<int, int>> get_program_mapped();
};

#endif