#include "multiRecordArea.hpp"
#include <iostream>

void multiRecordArea::addRecord(multiRecord record) {
  record.setEndOfList(true);
  if(!m_records.empty()) {
    m_records.back().setEndOfList(false);
  }
  m_records.push_back(record);
}

void multiRecordArea::addRecord(uint8_t typeId, std::vector<uint8_t> payload) {
  multiRecord newRecord(typeId, payload);
  addRecord(newRecord);
};

void multiRecordArea::addAMCPtPConnectivityRecord(std::list<amcChannelDescriptor> chDescrs, std::list<amcLinkDescriptor> lnkDescrs) {
  amcPtPConnectivityRecord newRecord(chDescrs, lnkDescrs);
  addRecord(newRecord);
};

void multiRecordArea::addModuleCurrentRequirementsRecord(double currentDraw) {
  moduleCurrentRequirementsRecord newRecord(currentDraw);
  addRecord(newRecord);
};

void multiRecordArea::addZone3InterfaceCompatibilityRecord(uint8_t identifier, interfaceIdentifierBody* body)
{
  zone3InterfaceCompatibilityRecord newRecord(identifier, body);
  addRecord(newRecord);
};

void multiRecordArea::addClockConfigurationRecord(resourceIDResourceType rID, uint8_t dID, std::list<clockConfigurationDescriptor> clockDescrs)
{
  clockConfigurationRecord newRecord();
  addRecord(newRecord);
}

std::vector<uint8_t> multiRecordArea::getBinaryData() {
  std::list<multiRecord>::iterator li;
  std::vector<uint8_t> rawData;
  for(li = m_records.begin(); li != m_records.end(); li++) {
    std::vector<uint8_t> recordRawData = li->getBinaryData();
    rawData.insert(rawData.end(), recordRawData.begin(), recordRawData.end());
  }
  return rawData;
};

void multiRecordArea::printData() {
  std::list<multiRecord>::iterator li;
  for(li = m_records.begin(); li != m_records.end(); li++) {
    std::cout << "MULTI RECORD:" << std::endl;
    li->printData();
  }
};

int multiRecordArea::size() {
  std::list<multiRecord>::iterator li;
  int sum = 0;
  for(li = m_records.begin(); li != m_records.end(); li++)
    sum += li->size();
  return sum;
};