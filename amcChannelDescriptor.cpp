#include "amcChannelDescriptor.hpp"
#include <stdexcept>
#include <iostream>

amcChannelDescriptor::amcChannelDescriptor(const std::vector<int> port) {
  if( port.size() != 4 ) {
    throw std::runtime_error("Invalid number of entries in port vector (shall be 4).");
  }
  for(int lane = 0; lane < 4; lane++) {
    if(port[lane] < 0 || port[lane] > 31) {
      throw std::out_of_range("port number out of valid range");
    }
  }
  m_data.portLane0 = port[0];
  m_data.portLane1 = port[1];
  m_data.portLane2 = port[2];
  m_data.portLane3 = port[3];
  m_data.pad = 0xf;
}

std::vector<uint8_t> amcChannelDescriptor::getBinaryData() const {
  std::vector<uint8_t> returnVec( (uint8_t *)&m_data, ( (uint8_t *)&m_data ) + amcChDescrDataSize);
  return returnVec;
}

void amcChannelDescriptor::printData() const {
  std::cout << "Lane 0 Port Number: " << m_data.portLane0 << std::endl;
  std::cout << "Lane 1 Port Number: " << m_data.portLane1 << std::endl;
  std::cout << "Lane 2 Port Number: " << m_data.portLane2 << std::endl;
  std::cout << "Lane 3 Port Number: " << m_data.portLane3 << std::endl;
}

int amcChannelDescriptor::size() const {
  return amcChDescrDataSize;
}