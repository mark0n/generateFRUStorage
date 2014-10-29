#include "moduleCurrentRequirementsRecord.hpp"
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <iomanip>

const uint8_t modulePwrDescriptorPICMGRecordId = 0x16;
const uint8_t modulePwrRecordFormatVersion = 0;

moduleCurrentRequirementsRecord::moduleCurrentRequirementsRecord(double currentDraw) :
  multiRecord::multiRecord(RECORD_TYPE_OEM, std::vector<uint8_t>(sizeof(struct payloadFormat)))
{
  m_data.manufacturerId[2] = PICMG_MANUFACTURER_ID_MSB;
  m_data.manufacturerId[1] = PICMG_MANUFACTURER_ID_MID;
  m_data.manufacturerId[0] = PICMG_MANUFACTURER_ID_LSB;
  m_data.picmgRecordId = modulePwrDescriptorPICMGRecordId;
  m_data.recordFormatVersion = modulePwrRecordFormatVersion;
  
  if(currentDraw < 0 || currentDraw > 80.0 / 12.0) {
    throw std::invalid_argument("currentDraw invalid, payload current must be between 0 and 6.67 Ampere (cf. REQ 4.4b)");
  }
  m_data.currentDraw = round(10 * currentDraw); // cf. REQ 3.75

  multiRecord::m_payload = std::vector<uint8_t>( (uint8_t *)&m_data, (uint8_t *)(&m_data + 1) );
}

std::vector<uint8_t> moduleCurrentRequirementsRecord::getBinaryData() {
  return multiRecord::getBinaryData();
};

void moduleCurrentRequirementsRecord::printData() {
  updateRecordChecksum();
  updateHeaderChecksum();
  std::cout << "Record Type ID: 0x" << std::hex << (unsigned int)m_header.recordTypeId << std::endl;
  std::cout << "End of list: " << std::boolalpha << (bool)m_header.endOfList << std::endl;
  std::cout << "Record format version: " << std::dec << (unsigned int)m_header.recordFormatVersion << std::endl;
  std::cout << "Record length: " << std::dec << (unsigned int)m_header.recordLength << std::endl;
  std::cout << "Record checksum: 0x" << std::hex << (unsigned int)m_header.recordChecksum << std::endl;
  std::cout << "Header checksum: 0x" << std::hex << (unsigned int)m_header.headerChecksum << std::endl;
  const unsigned int manId = m_data.manufacturerId[2] << 16 | m_data.manufacturerId[1] << 8 | m_data.manufacturerId[0];
  std::cout << "Manufacturer ID: 0x" << std::hex << manId << std::endl;
  std::cout << "PICMG Record ID: 0x" << std::hex << (unsigned int)m_data.picmgRecordId << std::endl;
  std::cout << "Record Format Version: " << std::dec << (unsigned int)m_data.recordFormatVersion << std::endl;
  std::cout << "Current Draw: " << std::dec << std::setprecision(1) << m_data.currentDraw / 10.0 << std::endl;
};