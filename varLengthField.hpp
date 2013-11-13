#ifndef VARLENGTHFIELD_HPP
#define VARLENGTHFIELD_HPP

#include <cstdint>
#include <vector>
#include <string>

enum fieldType { BINARY, BCDPLUS, ASCII6, LANGCODE };

struct typeLength {
  uint8_t length : 6;
  uint8_t type : 2;
};

class varLengthField {
protected:
  struct typeLength header;
  std::vector<uint8_t> payload;
public:
  std::vector<uint8_t> getBinaryData();
  int size();
};

#endif /* VARLENGTHFIELD_HPP */