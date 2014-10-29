#include "varLengthLangCodeField.hpp"
#include <iostream>
#include <stdexcept>

varLengthLangCodeField::varLengthLangCodeField()
{
  m_header.type = LANGCODE;
  m_header.length = 0;
};

std::string varLengthLangCodeField::getString()
{
  return std::string(m_payload.cbegin(), m_payload.cend());
};

void varLengthLangCodeField::setString(std::string str)
{
  if(str.length() >= 64)
    throw std::runtime_error(std::string("Argument exceeds allowed length of 63 characters!"));
  m_header.length = str.size();
  m_payload = std::vector<uint8_t>(str.cbegin(), str.cend());
};