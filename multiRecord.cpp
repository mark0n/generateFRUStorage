#include "multiRecord.hpp"
#include "checksum.hpp"
#include <iostream>
#include <sstream>

multiRecord::multiRecord(uint8_t typeId, std::vector<uint8_t> payload) {
  if(payload.size() > UINT8_MAX) {
    std::stringstream ss;
    ss << "Payload data exceeds allowed length of " << UINT8_MAX << " bytes!";
    throw std::runtime_error(ss.str());
  }
  m_header.recordTypeId = typeId;
  m_header.recordFormatVersion = 2;
  m_header.reserved = 0;
  m_header.endOfList = 0;
  m_header.recordLength = payload.size();
  this->m_payload = payload;
};

void multiRecord::updateRecordChecksum() {
  m_header.recordChecksum = -calcChecksum(m_payload.cbegin(), m_payload.cend()) & 0xff;
};

void multiRecord::updateHeaderChecksum() {
  updateAreaChecksum( (uint8_t *)&m_header, (uint8_t *)(&m_header + 1) );
};

uint8_t multiRecord::getFormatVersion() { return m_header.recordFormatVersion; };
uint8_t multiRecord::getEndOfList() { return m_header.endOfList; };
void multiRecord::setEndOfList(bool endOfList) { m_header.endOfList = endOfList; };
uint8_t multiRecord::getRecordLength() { return m_header.recordLength; };
uint8_t multiRecord::getChecksum() { updateRecordChecksum(); return m_header.recordChecksum; };

uint8_t multiRecord::getHeaderChecksum() {
  updateRecordChecksum();
  updateHeaderChecksum();
  return m_header.headerChecksum;
};

std::vector<uint8_t> multiRecord::getBinaryData() {
  updateRecordChecksum();
  updateHeaderChecksum();
  
  std::vector<uint8_t> rawData( (uint8_t *)&m_header, (uint8_t *)(&m_header + 1) );
  std::copy(m_payload.begin(), m_payload.end(), std::back_inserter(rawData));
  return rawData;
};

void multiRecord::printData() {
  updateRecordChecksum();
  updateHeaderChecksum();
  std::cout << "Record Type ID: 0x" << std::hex << (unsigned int)m_header.recordTypeId << std::endl;
  std::cout << "End of list: " << std::boolalpha << (bool)m_header.endOfList << std::endl;
  std::cout << "Record format version: " << std::dec << (unsigned int)m_header.recordFormatVersion << std::endl;
  std::cout << "Record length: " << std::dec << (unsigned int)m_header.recordLength << std::endl;
  std::cout << "Record checksum: 0x" << std::hex << (unsigned int)m_header.recordChecksum << std::endl;
  std::cout << "Header checksum: 0x" << std::hex << (unsigned int)m_header.headerChecksum << std::endl;
  std::cout << "Payload: { ";
  for(std::vector<uint8_t>::iterator vi = m_payload.begin(); vi != m_payload.end(); vi++) {
    std::cout << "0x" << std::hex << (unsigned int)*vi << " ";
  }
  std::cout << "}" << std::endl;
};

int multiRecord::size() { return sizeof(m_header) + m_payload.size(); };