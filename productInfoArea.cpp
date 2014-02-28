#include "productInfoArea.hpp"
#include "checksum.hpp"
#include <iostream>

productInfoArea::productInfoArea() : rawData(13) {
  data = (struct productInfoAreaData *)rawData.data();
  data->formatVersion = 1;
  data->areaLength = 1;
}

uint8_t productInfoArea::getFormatVersion() { data = (struct productInfoAreaData *)rawData.data(); return data->formatVersion; };
uint8_t productInfoArea::getProductAreaLength() { data = (struct productInfoAreaData *)rawData.data(); return data->areaLength; };
uint8_t productInfoArea::getLanguageCode() { data = (struct productInfoAreaData *)rawData.data(); return data->languageCode; };
void productInfoArea::setLanguageCode(uint8_t lang) { data = (struct productInfoAreaData *)rawData.data(); data->languageCode = lang; };
std::string productInfoArea::getManufacturer() { return manufacturer.getString(); };
void productInfoArea::setManufacturer(std::string str) { manufacturer.setString(str); };
std::string productInfoArea::getProductName() { return productName.getString(); };
void productInfoArea::setProductName(std::string str) { productName.setString(str); };
std::string productInfoArea::getPartNumber() { return partNumber.getString(); };
void productInfoArea::setPartNumber(std::string str) { partNumber.setString(str); };
std::string productInfoArea::getVersion() { return version.getString(); };
void productInfoArea::setVersion(std::string str) { version.setString(str); };
std::string productInfoArea::getSerialNumber() { return serialNumber.getString(); };
void productInfoArea::setSerialNumber(std::string str) { serialNumber.setString(str); };
std::string productInfoArea::getAssetTag() { return assetTag.getString(); };
void productInfoArea::setAssetTag(std::string str) { assetTag.setString(str); };
std::string productInfoArea::getFRUFileId() { return fruFileId.getString(); };
void productInfoArea::setFRUFileId(std::string str) { fruFileId.setString(str); };

uint8_t productInfoArea::getChecksum() {
  updateAreaChecksum(rawData.begin(), rawData.end());
  return rawData.back();
}

std::vector<uint8_t> productInfoArea::getBinaryData() {
  std::vector<uint8_t> manufacturerVec = manufacturer.getBinaryData();
  std::vector<uint8_t> productNameVec = productName.getBinaryData();
  std::vector<uint8_t> partNumberVec = partNumber.getBinaryData();
  std::vector<uint8_t> versionVec = version.getBinaryData();
  std::vector<uint8_t> serialNumberVec = serialNumber.getBinaryData();
  std::vector<uint8_t> assetTagVec = assetTag.getBinaryData();
  std::vector<uint8_t> fruFileIdVec = fruFileId.getBinaryData();

  rawData.resize(sizeof(*data));
  rawData.insert(rawData.end(), manufacturerVec.begin(), manufacturerVec.end());
  rawData.insert(rawData.end(), productNameVec.begin(), productNameVec.end());
  rawData.insert(rawData.end(), partNumberVec.begin(), partNumberVec.end());
  rawData.insert(rawData.end(), versionVec.begin(), versionVec.end());
  rawData.insert(rawData.end(), serialNumberVec.begin(), serialNumberVec.end());
  rawData.insert(rawData.end(), assetTagVec.begin(), assetTagVec.end());
  rawData.insert(rawData.end(), fruFileIdVec.begin(), fruFileIdVec.end());
  rawData.insert(rawData.end(), 0xC1);

  std::vector<uint8_t> padVec;
  if(rawData.size() % 8 != 0) {
    padVec.resize(8 - rawData.size() % 8);
  }
  rawData.insert(rawData.end(), padVec.begin(), padVec.end());
 
  data = (struct productInfoAreaData *)rawData.data();
  data->areaLength = rawData.size() / 8;
  updateAreaChecksum(rawData.begin(), rawData.end());
  return rawData;
}

void productInfoArea::printData() {
  data = (struct productInfoAreaData *)rawData.data(); 
  updateAreaChecksum(rawData.begin(), rawData.end());
  std::cout << "Product Area Format Version: " << std::dec << (unsigned int)data->formatVersion << std::endl;
  std::cout << "Product Area Length: " << (unsigned int)data->areaLength << std::endl;
  std::cout << "Language Code: " << (unsigned int)data->languageCode << std::endl;
  std::cout << "Product Manufacturer: " << manufacturer.getString() << std::endl;
  std::cout << "Product Name: " << productName.getString() << std::endl;
  std::cout << "Product Serial Number: " << serialNumber.getString() << std::endl;
  std::cout << "Product Part Number: " << partNumber.getString() << std::endl;
  std::cout << "FRU File ID: " << fruFileId.getString() << std::endl;
  std::cout << "Product Area Checksum: " << (unsigned int)getChecksum() << std::endl;
}

int productInfoArea::size() {
  return getBinaryData().size();
}
