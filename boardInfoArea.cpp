#include "boardInfoArea.hpp"
#include "checksum.hpp"
#include <iostream>

using namespace boost::posix_time;
using namespace boost::gregorian;

const ptime boardInfoArea::m_epoch(date(1996, Jan, 1), hours(0) + minutes(0));

boardInfoArea::boardInfoArea() {
  m_data.formatVersion = 1;
  m_data.formatVersionPad = 0;
  m_data.areaLength = 2;
  m_data.languageCode = 0;
  m_data.mfgDateTime[0] = 0;
  m_data.mfgDateTime[1] = 0;
  m_data.mfgDateTime[2] = 0;
}

void boardInfoArea::updateAreaLength()
{
  int length = sizeof(m_data) + m_manufacturer.size() + m_productName.size() + m_serialNumber.size() + m_partNumber.size() + m_fruFileId.size() + 2;
  if( length % 8 ) {
    m_data.areaLength = length / 8 + 1;
  } else {
    m_data.areaLength = length / 8;
  }
}

uint8_t boardInfoArea::getFormatVersion() { return m_data.formatVersion; };
uint8_t boardInfoArea::getBoardAreaLength() { updateAreaLength(); return m_data.areaLength; };
uint8_t boardInfoArea::getLanguageCode() { return m_data.languageCode; };
void boardInfoArea::setLanguageCode(uint8_t lang) { m_data.languageCode = lang; };

ptime boardInfoArea::getMfgDateTime() {
  int minutesSinceEpoch = (m_data.mfgDateTime[2] << 16) + (m_data.mfgDateTime[1] << 8) + m_data.mfgDateTime[0];
  return m_epoch + minutes(minutesSinceEpoch);
};

void boardInfoArea::setMfgDateTime(ptime time) {
  int minutesSinceEpoch = time_duration(time - m_epoch).total_seconds() / 60;
  m_data.mfgDateTime[2] = (minutesSinceEpoch >> 16) & 0xff;
  m_data.mfgDateTime[1] = (minutesSinceEpoch >> 8) & 0xff;
  m_data.mfgDateTime[0] = minutesSinceEpoch & 0xff;
};

std::string boardInfoArea::getManufacturer() { return m_manufacturer.getString(); };
void boardInfoArea::setManufacturer(std::string str) { m_manufacturer.setString(str); };
std::string boardInfoArea::getProductName() { return m_productName.getString(); };
void boardInfoArea::setProductName(std::string str) { m_productName.setString(str); };
std::string boardInfoArea::getSerialNumber() { return m_serialNumber.getString(); };
void boardInfoArea::setSerialNumber(std::string str) { m_serialNumber.setString(str); };
std::string boardInfoArea::getPartNumber() { return m_partNumber.getString(); };
void boardInfoArea::setPartNumber(std::string str) { m_partNumber.setString(str); };
std::string boardInfoArea::getFRUFileId() { return m_fruFileId.getString(); };
void boardInfoArea::setFRUFileId(std::string str) { m_fruFileId.setString(str); };

uint8_t boardInfoArea::getChecksum() {
  return getBinaryData().back();
}

std::vector<uint8_t> boardInfoArea::getBinaryData() {
  updateAreaLength();
  std::vector<uint8_t> rawData( (uint8_t *)&m_data, (uint8_t *)(&m_data + 1) );
  std::vector<uint8_t> manufacturerVec = m_manufacturer.getBinaryData();
  std::vector<uint8_t> productNameVec = m_productName.getBinaryData();
  std::vector<uint8_t> serialNumberVec = m_serialNumber.getBinaryData();
  std::vector<uint8_t> partNumberVec = m_partNumber.getBinaryData();
  std::vector<uint8_t> fruFileIdVec = m_fruFileId.getBinaryData();

  rawData.insert(rawData.end(), manufacturerVec.begin(), manufacturerVec.end());
  rawData.insert(rawData.end(), productNameVec.begin(), productNameVec.end());
  rawData.insert(rawData.end(), serialNumberVec.begin(), serialNumberVec.end());
  rawData.insert(rawData.end(), partNumberVec.begin(), partNumberVec.end());
  rawData.insert(rawData.end(), fruFileIdVec.begin(), fruFileIdVec.end());
  rawData.insert( rawData.end(), 0xc1 );
  rawData.resize(8 * m_data.areaLength, 0); // fill rest of vector with zeros (padding)

  updateAreaChecksum(rawData.begin(), rawData.end());
  return rawData;
}

void boardInfoArea::printData() {
  std::cout << "Board Area Format Version: " << std::dec << (unsigned int)m_data.formatVersion << std::endl;
  std::cout << "Board Area Length: " << (unsigned int)m_data.areaLength << std::endl;
  std::cout << "Language Code: " << (unsigned int)m_data.languageCode << std::endl;
  std::cout << "Mfg. Date/Time: " << getMfgDateTime() << std::endl;
  std::cout << "Board Manufacturer: " << m_manufacturer.getString() << std::endl;
  std::cout << "Board Product Name: " << m_productName.getString() << std::endl;
  std::cout << "Board Serial Number: " << m_serialNumber.getString() << std::endl;
  std::cout << "Board Part Number: " << m_partNumber.getString() << std::endl;
  std::cout << "FRU File ID: " << m_fruFileId.getString() << std::endl;
  std::cout << "Board Area Checksum: " << (unsigned int)getChecksum() << std::endl;
}

int boardInfoArea::size() {
  return getBinaryData().size();
}