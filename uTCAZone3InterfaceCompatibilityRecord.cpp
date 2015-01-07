#include "uTCAZone3InterfaceCompatibilityRecord.hpp"
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <functional>
#include <sstream>

const uint8_t uTCAZone3InterfaceCompatibilityRecordPICMGRecordId = 0x30;
const uint8_t uTCAZone3InterfaceCompatibilityRecordFormatVersion = 0x01;

uTCAZone3InterfaceCompatibilityRecord::uTCAZone3InterfaceCompatibilityRecord(uint8_t interface, interfaceIdentifierBody body) :
  multiRecord::multiRecord(RECORD_TYPE_OEM, std::vector<uint8_t>())
{

  m_interfaceHeader.manufacturerId[2] = PICMG_MANUFACTURER_ID_MSB;
  m_interfaceHeader.manufacturerId[1] = PICMG_MANUFACTURER_ID_MID;
  m_interfaceHeader.manufacturerId[0] = PICMG_MANUFACTURER_ID_LSB;
  m_interfaceHeader.picmgRecordId = uTCAZone3InterfaceCompatibilityRecordPICMGRecordId;
  m_interfaceHeader.recordFormatVersion = uTCAZone3InterfaceCompatibilityRecordFormatVersion;
  m_interfaceHeader.interfaceIdentifier = interface;
  bodySize = body.size();
  updateRecordLength();
  m_payload = std::vector<uint8_t>( (uint8_t *)&m_interfaceHeader, (uint8_t *)(&m_interfaceHeader + 1) );
  
  std::vector<uint8_t> interfaceBody = body.getBinaryData();
  std::copy(interfaceBody.begin(), interfaceBody.end(), std::back_inserter(m_payload));
}

void uTCAZone3InterfaceCompatibilityRecord::updateRecordLength()
{
  int payloadSize = sizeof(m_interfaceHeader);
  payloadSize += bodySize; // interface identifier

  if(payloadSize > UINT8_MAX) {
    std::stringstream ss;
    ss << "Record length exceeds maximum allowed length of " << UINT8_MAX << " bytes!";
    throw std::length_error( ss.str() );
  }
  m_header.recordLength = payloadSize;
}

std::vector<uint8_t> uTCAZone3InterfaceCompatibilityRecord::getBinaryData() {
  return multiRecord::getBinaryData();
}

void uTCAZone3InterfaceCompatibilityRecord::printData() {
  updateRecordLength();
  updateRecordChecksum();
  updateHeaderChecksum();
  std::cout << "Record Type ID: 0x" << std::hex << (unsigned int)m_header.recordTypeId << std::endl;
  std::cout << "End of list: " << std::boolalpha << (bool)m_header.endOfList << std::endl;
  std::cout << "Record format version: " << std::dec << (unsigned int)m_header.recordFormatVersion << std::endl;
  std::cout << "Record length: " << std::dec << (unsigned int)m_header.recordLength << std::endl;
  std::cout << "Record checksum: 0x" << std::hex << (unsigned int)m_header.recordChecksum << std::endl;
  std::cout << "Header checksum: 0x" << std::hex << (unsigned int)m_header.headerChecksum << std::endl;
  const unsigned int manId = m_interfaceHeader.manufacturerId[2] << 16 | m_interfaceHeader.manufacturerId[1] << 8 | m_interfaceHeader.manufacturerId[0];
  std::cout << "Manufacturer ID: 0x" << std::hex << manId << std::endl;
  std::cout << "PICMG Record ID: 0x" << std::hex << (unsigned int)m_interfaceHeader.picmgRecordId << std::endl;
  std::cout << "Record Format Version: " << std::dec << (unsigned int)m_interfaceHeader.recordFormatVersion << std::endl;
};

int uTCAZone3InterfaceCompatibilityRecord::size()
{
  updateRecordLength();
  return sizeof(m_header) + m_header.recordLength;
};
