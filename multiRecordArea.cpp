#include "multiRecordArea.hpp"
#include <iostream>

void multiRecordArea::addRecord(uint8_t typeId, std::vector<uint8_t> payload) {
  multiRecord *newRecord = new multiRecord(typeId, payload);
  newRecord->setEndOfList(true);
  if(!records.empty()) {
    records.back()->setEndOfList(false);
  }
  records.push_back(newRecord);
};

std::vector<uint8_t> multiRecordArea::getBinaryData() {
  std::list<multiRecord *>::iterator li;
  std::vector<uint8_t> rawData;
  for(li = records.begin(); li != records.end(); li++) {
    std::vector<uint8_t> recordRawData = (*li)->getBinaryData();
    rawData.insert(rawData.end(), recordRawData.begin(), recordRawData.end());
  }
  return rawData;
};

void multiRecordArea::printData() {
  std::list<multiRecord *>::iterator li;
  for(li = records.begin(); li != records.end(); li++) {
    std::cout << "MULTI RECORD:" << std::endl;
    (*li)->printData();
  }
};

int multiRecordArea::size() {
  std::list<multiRecord *>::iterator li;
  int sum = 0;
  for(li = records.begin(); li != records.end(); li++)
    sum += (*li)->size();
  return sum;
};