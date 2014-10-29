#include "amcLinkDescriptor.hpp"
#include <iostream>

amcLinkDescriptor::amcLinkDescriptor(amcLinkDesignator lnkDesignator, amcLinkType lnkType, int amcLinkTypeExtension, int linkGroupingId, int amcAsymmetricMatch) {
  m_data.amcLinkDesignator = lnkDesignator.laneFlag[3] << 11 |
                           lnkDesignator.laneFlag[2] << 10 |
                           lnkDesignator.laneFlag[1] << 9 |
                           lnkDesignator.laneFlag[0] << 8 |
                           lnkDesignator.channelId;
  m_data.amcLinkType = lnkType;
  m_data.amcLinkTypeExtension = amcLinkTypeExtension;
  m_data.amcLinkGroupingId = linkGroupingId;
  m_data.amcAsymmetricMatch = amcAsymmetricMatch;
  m_data.reserved = 0x3f;
}

std::vector<uint8_t> amcLinkDescriptor::getBinaryData() const {
  return std::vector<uint8_t>( ( uint8_t * )&m_data, ( ( uint8_t * )&m_data ) + amcLnkDescrDataSize );
}

void amcLinkDescriptor::printData() const {
  std::cout << "AMC channel ID: " << std::dec << (m_data.amcLinkDesignator & 0x0f) << std::endl;
  for(int lane = 0; lane < 4; lane++) {
    std::cout << "Lane " << std::dec << lane << " bit flag: " << std::boolalpha << (bool)(m_data.amcLinkDesignator >> (8 + lane) & 0x01) << std::endl;
  }
  std::cout << "AMC link type: " << std::dec << (int)m_data.amcLinkType << std::endl;
  std::cout << "AMC link type extension: " << std::dec << (int)m_data.amcLinkTypeExtension << std::endl;
  std::cout << "AMC link grouping ID: " << std::dec << (int)m_data.amcLinkGroupingId << std::endl;
  std::cout << "AMC asymmetric match: " << std::dec << (int)m_data.amcAsymmetricMatch << std::endl;
}

int amcLinkDescriptor::size() const {
  return amcLnkDescrDataSize;
}