#ifndef MULTIRECORDAREA_HPP
#define MULTIRECORDAREA_HPP

#include "multiRecord.hpp"
#include "amcPtPConnectivityRecord.hpp"
#include "amcChannelDescriptor.hpp"
#include "amcLinkDescriptor.hpp"
#include <cstdint>
#include <vector>
#include <list>

typedef int channelDescriptorHandle;

class multiRecordArea {
  std::list<multiRecord *> records;
public :
  void addRecord(uint8_t typeId, std::vector<uint8_t> payload);
  void addAMCPtPConnectivityRecord(std::list<amcChannelDescriptor> chDescrs, std::list<amcLinkDescriptor> lnkDescrs);
  std::vector<uint8_t> getBinaryData();
  void printData();
  int size();
};

#endif /* MULTIRECORDAREA_HPP */