#include "boardInfoArea.hpp"
#include "checksum.hpp"
#include <iostream>

using namespace boost::posix_time;
using namespace boost::gregorian;

const ptime boardInfoArea::epoch(date(1996, Jan, 1), hours(0) + minutes(0));

boardInfoArea::boardInfoArea() {
  data.formatVersion = 1;
  data.formatVersionPad = 0;
  data.areaLength = 2;
  data.languageCode = 0;
  data.mfgDateTime[0] = 0;
  data.mfgDateTime[1] = 0;
  data.mfgDateTime[2] = 0;
}

void boardInfoArea::updateAreaLength()
{
  int length = sizeof(data) + manufacturer.size() + productName.size() + serialNumber.size() + partNumber.size() + fruFileId.size() + 2;
  if( length % 8 ) {
    data.areaLength = length / 8 + 1;
  } else {
    data.areaLength = length / 8;
  }
}

uint8_t boardInfoArea::getFormatVersion() { return data.formatVersion; };
uint8_t boardInfoArea::getBoardAreaLength() { updateAreaLength(); return data.areaLength; };
uint8_t boardInfoArea::getLanguageCode() { return data.languageCode; };
void boardInfoArea::setLanguageCode(uint8_t lang) { data.languageCode = lang; };

ptime boardInfoArea::getMfgDateTime() {
  int minutesSinceEpoch = (data.mfgDateTime[2] << 16) + (data.mfgDateTime[1] << 8) + data.mfgDateTime[0];
  return epoch + minutes(minutesSinceEpoch);
};

void boardInfoArea::setMfgDateTime(ptime time) {
  int minutesSinceEpoch = time_duration(time - epoch).total_seconds() / 60;
  data.mfgDateTime[2] = (minutesSinceEpoch >> 16) & 0xff;
  data.mfgDateTime[1] = (minutesSinceEpoch >> 8) & 0xff;
  data.mfgDateTime[0] = minutesSinceEpoch & 0xff;
};

std::string boardInfoArea::getManufacturer() { return manufacturer.getString(); };
void boardInfoArea::setManufacturer(std::string str) { manufacturer.setString(str); };
std::string boardInfoArea::getProductName() { return productName.getString(); };
void boardInfoArea::setProductName(std::string str) { productName.setString(str); };
std::string boardInfoArea::getSerialNumber() { return serialNumber.getString(); };
void boardInfoArea::setSerialNumber(std::string str) { serialNumber.setString(str); };
std::string boardInfoArea::getPartNumber() { return partNumber.getString(); };
void boardInfoArea::setPartNumber(std::string str) { partNumber.setString(str); };
std::string boardInfoArea::getFRUFileId() { return fruFileId.getString(); };
void boardInfoArea::setFRUFileId(std::string str) { fruFileId.setString(str); };

uint8_t boardInfoArea::getChecksum() {
  return getBinaryData().back();
}

std::vector<uint8_t> boardInfoArea::getBinaryData() {
  updateAreaLength();
  std::vector<uint8_t> rawData( (uint8_t *)&data, (uint8_t *)(&data + 1) );
  std::vector<uint8_t> manufacturerVec = manufacturer.getBinaryData();
  std::vector<uint8_t> productNameVec = productName.getBinaryData();
  std::vector<uint8_t> serialNumberVec = serialNumber.getBinaryData();
  std::vector<uint8_t> partNumberVec = partNumber.getBinaryData();
  std::vector<uint8_t> fruFileIdVec = fruFileId.getBinaryData();

  rawData.insert(rawData.end(), manufacturerVec.begin(), manufacturerVec.end());
  rawData.insert(rawData.end(), productNameVec.begin(), productNameVec.end());
  rawData.insert(rawData.end(), serialNumberVec.begin(), serialNumberVec.end());
  rawData.insert(rawData.end(), partNumberVec.begin(), partNumberVec.end());
  rawData.insert(rawData.end(), fruFileIdVec.begin(), fruFileIdVec.end());
  rawData.insert( rawData.end(), 0xc1 );
  rawData.resize(8 * data.areaLength, 0); // fill rest of vector with zeros (padding)

  updateAreaChecksum(rawData.begin(), rawData.end());
  return rawData;
}

void boardInfoArea::printData() {
  updateAreaChecksum( (uint8_t *)&data, (uint8_t *)(&data + 1) );
  std::cout << "Board Area Format Version: " << std::dec << (unsigned int)data.formatVersion << std::endl;
  std::cout << "Board Area Length: " << (unsigned int)data.areaLength << std::endl;
  std::cout << "Language Code: " << (unsigned int)data.languageCode << std::endl;
  std::cout << "Mfg. Date/Time: " << getMfgDateTime() << std::endl;
  std::cout << "Board Manufacturer: " << manufacturer.getString() << std::endl;
  std::cout << "Board Product Name: " << productName.getString() << std::endl;
  std::cout << "Board Serial Number: " << serialNumber.getString() << std::endl;
  std::cout << "Board Part Number: " << partNumber.getString() << std::endl;
  std::cout << "FRU File ID: " << fruFileId.getString() << std::endl;
  std::cout << "Board Area Checksum: " << (unsigned int)getChecksum() << std::endl;
}

int boardInfoArea::size() {
  return getBinaryData().size();
}