#ifndef AMCCHANNELDESCRIPTOR_HPP
#define AMCCHANNELDESCRIPTOR_HPP

#include <cstdint>
#include <vector>

struct amcChDescrData {
  uint32_t portLane0 : 5;
  uint32_t portLane1 : 5;
  uint32_t portLane2 : 5;
  uint32_t portLane3 : 5;
  uint32_t pad : 4;
};

class amcChannelDescriptor {
  std::vector<uint8_t> rawData;
  amcChDescrData *data;
//   std::vector<uint8_t> headerRawData;
//   struct multiRecordHeader *header;
//   std::vector<uint8_t> payload;
//   void updateRecordChecksum();
//   void updateHeaderChecksum();
public :
  amcChannelDescriptor(const int port[4]);
//   std::list<amcChannelDescriptor> amcChannelDescriptors;
//   multiRecord();
//   void amcPtPConnectivityRecord();
//   addAMCChannelDescriptor(int lanePortNo[4]);
//   multiRecord(uint8_t typeId, std::vector<uint8_t> payload);
//   uint8_t getFormatVersion();
//   uint8_t getEndOfList();
//   void setEndOfList(bool endOfList);
//   uint8_t getRecordLength();
//   uint8_t getChecksum();
//   uint8_t getHeaderChecksum();
  std::vector<uint8_t> getBinaryData() const;
  void printData() const;
  int size() const;
};

#endif /* AMCCHANNELDESCRIPTOR_HPP */