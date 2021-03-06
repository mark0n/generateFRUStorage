#ifndef AMCPTPCONNECTIVITYRECORD_HPP
#define AMCPTPCONNECTIVITYRECORD_HPP

#include "multiRecord.hpp"
#include "amcChannelDescriptor.hpp"
#include "amcLinkDescriptor.hpp"
#include <list>
#include <cstdint>

struct amcPtPConnectivityRecordHeader {
  uint8_t manufacturerId[3];
  uint8_t picmgRecordId;
  uint8_t recordFormatVersion;
  uint8_t oemGuidCount;
};

class amcPtPConnectivityRecord : public multiRecord {
  amcPtPConnectivityRecordHeader m_ptPConnRecHeader;
  uint8_t recordType;
  std::list<amcChannelDescriptor> m_amcChannelDescriptors;
  std::list<amcLinkDescriptor> m_amcLinkDescriptors;
public :
  amcPtPConnectivityRecord(std::list<amcChannelDescriptor> chDescrs, std::list<amcLinkDescriptor> lnkDescrs);
  void updateRecordLength();
  void addAMCChannelDescriptor(int lanePortNo[4]);
  std::vector<uint8_t> getBinaryData();
  void printData();
  int size();
};

#endif /* AMCPTPCONNECTIVITYRECORD_HPP */