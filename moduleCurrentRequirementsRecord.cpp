#include "moduleCurrentRequirementsRecord.hpp"
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <iomanip>

#define MODULE_PWR_DESCRIPTOR_PICMG_RECORD_ID 0x16
#define MODULE_PWR_RECORD_FORMAT_VERSION 0

moduleCurrentRequirementsRecord::moduleCurrentRequirementsRecord(double currentDraw) : multiRecord::multiRecord(RECORD_TYPE_OEM, std::vector<uint8_t>(sizeof(struct payloadFormat))) {
  payloadData = (struct payloadFormat *)payload.data();
  payloadData->manufacturerId[2] = PICMG_MANUFACTURER_ID_MSB;
  payloadData->manufacturerId[1] = PICMG_MANUFACTURER_ID_MID;
  payloadData->manufacturerId[0] = PICMG_MANUFACTURER_ID_LSB;
  payloadData->picmgRecordId = MODULE_PWR_DESCRIPTOR_PICMG_RECORD_ID;
  payloadData->recordFormatVersion = MODULE_PWR_RECORD_FORMAT_VERSION;
  
  if(currentDraw < 0 || currentDraw > 80.0 / 12.0) {
    throw std::invalid_argument("currentDraw invalid, payload current must be between 0 and 6.67 Ampere (cf. REQ 4.4b)");
  }
  payloadData->currentDraw = round(10 * currentDraw); // cf. REQ 3.75
}

std::vector<uint8_t> moduleCurrentRequirementsRecord::getBinaryData() {
  return multiRecord::getBinaryData();
};

void moduleCurrentRequirementsRecord::printData() {
  updateRecordChecksum();
  updateHeaderChecksum();
  std::cout << "Record Type ID: 0x" << std::hex << (unsigned int)header->recordTypeId << std::endl;
  std::cout << "End of list: " << std::boolalpha << (bool)header->endOfList << std::endl;
  std::cout << "Record format version: " << std::dec << (unsigned int)header->recordFormatVersion << std::endl;
  std::cout << "Record length: " << std::dec << (unsigned int)header->recordLength << std::endl;
  std::cout << "Record checksum: 0x" << std::hex << (unsigned int)header->recordChecksum << std::endl;
  std::cout << "Header checksum: 0x" << std::hex << (unsigned int)header->headerChecksum << std::endl;
  const unsigned int manId = payloadData->manufacturerId[2] << 16 | payloadData->manufacturerId[1] << 8 | payloadData->manufacturerId[0];
  std::cout << "Manufacturer ID: 0x" << std::hex << manId << std::endl;
  std::cout << "PICMG Record ID: 0x" << std::hex << (unsigned int)payloadData->picmgRecordId << std::endl;
  std::cout << "Record Format Version: " << std::dec << (unsigned int)payloadData->recordFormatVersion << std::endl;
  std::cout << "Current Draw: " << std::dec << std::setprecision(1) << payloadData->currentDraw / 10.0 << std::endl;
};