#include "varLengthField.hpp"
#include <iostream>
#include <stdexcept>

std::vector<uint8_t> varLengthField::getBinaryData() {
  std::vector<uint8_t> rawData((uint8_t *)&m_header, (uint8_t *)(&m_header + 1));
  std::copy(m_payload.cbegin(), m_payload.cend(), std::back_inserter(rawData));
  return rawData;
}

int varLengthField::size()
{
  return sizeof(m_header) + m_payload.size();
}