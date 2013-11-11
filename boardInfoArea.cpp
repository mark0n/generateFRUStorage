#include "boardInfoArea.hpp"
#include "checksum.hpp"
#include <iostream>

using namespace boost::posix_time;
using namespace boost::gregorian;

const ptime boardInfoArea::epoch(date(1996, Jan, 1), hours(0) + minutes(0));

boardInfoArea::boardInfoArea() : rawData(13) {
  data = (struct boardInfoAreaData *)rawData.data();
  data->formatVersion = 1;
  data->areaLength = 2;
}

uint8_t boardInfoArea::getFormatVersion() { data = (struct boardInfoAreaData *)rawData.data(); return data->formatVersion; };
uint8_t boardInfoArea::getBoardAreaLength() { data = (struct boardInfoAreaData *)rawData.data(); return data->areaLength; };
uint8_t boardInfoArea::getLanguageCode() { data = (struct boardInfoAreaData *)rawData.data(); return data->languageCode; };
void boardInfoArea::setLanguageCode(uint8_t lang) { data = (struct boardInfoAreaData *)rawData.data(); data->languageCode = lang; };

ptime boardInfoArea::getMfgDateTime() {
  int minutesSinceEpoch = (data->mfgDateTime[2] << 16) + (data->mfgDateTime[1] << 8) + data->mfgDateTime[0];
  return epoch + minutes(minutesSinceEpoch);
};

void boardInfoArea::setMfgDateTime(ptime time) {
  int minutesSinceEpoch = time_duration(time - epoch).total_seconds() / 60;
  data->mfgDateTime[2] = (minutesSinceEpoch >> 16) & 0xff;
  data->mfgDateTime[1] = (minutesSinceEpoch >> 8) & 0xff;
  data->mfgDateTime[0] = minutesSinceEpoch & 0xff;
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
  updateAreaChecksum(rawData.begin(), rawData.end());
  return rawData.back();
}

std::vector<uint8_t> boardInfoArea::getBinaryData() {
  std::vector<uint8_t> manufacturerVec = manufacturer.getBinaryData();
  std::vector<uint8_t> productNameVec = productName.getBinaryData();
  std::vector<uint8_t> serialNumberVec = serialNumber.getBinaryData();
  std::vector<uint8_t> partNumberVec = partNumber.getBinaryData();
  std::vector<uint8_t> fruFileIdVec = fruFileId.getBinaryData();

  rawData.resize(sizeof(*data));
  rawData.insert(rawData.end(), manufacturerVec.begin(), manufacturerVec.end());
  rawData.insert(rawData.end(), productNameVec.begin(), productNameVec.end());
  rawData.insert(rawData.end(), serialNumberVec.begin(), serialNumberVec.end());
  rawData.insert(rawData.end(), partNumberVec.begin(), partNumberVec.end());
  rawData.insert(rawData.end(), fruFileIdVec.begin(), fruFileIdVec.end());
  rawData.insert(rawData.end(), 0xC1);

  std::vector<uint8_t> padVec;
  padVec.resize(8 - rawData.size() % 8); // if the size is a multiple of 8 we have to add 8 bytes since the last byte gets overwritten by the checksum
  rawData.insert(rawData.end(), padVec.begin(), padVec.end());
 
  data = (struct boardInfoAreaData *)rawData.data();
  data->areaLength = rawData.size() / 8;
  updateAreaChecksum(rawData.begin(), rawData.end());
  return rawData;
}

void boardInfoArea::printData() {
  data = (struct boardInfoAreaData *)rawData.data(); 
  updateAreaChecksum(rawData.begin(), rawData.end());
  std::cout << "Board Area Format Version: " << std::dec << (unsigned int)data->formatVersion << std::endl;
  std::cout << "Board Area Length: " << (unsigned int)data->areaLength << std::endl;
  std::cout << "Language Code: " << (unsigned int)data->languageCode << std::endl;
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