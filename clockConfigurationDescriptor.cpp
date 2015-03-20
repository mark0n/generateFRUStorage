
#include "clockConfigurationDescriptor.hpp"
#include <iostream>

clockConfigurationDescriptor::clockConfigurationDescriptor(clockID ID, uint8_t control, std::list<indirectClockDescriptors> indirect, std::list<directClockDescriptors> direct) {
  
  
}

std::vector<uint8_t> clockConfigurationDescriptor::getBinaryData() const {
  return std::vector<uint8_t>( ( uint8_t * )&m_data, ( ( uint8_t * )&m_data ) + clockDescrDataSize );
}

void clockConfigurationDescriptor::printData() const {
}

int clockConfigurationDescripto::size() const {
  return clockDescrDataSize;
}