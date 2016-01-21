#include "clockConfigurationRecord.hpp"
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <functional>
#include <sstream>

const uint8_t clockConfigurationRecordPICMGRecordId = 0x2D;
const uint8_t clockConfigurationRecordFormatVersion = 0x00;

clockConfigurationRecord::clockConfigurationRecord(resourceIDResourceType rID, uint8_t dID, std::list<clockConfigurationDescriptor> clockDescriptors) :
  multiRecord::multiRecord(RECORD_TYPE_OEM, std::vector<uint8_t>())
{
  if(clockDescriptors.size() > UINT8_MAX)
  {
    std::stringstream ss;
    ss << "list clockDescriptors exceeds maximum allowed length of " << UINT8_MAX << " entries";
    throw std::length_error( ss.str() );
  }

  m_clockConfigurationHeader.manufacturerId[2] = PICMG_MANUFACTURER_ID_MSB;
  m_clockConfigurationHeader.manufacturerId[1] = PICMG_MANUFACTURER_ID_MID;
  m_clockConfigurationHeader.manufacturerId[0] = PICMG_MANUFACTURER_ID_LSB;
  m_clockConfigurationHeader.picmgRecordId = clockConfigurationRecordPICMGRecordId;
  m_clockConfigurationHeader.recordFormatVersion = clockConfigurationRecordFormatVersion;
  
  m_clockDescriptors = clockDescriptors;
  
  updateRecordLength();
  m_payload = std::vector<uint8_t>( (uint8_t *)&m_clockConfigurationHeader, (uint8_t *)(&m_clockConfigurationHeader + 1) );
  m_resourceIDDefinition.idType = rID;
  m_resourceIDDefinition.deviceID = dID;
  std::vector<uint8_t> resource = std::vector<uint8_t>( (uint8_t *)&m_resourceIDDefinition, (uint8_t *)(&m_resourceIDDefinition + 1) );
  m_payload.insert(m_payload.end(), resource.begin(), resource.end());
  m_payload.push_back( m_clockDescriptors.size() );
  
  for(std::list<clockConfigurationDescriptor>::const_iterator li = m_clockDescriptors.begin(); li != m_clockDescriptors.end(); li++) {
    std::vector<uint8_t> clockDescriptor = li->getBinaryData();
    std::copy(clockDescriptor.begin(), clockDescriptor.end(), std::back_inserter(m_payload));
  }
}

void clockConfigurationRecord::updateRecordLength()
{
  int payloadSize = sizeof(m_clockConfigurationHeader);
  payloadSize += 2;
  for(std::list<clockConfigurationDescriptor>::const_iterator li = m_clockDescriptors.cbegin(); li != m_clockDescriptors.cend(); li++) {
    payloadSize += li->size();
  }
  if(payloadSize > UINT8_MAX) {
    std::stringstream ss;
    ss << "Record length exceeds maximum allowed length of " << UINT8_MAX << " bytes!";
    throw std::length_error( ss.str() );
  }
  m_header.recordLength = payloadSize;
}

std::vector<uint8_t> clockConfigurationRecord::getBinaryData() {
  return multiRecord::getBinaryData();
}

void clockConfigurationRecord::printData() {
  updateRecordLength();
  updateRecordChecksum();
  updateHeaderChecksum();
  std::cout << "Record Type ID: 0x" << std::hex << (unsigned int)m_header.recordTypeId << std::endl;
  std::cout << "End of list: " << std::boolalpha << (bool)m_header.endOfList << std::endl;
  std::cout << "Record format version: " << std::dec << (unsigned int)m_header.recordFormatVersion << std::endl;
  std::cout << "Record length: " << std::dec << (unsigned int)m_header.recordLength << std::endl;
  std::cout << "Record checksum: 0x" << std::hex << (unsigned int)m_header.recordChecksum << std::endl;
  std::cout << "Header checksum: 0x" << std::hex << (unsigned int)m_header.headerChecksum << std::endl;
  const unsigned int manId = m_clockConfigurationHeader.manufacturerId[2] << 16 | m_clockConfigurationHeader.manufacturerId[1] << 8 | m_clockConfigurationHeader.manufacturerId[0];
  std::cout << "Manufacturer ID: 0x" << std::hex << manId << std::endl;
  std::cout << "PICMG Record ID: 0x" << std::hex << (unsigned int)m_clockConfigurationHeader.picmgRecordId << std::endl;
  std::cout << "Record Format Version: " << std::dec << (unsigned int)m_clockConfigurationHeader.recordFormatVersion << std::endl;
  std::cout << "Clock configuration descriptors: { " << std::endl;
  std::list<clockConfigurationDescriptor>::iterator cdli;
  int i;
  for(cdli = m_clockDescriptors.begin(), i = 0; cdli != m_clockDescriptors.end(); cdli++, i++)
  {
    std::cout << "Clock configuration descriptor #" << std::dec << i << ":" << std::endl;
    cdli->printData();
  }
  std::cout << "}" << std::endl;
};

int clockConfigurationRecord::size()
{
  updateRecordLength();
  return sizeof(m_header) + m_header.recordLength;
};