#include "productInfoArea.hpp"
#include "checksum.hpp"
#include <iostream>

productInfoArea::productInfoArea() {
  data.formatVersion = 1;
  data.formatVersionPad = 0;
  data.areaLength = 2;
  data.languageCode = 0;
}

void productInfoArea::updateAreaLength()
{
  int length = sizeof(data) + manufacturer.size() + productName.size() + partNumber.size() + version.size() + serialNumber.size() + assetTag.size() + fruFileId.size() + 2;
  if( length % 8 ) {
    data.areaLength = length / 8 + 1;
  } else {
    data.areaLength = length / 8;
  }
}

uint8_t productInfoArea::getFormatVersion() { return data.formatVersion; };
uint8_t productInfoArea::getProductAreaLength() { updateAreaLength(); return data.areaLength; };
uint8_t productInfoArea::getLanguageCode() { return data.languageCode; };
void productInfoArea::setLanguageCode(uint8_t lang) { data.languageCode = lang; };
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
  return getBinaryData().back();
}

std::vector<uint8_t> productInfoArea::getBinaryData() {
  updateAreaLength();
  std::vector<uint8_t> rawData( (uint8_t *)&data, (uint8_t *)(&data + 1) );
  std::vector<uint8_t> manufacturerVec = manufacturer.getBinaryData();
  std::vector<uint8_t> productNameVec = productName.getBinaryData();
  std::vector<uint8_t> partNumberVec = partNumber.getBinaryData();
  std::vector<uint8_t> versionVec = version.getBinaryData();
  std::vector<uint8_t> serialNumberVec = serialNumber.getBinaryData();
  std::vector<uint8_t> assetTagVec = assetTag.getBinaryData();
  std::vector<uint8_t> fruFileIdVec = fruFileId.getBinaryData();

  rawData.insert(rawData.end(), manufacturerVec.begin(), manufacturerVec.end());
  rawData.insert(rawData.end(), productNameVec.begin(), productNameVec.end());
  rawData.insert(rawData.end(), partNumberVec.begin(), partNumberVec.end());
  rawData.insert(rawData.end(), versionVec.begin(), versionVec.end());
  rawData.insert(rawData.end(), serialNumberVec.begin(), serialNumberVec.end());
  rawData.insert(rawData.end(), assetTagVec.begin(), assetTagVec.end());
  rawData.insert(rawData.end(), fruFileIdVec.begin(), fruFileIdVec.end());
  rawData.insert(rawData.end(), 0xC1);
  rawData.resize(8 * data.areaLength, 0); // fill rest of vector with zeros (padding)
 
  updateAreaChecksum(rawData.begin(), rawData.end());
  return rawData;
}

void productInfoArea::printData() {
  std::cout << "Product Area Format Version: " << std::dec << (unsigned int)data.formatVersion << std::endl;
  std::cout << "Product Area Length: " << (unsigned int)data.areaLength << std::endl;
  std::cout << "Language Code: " << (unsigned int)data.languageCode << std::endl;
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
