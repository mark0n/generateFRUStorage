#include "multiRecord.hpp"
#include "checksum.hpp"
#include <iostream>

multiRecord::multiRecord(uint8_t typeId, std::vector<uint8_t> payload) : headerRawData(sizeof(*header)) {
  header = (struct multiRecordHeader *)headerRawData.data();
  header->recordTypeId = typeId;
  header->recordFormatVersion = 2;
  header->recordLength = payload.size();
  this->payload = payload;
};

void multiRecord::updateRecordChecksum() {
  header->recordChecksum = -calcChecksum(payload.cbegin(), payload.cend()) & 0xff;
};

void multiRecord::updateHeaderChecksum() {
  updateAreaChecksum(headerRawData.begin(), headerRawData.end());
};

uint8_t multiRecord::getFormatVersion() { return header->recordFormatVersion; };
uint8_t multiRecord::getEndOfList() { return header->endOfList; };
void multiRecord::setEndOfList(bool endOfList) { header->endOfList = endOfList; };
uint8_t multiRecord::getRecordLength() { return header->recordLength; };
uint8_t multiRecord::getChecksum() { updateRecordChecksum(); return header->recordChecksum; };

uint8_t multiRecord::getHeaderChecksum() {
  updateRecordChecksum();
  updateHeaderChecksum();
  return header->headerChecksum;
};

std::vector<uint8_t> multiRecord::getBinaryData() {
  updateRecordChecksum();
  updateHeaderChecksum();
  
  std::vector<uint8_t> rawData(headerRawData.begin(), headerRawData.end());
  std::copy(payload.begin(), payload.end(), std::back_inserter(rawData));
  return rawData;
};

void multiRecord::printData() {
  updateRecordChecksum();
  updateHeaderChecksum();
  std::cout << "Record Type ID: 0x" << std::hex << (unsigned int)header->recordTypeId << std::endl;
  std::cout << "End of list: " << std::boolalpha << (bool)header->endOfList << std::endl;
  std::cout << "Record format version: " << std::dec << (unsigned int)header->recordFormatVersion << std::endl;
  std::cout << "Record length: " << std::dec << (unsigned int)header->recordLength << std::endl;
  std::cout << "Record checksum: 0x" << std::hex << (unsigned int)header->recordChecksum << std::endl;
  std::cout << "Header checksum: 0x" << std::hex << (unsigned int)header->headerChecksum << std::endl;
  std::cout << "Payload: { ";
  for(std::vector<uint8_t>::iterator vi = payload.begin(); vi != payload.end(); vi++) {
    std::cout << "0x" << std::hex << (unsigned int)*vi << " ";
  }
  std::cout << "}" << std::endl;
};

int multiRecord::size() { return sizeof(*header) + payload.size(); };