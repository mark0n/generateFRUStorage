#include "commonHeader.hpp"
#include "checksum.hpp"
#include <iostream>

commonHeader::commonHeader() : rawData(sizeof(commonHeaderData *)) {
  data = (struct commonHeaderData *)rawData.data();
  data->formatVersion = 1;
}

uint8_t commonHeader::getFormatVersion() { return data->formatVersion; }
uint8_t commonHeader::getInternalUseAreaOffset() { return data->internalUseAreaOffset; }
void commonHeader::setInternalUseAreaOffset(uint8_t offset) { data->internalUseAreaOffset = offset; }
uint8_t commonHeader::getChassisInfoAreaOffset() { return data->chassisInfoAreaOffset; }
void commonHeader::setChassisInfoAreaOffset(uint8_t offset) { data->chassisInfoAreaOffset = offset; }
uint8_t commonHeader::getBoardAreaOffset() { return data->boardAreaOffset; }
void commonHeader::setBoardAreaOffset(uint8_t offset) { data->boardAreaOffset = offset; }
uint8_t commonHeader::getProductInfoAreaOffset() { return data->productInfoAreaOffset; }
void commonHeader::setProductInfoAreaOffset(uint8_t offset) { data->productInfoAreaOffset = offset; }
uint8_t commonHeader::getMultiRecordAreaOffset() { return data->multiRecordAreaOffset; }
void commonHeader::setMultiRecordAreaOffset(uint8_t offset) { data->multiRecordAreaOffset = offset; }

uint8_t commonHeader::getChecksum() {
  updateAreaChecksum(rawData);
  return rawData.back();
}

std::vector<uint8_t> commonHeader::getBinaryData() {
  updateAreaChecksum(rawData);
  return rawData;
}

void commonHeader::printData() {
  updateAreaChecksum(rawData);
  std::cout << "Common Header Format Version: " << std::dec << (unsigned int)data->formatVersion << std::endl;
  std::cout << "Internal Use Area Starting Offset: 0x" << std::hex << (unsigned int)data->internalUseAreaOffset << std::endl;
  std::cout << "Chassis Info Area Starting Offset: 0x" << std::hex << (unsigned int)data->chassisInfoAreaOffset << std::endl;
  std::cout << "boardAreaStartingOffset: 0x" << std::hex << (unsigned int)data->boardAreaOffset << std::endl;
  std::cout << "productInfoAreaStartingOffset: 0x" << std::hex << (unsigned int)data->productInfoAreaOffset << std::endl;
  std::cout << "multiRecordAreaStartingOffset: 0x" << std::hex << (unsigned int)data->multiRecordAreaOffset << std::endl;
  std::cout << "Pad: 0x" << std::hex << (unsigned int)data->pad << std::endl;
  std::cout << "Common Header Checksum: 0x" << std::hex << (unsigned int)getChecksum() << std::endl;
}

int commonHeader::size() {
  return rawData.size();
}