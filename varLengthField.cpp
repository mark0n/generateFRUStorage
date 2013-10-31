#include "varLengthField.hpp"
#include <iostream>
#include <stdexcept>

varLengthField::varLengthField() : rawData(1) {}

std::string varLengthField::getString() {
  std::string str;
  data = (struct typeLength *)rawData.data();
  if(data->length > 0)
    str = std::string(++rawData.begin(), rawData.end());
  return str;
}

void varLengthField::setString(const std::string str) {
  if(str.length() >= 64)
    throw std::runtime_error(std::string("Argument exceeds allowed length of 63 characters!"));
  rawData.resize(str.length() + 1);
  data = (struct typeLength *)rawData.data();
  data->type = LANGCODE;
  data->length = (int)str.length();
  std::copy(str.begin(), str.end(), ++rawData.begin());
}

std::vector<uint8_t> varLengthField::getBinaryData() {
  return rawData;
}