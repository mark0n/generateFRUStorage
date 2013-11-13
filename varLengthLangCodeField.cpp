#include "varLengthLangCodeField.hpp"
#include <iostream>
#include <stdexcept>

varLengthLangCodeField::varLengthLangCodeField()
{
  header.type = LANGCODE;
  header.length = 0;
};

std::string varLengthLangCodeField::getString()
{
  return std::string(payload.cbegin(), payload.cend());
};

void varLengthLangCodeField::setString(std::string str)
{
  if(str.length() >= 64)
    throw std::runtime_error(std::string("Argument exceeds allowed length of 63 characters!"));
  header.length = str.size();
  payload = std::vector<uint8_t>(str.cbegin(), str.cend());
};