#include "boardInfoArea.hpp"
#include "checksum.hpp"
#include <iostream>
#include <ctime>

#define TIMEBASE1996 820472400

boardInfoArea::boardInfoArea() : rawData(13) {
  data = (struct boardInfoAreaData *)rawData.data();
  data->formatVersion = 1;
  data->areaLength = 1;
}

time_t minutesToPosixTime(int minutesSince1996) {
  return TIMEBASE1996 + minutesSince1996 * 60;
}

int posixTimeToMinutes(time_t posixTime) {
  return (posixTime - TIMEBASE1996) / 60;
}

uint8_t boardInfoArea::getFormatVersion() { data = (struct boardInfoAreaData *)rawData.data(); return data->formatVersion; };
uint8_t boardInfoArea::getBoardAreaLength() { data = (struct boardInfoAreaData *)rawData.data(); return data->areaLength; };
uint8_t boardInfoArea::getLanguageCode() { data = (struct boardInfoAreaData *)rawData.data(); return data->languageCode; };
void boardInfoArea::setLanguageCode(uint8_t lang) { data = (struct boardInfoAreaData *)rawData.data(); data->languageCode = lang; };
time_t boardInfoArea::getMfgDateTime() {
  int minutesSince1996 = (data->mfgDateTime[2] << 16) + (data->mfgDateTime[1] << 8) + data->mfgDateTime[0];
  return minutesToPosixTime(minutesSince1996);
};
void boardInfoArea::setMfgDateTime(time_t posixTime) {
  int minutesSince1996 = posixTimeToMinutes(posixTime);
  data->mfgDateTime[2] = (minutesSince1996 >> 16) & 0xff;
  data->mfgDateTime[1] = (minutesSince1996 >> 8) & 0xff;
  data->mfgDateTime[0] = minutesSince1996 & 0xff;
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
  updateAreaChecksum(rawData);
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
  if(rawData.size() % 8 != 0) {
    padVec.resize(8 - rawData.size() % 8);
  }
  rawData.insert(rawData.end(), padVec.begin(), padVec.end());
 
  data = (struct boardInfoAreaData *)rawData.data();
  data->areaLength = rawData.size() / 8;
  updateAreaChecksum(rawData);
  return rawData;
}

void boardInfoArea::printData() {
  data = (struct boardInfoAreaData *)rawData.data(); 
  updateAreaChecksum(rawData);
  std::cout << "Board Area Format Version: " << std::dec << (unsigned int)data->formatVersion << std::endl;
  std::cout << "Board Area Length: " << (unsigned int)data->areaLength << std::endl;
  std::cout << "Language Code: " << (unsigned int)data->languageCode << std::endl;
  const time_t posixTime = getMfgDateTime();
  std::string timeStr = ctime(&posixTime);
  timeStr.erase(timeStr.find_last_not_of(" \n\r\t")+ 1); // remove trailing linebreak/whitespaces
  std::cout << "Mfg. Date/Time: " << timeStr << std::endl;
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