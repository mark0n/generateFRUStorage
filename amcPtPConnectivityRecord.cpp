#include "amcPtPConnectivityRecord.hpp"
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <functional>

#define RECORD_TYPE_OEM 0xc0
#define PICMG_MANUFACTURER_ID_MSB 0x00
#define PICMG_MANUFACTURER_ID_MID 0x31
#define PICMG_MANUFACTURER_ID_LSB 0x5a
#define PICMG_RECORD_ID 0x19
#define AMC_PTP_CONNECTIVITY_RECORD_FORMAT_VERSION 0x00
#define AMC_PTP_CONNECTIVITY_RECORD_TYPE 0x80

amcPtPConnectivityRecord::amcPtPConnectivityRecord(std::list<amcChannelDescriptor> chDescrs, std::list<amcLinkDescriptor> lnkDescrs) :
  multiRecord::multiRecord(RECORD_TYPE_OEM, std::vector<uint8_t>()),
  ptPConnRecHeaderRawData(sizeof(*ptPConnRecHeader))
{
  header = (struct multiRecordHeader *)headerRawData.data();
  ptPConnRecHeader = (struct amcPtPConnectivityRecordHeader *)ptPConnRecHeaderRawData.data();
  if(chDescrs.size() > 255) {
    throw std::length_error("list chDescrs exceeds maximum allowed length of 255 entries");
  }
  if(lnkDescrs.size() > 255) {
    throw std::length_error("list lnkDescrs exceeds maximum allowed length of 255 entries");
  }

  ptPConnRecHeader->manufacturerId[2] = PICMG_MANUFACTURER_ID_MSB;
  ptPConnRecHeader->manufacturerId[1] = PICMG_MANUFACTURER_ID_MID;
  ptPConnRecHeader->manufacturerId[0] = PICMG_MANUFACTURER_ID_LSB;
  ptPConnRecHeader->picmgRecordId = PICMG_RECORD_ID;
  ptPConnRecHeader->recordFormatVersion = AMC_PTP_CONNECTIVITY_RECORD_FORMAT_VERSION;
  ptPConnRecHeader->oemGuidCount = 0;
  recordType = AMC_PTP_CONNECTIVITY_RECORD_TYPE;

  amcChannelDescriptors = chDescrs;
  amcLinkDescriptors = lnkDescrs;
  
  int payloadSize = ptPConnRecHeaderRawData.size();
  for(std::list<amcChannelDescriptor>::const_iterator li = amcChannelDescriptors.cbegin(); li != amcChannelDescriptors.cend(); li++) {
    payloadSize += li->size();
  }
  for(std::list<amcLinkDescriptor>::const_iterator li = amcLinkDescriptors.cbegin(); li != amcLinkDescriptors.cend(); li++) {
    payloadSize += li->size();
  }
  if(payloadSize > 255) {
    throw std::length_error("record length exceeds maximum allowed length of 255 bytes");
  }
  header->recordLength = payloadSize;
}

void amcPtPConnectivityRecord::addAMCChannelDescriptor(int lanePortNo[4]) {
  for(int lane = 0; lane < 4; lane++) {
    if(lanePortNo[lane] < 0 || lanePortNo[lane] > 31) {
      throw std::out_of_range("lane number out of range");
    }
  }
}

std::vector<uint8_t> amcPtPConnectivityRecord::getBinaryData() {
  payload = ptPConnRecHeaderRawData;
  
  payload.push_back(recordType);
  payload.push_back(amcChannelDescriptors.size());
  
  for(std::list<amcChannelDescriptor>::const_iterator li = amcChannelDescriptors.begin(); li != amcChannelDescriptors.end(); li++) {
    std::vector<uint8_t> chDescriptor = li->getBinaryData();
    std::copy(chDescriptor.begin(), chDescriptor.end(), std::back_inserter(payload));
  }
  
  for(std::list<amcLinkDescriptor>::const_iterator li = amcLinkDescriptors.begin(); li != amcLinkDescriptors.end(); li++) {
    std::vector<uint8_t> lnkDescriptor = li->getBinaryData();
    std::copy(lnkDescriptor.begin(), lnkDescriptor.end(), std::back_inserter(payload));
  }
  
  header->recordLength = payload.size();

  return multiRecord::getBinaryData();
}

void amcPtPConnectivityRecord::printData() {
  updateRecordChecksum();
  updateHeaderChecksum();
  std::cout << "Record Type ID: 0x" << std::hex << (unsigned int)header->recordTypeId << std::endl;
  std::cout << "End of list: " << std::boolalpha << (bool)header->endOfList << std::endl;
  std::cout << "Record format version: " << std::dec << (unsigned int)header->recordFormatVersion << std::endl;
  std::cout << "Record length: " << std::dec << (unsigned int)header->recordLength << std::endl;
  std::cout << "Record checksum: 0x" << std::hex << (unsigned int)header->recordChecksum << std::endl;
  std::cout << "Header checksum: 0x" << std::hex << (unsigned int)header->headerChecksum << std::endl;
  const unsigned int manId = ptPConnRecHeader->manufacturerId[2] << 16 | ptPConnRecHeader->manufacturerId[1] << 8 | ptPConnRecHeader->manufacturerId[0];
  std::cout << "Manufacturer ID: 0x" << std::hex << manId << std::endl;
  std::cout << "PICMG Record ID: 0x" << std::hex << (unsigned int)ptPConnRecHeader->picmgRecordId << std::endl;
  std::cout << "Record Format Version: " << std::dec << (unsigned int)ptPConnRecHeader->recordFormatVersion << std::endl;
  std::cout << "OEM GUID Count: " << std::dec << (unsigned int)ptPConnRecHeader->oemGuidCount << std::endl;
  std::cout << "AMC Channel Descriptors: { " << std::endl;
  std::list<amcChannelDescriptor>::iterator cdli;
  int i;
  for(cdli = amcChannelDescriptors.begin(), i = 0; cdli != amcChannelDescriptors.end(); cdli++, i++) {
    std::cout << "AMC channel descriptor #" << std::dec << i << ":" << std::endl;
    cdli->printData();
  }
  std::cout << "}" << std::endl;

  std::cout << "AMC Link Descriptors: { " << std::endl;
  std::list<amcLinkDescriptor>::iterator ldli;
  for(ldli = amcLinkDescriptors.begin(), i = 0; ldli != amcLinkDescriptors.end(); ldli++, i++) {
    std::cout << "AMC link descriptor #" << std::dec << i << ":" << std::endl;
    ldli->printData();
  }
  std::cout << "}" << std::endl;
};
