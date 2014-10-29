#include "amcPtPConnectivityRecord.hpp"
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <functional>
#include <sstream>

const uint8_t amcPtPConnectivityRecordPICMGRecordId = 0x19;
const uint8_t amcPtPConnectivityRecordFormatVersion = 0x00;
const uint8_t amcPtPConnectivityRecordType = 0x80;

amcPtPConnectivityRecord::amcPtPConnectivityRecord(std::list<amcChannelDescriptor> chDescrs, std::list<amcLinkDescriptor> lnkDescrs) :
  multiRecord::multiRecord(RECORD_TYPE_OEM, std::vector<uint8_t>())
{
  if(chDescrs.size() > UINT8_MAX) {
    std::stringstream ss;
    ss << "list chDescrs exceeds maximum allowed length of " << UINT8_MAX << " entries";
    throw std::length_error( ss.str() );
  }
  if(lnkDescrs.size() > UINT8_MAX) {
    std::stringstream ss;
    ss << "list lnkDescrs exceeds maximum allowed length of " << UINT8_MAX << " entries";
    throw std::length_error( ss.str() );
  }

  recordType = amcPtPConnectivityRecordType;
  m_ptPConnRecHeader.manufacturerId[2] = PICMG_MANUFACTURER_ID_MSB;
  m_ptPConnRecHeader.manufacturerId[1] = PICMG_MANUFACTURER_ID_MID;
  m_ptPConnRecHeader.manufacturerId[0] = PICMG_MANUFACTURER_ID_LSB;
  m_ptPConnRecHeader.picmgRecordId = amcPtPConnectivityRecordPICMGRecordId;
  m_ptPConnRecHeader.recordFormatVersion = amcPtPConnectivityRecordFormatVersion;
  m_ptPConnRecHeader.oemGuidCount = 0;

  m_amcChannelDescriptors = chDescrs;
  m_amcLinkDescriptors = lnkDescrs;
  
  updateRecordLength();
  m_payload = std::vector<uint8_t>( (uint8_t *)&m_ptPConnRecHeader, (uint8_t *)(&m_ptPConnRecHeader + 1) );
  m_payload.push_back( recordType );
  m_payload.push_back( m_amcChannelDescriptors.size() );
  
  for(std::list<amcChannelDescriptor>::const_iterator li = m_amcChannelDescriptors.begin(); li != m_amcChannelDescriptors.end(); li++) {
    std::vector<uint8_t> chDescriptor = li->getBinaryData();
    std::copy(chDescriptor.begin(), chDescriptor.end(), std::back_inserter(m_payload));
  }
  
  for(std::list<amcLinkDescriptor>::const_iterator li = m_amcLinkDescriptors.begin(); li != m_amcLinkDescriptors.end(); li++) {
    std::vector<uint8_t> lnkDescriptor = li->getBinaryData();
    std::copy(lnkDescriptor.begin(), lnkDescriptor.end(), std::back_inserter(m_payload));
  }
}

void amcPtPConnectivityRecord::updateRecordLength()
{
  int payloadSize = sizeof(m_ptPConnRecHeader);
  payloadSize += 2; // recordType and amcChannelDescriptorCount
  for(std::list<amcChannelDescriptor>::const_iterator li = m_amcChannelDescriptors.cbegin(); li != m_amcChannelDescriptors.cend(); li++) {
    payloadSize += li->size();
  }
  for(std::list<amcLinkDescriptor>::const_iterator li = m_amcLinkDescriptors.cbegin(); li != m_amcLinkDescriptors.cend(); li++) {
    payloadSize += li->size();
  }
  if(payloadSize > UINT8_MAX) {
    std::stringstream ss;
    ss << "Record length exceeds maximum allowed length of " << UINT8_MAX << " bytes!";
    throw std::length_error( ss.str() );
  }
  m_header.recordLength = payloadSize;
}

std::vector<uint8_t> amcPtPConnectivityRecord::getBinaryData() {
  return multiRecord::getBinaryData();
}

void amcPtPConnectivityRecord::printData() {
  updateRecordLength();
  updateRecordChecksum();
  updateHeaderChecksum();
  std::cout << "Record Type ID: 0x" << std::hex << (unsigned int)m_header.recordTypeId << std::endl;
  std::cout << "End of list: " << std::boolalpha << (bool)m_header.endOfList << std::endl;
  std::cout << "Record format version: " << std::dec << (unsigned int)m_header.recordFormatVersion << std::endl;
  std::cout << "Record length: " << std::dec << (unsigned int)m_header.recordLength << std::endl;
  std::cout << "Record checksum: 0x" << std::hex << (unsigned int)m_header.recordChecksum << std::endl;
  std::cout << "Header checksum: 0x" << std::hex << (unsigned int)m_header.headerChecksum << std::endl;
  const unsigned int manId = m_ptPConnRecHeader.manufacturerId[2] << 16 | m_ptPConnRecHeader.manufacturerId[1] << 8 | m_ptPConnRecHeader.manufacturerId[0];
  std::cout << "Manufacturer ID: 0x" << std::hex << manId << std::endl;
  std::cout << "PICMG Record ID: 0x" << std::hex << (unsigned int)m_ptPConnRecHeader.picmgRecordId << std::endl;
  std::cout << "Record Format Version: " << std::dec << (unsigned int)m_ptPConnRecHeader.recordFormatVersion << std::endl;
  std::cout << "OEM GUID Count: " << std::dec << (unsigned int)m_ptPConnRecHeader.oemGuidCount << std::endl;
  std::cout << "AMC Channel Descriptors: { " << std::endl;
  std::list<amcChannelDescriptor>::iterator cdli;
  int i;
  for(cdli = m_amcChannelDescriptors.begin(), i = 0; cdli != m_amcChannelDescriptors.end(); cdli++, i++) {
    std::cout << "AMC channel descriptor #" << std::dec << i << ":" << std::endl;
    cdli->printData();
  }
  std::cout << "}" << std::endl;

  std::cout << "AMC Link Descriptors: { " << std::endl;
  std::list<amcLinkDescriptor>::iterator ldli;
  for(ldli = m_amcLinkDescriptors.begin(), i = 0; ldli != m_amcLinkDescriptors.end(); ldli++, i++) {
    std::cout << "AMC link descriptor #" << std::dec << i << ":" << std::endl;
    ldli->printData();
  }
  std::cout << "}" << std::endl;
};

int amcPtPConnectivityRecord::size()
{
  updateRecordLength();
  return sizeof(m_header) + m_header.recordLength;
};