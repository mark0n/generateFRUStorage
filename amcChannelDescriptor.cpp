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
  data.portLane0 = port[0];
  data.portLane1 = port[1];
  data.portLane2 = port[2];
  data.portLane3 = port[3];
  data.pad = 0xf;
}

std::vector<uint8_t> amcChannelDescriptor::getBinaryData() const {
  std::vector<uint8_t> returnVec( (uint8_t *)&data, ( (uint8_t *)&data ) + amcChDescrDataSize);
  return returnVec;
}

void amcChannelDescriptor::printData() const {
  std::cout << "Lane 0 Port Number: " << data.portLane0 << std::endl;
  std::cout << "Lane 1 Port Number: " << data.portLane1 << std::endl;
  std::cout << "Lane 2 Port Number: " << data.portLane2 << std::endl;
  std::cout << "Lane 3 Port Number: " << data.portLane3 << std::endl;
}

int amcChannelDescriptor::size() const {
  return amcChDescrDataSize;
}