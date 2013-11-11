#ifndef VARLENGTHFIELD_HPP
#define VARLENGTHFIELD_HPP

#include <cstdint>
#include <vector>
#include <string>

enum fieldType { BINARY, BCDPLUS, ASCII6, LANGCODE };

struct typeLength {
  uint8_t length : 6;
  fieldType type : 2;
};

class varLengthField {
  std::vector<uint8_t> rawData;
  struct typeLength *data;
public:
  varLengthField();
  int getType();
  int getLength();
  std::string getString();
  void setString(std::string str);
  std::vector<uint8_t> getBinaryData();
  int size();
};

#endif /* VARLENGTHFIELD_HPP */