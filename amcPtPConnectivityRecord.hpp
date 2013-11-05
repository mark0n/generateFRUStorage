#ifndef AMCPTPCONNECTIVITYRECORD_HPP
#define AMCPTPCONNECTIVITYRECORD_HPP

#include "multiRecord.hpp"
#include "amcChannelDescriptor.hpp"
#include "amcLinkDescriptor.hpp"
#include <list>

struct amcPtPConnectivityRecordHeader {
  uint8_t manufacturerId[3];
  uint8_t picmgRecordId;
  uint8_t recordFormatVersion;
  uint8_t oemGuidCount;
};

class amcPtPConnectivityRecord : public multiRecord {
  std::vector<uint8_t> ptPConnRecHeaderRawData;
  amcPtPConnectivityRecordHeader *ptPConnRecHeader;
  uint8_t recordType;
  std::list<amcChannelDescriptor> amcChannelDescriptors;
  std::list<amcLinkDescriptor> amcLinkDescriptors;
//   std::vector<uint8_t> headerRawData;
//   struct multiRecordHeader *header;
//   std::vector<uint8_t> payload;
//   void updateRecordChecksum();
//   void updateHeaderChecksum();
public :
  amcPtPConnectivityRecord(std::list<amcChannelDescriptor> chDescrs, std::list<amcLinkDescriptor> lnkDescrs);
  void addAMCChannelDescriptor(int lanePortNo[4]);
//   multiRecord();
//   addAMCChannelDescriptor(int lanePortNo[4]);
//   multiRecord(uint8_t typeId, std::vector<uint8_t> payload);
//   uint8_t getFormatVersion();
//   uint8_t getEndOfList();
//   void setEndOfList(bool endOfList);
//   uint8_t getRecordLength();
//   uint8_t getChecksum();
//   uint8_t getHeaderChecksum();
  std::vector<uint8_t> getBinaryData();
  void printData();
//   int size();
};

#endif /* AMCPTPCONNECTIVITYRECORD_HPP */