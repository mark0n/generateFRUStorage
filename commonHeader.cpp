#include "commonHeader.hpp"
#include "checksum.hpp"
#include <iostream>

commonHeader::commonHeader() {
  m_data.formatVersion = 1;
  m_data.internalUseAreaOffset = 0x00;
  m_data.chassisInfoAreaOffset = 0x00;
  m_data.boardAreaOffset = 0x00;
  m_data.productInfoAreaOffset = 0x00;
  m_data.multiRecordAreaOffset = 0x00;
  m_data.pad = 0x00;
  m_data.checksum = 0xff;
};

uint8_t commonHeader::getFormatVersion() { return m_data.formatVersion; }
uint8_t commonHeader::getInternalUseAreaOffset() { return m_data.internalUseAreaOffset; }
void commonHeader::setInternalUseAreaOffset(uint8_t offset) { m_data.internalUseAreaOffset = offset; }
uint8_t commonHeader::getChassisInfoAreaOffset() { return m_data.chassisInfoAreaOffset; }
void commonHeader::setChassisInfoAreaOffset(uint8_t offset) { m_data.chassisInfoAreaOffset = offset; }
uint8_t commonHeader::getBoardAreaOffset() { return m_data.boardAreaOffset; }
void commonHeader::setBoardAreaOffset(uint8_t offset) { m_data.boardAreaOffset = offset; }
uint8_t commonHeader::getProductInfoAreaOffset() { return m_data.productInfoAreaOffset; }
void commonHeader::setProductInfoAreaOffset(uint8_t offset) { m_data.productInfoAreaOffset = offset; }
uint8_t commonHeader::getMultiRecordAreaOffset() { return m_data.multiRecordAreaOffset; }
void commonHeader::setMultiRecordAreaOffset(uint8_t offset) { m_data.multiRecordAreaOffset = offset; }

uint8_t commonHeader::getChecksum() {
  updateAreaChecksum((uint8_t *)&m_data, (uint8_t *)(&m_data + 1));
  return m_data.checksum;
}

std::vector<uint8_t> commonHeader::getBinaryData() {
  updateAreaChecksum((uint8_t *)&m_data, (uint8_t *)(&m_data + 1));
  return std::vector<uint8_t>((uint8_t *)&m_data, (uint8_t *)(&m_data + 1));
}

void commonHeader::printData() {
  updateAreaChecksum((uint8_t *)&m_data, (uint8_t *)(&m_data + 1));
  std::cout << "Common Header Format Version: " << std::dec << (unsigned int)m_data.formatVersion << std::endl;
  std::cout << "Internal Use Area Starting Offset: 0x" << std::hex << (unsigned int)m_data.internalUseAreaOffset << std::endl;
  std::cout << "Chassis Info Area Starting Offset: 0x" << std::hex << (unsigned int)m_data.chassisInfoAreaOffset << std::endl;
  std::cout << "boardAreaStartingOffset: 0x" << std::hex << (unsigned int)m_data.boardAreaOffset << std::endl;
  std::cout << "productInfoAreaStartingOffset: 0x" << std::hex << (unsigned int)m_data.productInfoAreaOffset << std::endl;
  std::cout << "multiRecordAreaStartingOffset: 0x" << std::hex << (unsigned int)m_data.multiRecordAreaOffset << std::endl;
  std::cout << "Pad: 0x" << std::hex << (unsigned int)m_data.pad << std::endl;
  std::cout << "Common Header Checksum: 0x" << std::hex << (unsigned int)getChecksum() << std::endl;
}

int commonHeader::size() {
  return sizeof(m_data);
}