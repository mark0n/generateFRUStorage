#include "varLengthField.hpp"
#include <iostream>
#include <stdexcept>

std::vector<uint8_t> varLengthField::getBinaryData() {
  std::vector<uint8_t> rawData((uint8_t *)&header, (uint8_t *)(&header + 1));
  std::copy(payload.cbegin(), payload.cend(), std::back_inserter(rawData));
  return rawData;
}

int varLengthField::size()
{
  return sizeof(header) + payload.size();
}