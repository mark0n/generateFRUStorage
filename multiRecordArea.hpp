#ifndef MULTIRECORDAREA_HPP
#define MULTIRECORDAREA_HPP

#include "multiRecord.hpp"
#include <cstdint>
#include <vector>
#include <list>

enum recordType { ON_CARRIER_DEVICE, AMC_MODULE };

class multiRecordArea {
  std::list<multiRecord *> records;
public :
  void addRecord(uint8_t typeId, std::vector<uint8_t> payload);
  std::vector<uint8_t> getBinaryData();
  void printData();
  int size();
};

#endif /* MULTIRECORDAREA_HPP */