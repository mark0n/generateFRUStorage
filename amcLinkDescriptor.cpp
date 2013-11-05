#include "amcLinkDescriptor.hpp"
#include <iostream>

amcLinkDescriptor::amcLinkDescriptor(amcLinkDesignator lnkDesignator, amcLinkType lnkType, int amcLinkTypeExtension, int linkGroupingId, int amcAsymmetricMatch) : rawData(amcLnkDescrDataSize) {
  data = (struct amcLnkDescrData *)rawData.data();
  data->amcLinkDesignator = lnkDesignator.laneFlag[3] << 11 | lnkDesignator.laneFlag[2] << 10 | lnkDesignator.laneFlag[1] << 9 | lnkDesignator.laneFlag[0] << 8 | lnkDesignator.channelId;
  data->amcLinkType = lnkType;
  data->amcLinkTypeExtension = amcLinkTypeExtension;
  data->amcLinkGroupingId = linkGroupingId;
  data->amcAsymmetricMatch = amcAsymmetricMatch;
  data->reserved = 0x3f;
}

std::vector<uint8_t> amcLinkDescriptor::getBinaryData() const {
  return rawData;
}

void amcLinkDescriptor::printData() const {
  std::cout << "AMC channel ID: " << std::dec << (data->amcLinkDesignator & 0x0f) << std::endl;
  for(int lane = 0; lane < 4; lane++) {
    std::cout << "Lane " << std::dec << lane << " bit flag: " << std::boolalpha << (bool)(data->amcLinkDesignator >> (8 + lane) & 0x01) << std::endl;
  }
  std::cout << "AMC link type: " << std::dec << (int)data->amcLinkType << std::endl;
  std::cout << "AMC link type extension: " << std::dec << (int)data->amcLinkTypeExtension << std::endl;
  std::cout << "AMC link grouping ID: " << std::dec << (int)data->amcLinkGroupingId << std::endl;
  std::cout << "AMC asymmetric match: " << std::dec << (int)data->amcAsymmetricMatch << std::endl;
}

int amcLinkDescriptor::size() const {
  return rawData.size();
}