#ifndef AMCLINKDESCRIPTOR_HPP
#define AMCLINKDESCRIPTOR_HPP

#include <cstdint>
#include <vector>

struct amcLnkDescrData {
  uint32_t amcLinkDesignator : 12;
  uint32_t amcLinkType : 8;
  uint32_t amcLinkTypeExtension : 4;
  uint32_t amcLinkGroupingId : 8;
  uint8_t amcAsymmetricMatch : 2;
  uint8_t reserved : 6;
};

const int amcLnkDescrDataSize = 5;

struct amcLinkDesignator {
  uint8_t channelId;
  bool laneFlag[4];
};

enum amcLinkType {
  AMC1PCIe = 0x02,
  AMC1PCIeAdvancedSwitching3 = 0x03,
  AMC1PCIeAdvancedSwitching4 = 0x04,
  AMC2Ethernet = 0x05,
  AMC4SerialRapidIO = 0x06,
  AMC3Storage = 0x07
};

class amcLinkDescriptor {
  std::vector<uint8_t> rawData;
  struct amcLnkDescrData *data;
public :
  amcLinkDescriptor(struct amcLinkDesignator, amcLinkType lnkType, int amcLinkTypeExtension, int linkGroupingId, int amcSymmetricMatch);
  std::vector<uint8_t> getBinaryData() const;
  void printData() const;
  int size() const;
};

#endif /* AMCLINKDESCRIPTOR_HPP */