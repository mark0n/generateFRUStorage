#include "productInfoArea.hpp"
#include "checksum.hpp"
#include <iostream>

productInfoArea::productInfoArea() {
  m_data.formatVersion = 1;
  m_data.formatVersionPad = 0;
  m_data.areaLength = 2;
  m_data.languageCode = 0;
}

void productInfoArea::updateAreaLength()
{
  int length = sizeof(m_data) + m_manufacturer.size() + m_productName.size() + m_partNumber.size() + m_version.size() + m_serialNumber.size() + m_assetTag.size() + m_fruFileId.size() + 2;
  if( length % 8 ) {
    m_data.areaLength = length / 8 + 1;
  } else {
    m_data.areaLength = length / 8;
  }
}

uint8_t productInfoArea::getFormatVersion() { return m_data.formatVersion; };
uint8_t productInfoArea::getProductAreaLength() { updateAreaLength(); return m_data.areaLength; };
uint8_t productInfoArea::getLanguageCode() { return m_data.languageCode; };
void productInfoArea::setLanguageCode(uint8_t lang) { m_data.languageCode = lang; };
std::string productInfoArea::getManufacturer() { return m_manufacturer.getString(); };
void productInfoArea::setManufacturer(std::string str) { m_manufacturer.setString(str); };
std::string productInfoArea::getProductName() { return m_productName.getString(); };
void productInfoArea::setProductName(std::string str) { m_productName.setString(str); };
std::string productInfoArea::getPartNumber() { return m_partNumber.getString(); };
void productInfoArea::setPartNumber(std::string str) { m_partNumber.setString(str); };
std::string productInfoArea::getVersion() { return m_version.getString(); };
void productInfoArea::setVersion(std::string str) { m_version.setString(str); };
std::string productInfoArea::getSerialNumber() { return m_serialNumber.getString(); };
void productInfoArea::setSerialNumber(std::string str) { m_serialNumber.setString(str); };
std::string productInfoArea::getAssetTag() { return m_assetTag.getString(); };
void productInfoArea::setAssetTag(std::string str) { m_assetTag.setString(str); };
std::string productInfoArea::getFRUFileId() { return m_fruFileId.getString(); };
void productInfoArea::setFRUFileId(std::string str) { m_fruFileId.setString(str); };

uint8_t productInfoArea::getChecksum() {
  return getBinaryData().back();
}

std::vector<uint8_t> productInfoArea::getBinaryData() {
  updateAreaLength();
  std::vector<uint8_t> rawData( (uint8_t *)&m_data, (uint8_t *)(&m_data + 1) );
  std::vector<uint8_t> manufacturerVec = m_manufacturer.getBinaryData();
  std::vector<uint8_t> productNameVec = m_productName.getBinaryData();
  std::vector<uint8_t> partNumberVec = m_partNumber.getBinaryData();
  std::vector<uint8_t> versionVec = m_version.getBinaryData();
  std::vector<uint8_t> serialNumberVec = m_serialNumber.getBinaryData();
  std::vector<uint8_t> assetTagVec = m_assetTag.getBinaryData();
  std::vector<uint8_t> fruFileIdVec = m_fruFileId.getBinaryData();

  rawData.insert(rawData.end(), manufacturerVec.begin(), manufacturerVec.end());
  rawData.insert(rawData.end(), productNameVec.begin(), productNameVec.end());
  rawData.insert(rawData.end(), partNumberVec.begin(), partNumberVec.end());
  rawData.insert(rawData.end(), versionVec.begin(), versionVec.end());
  rawData.insert(rawData.end(), serialNumberVec.begin(), serialNumberVec.end());
  rawData.insert(rawData.end(), assetTagVec.begin(), assetTagVec.end());
  rawData.insert(rawData.end(), fruFileIdVec.begin(), fruFileIdVec.end());
  rawData.insert(rawData.end(), 0xC1);
  rawData.resize(8 * m_data.areaLength, 0); // fill rest of vector with zeros (padding)
 
  updateAreaChecksum(rawData.begin(), rawData.end());
  return rawData;
}

void productInfoArea::printData() {
  std::cout << "Product Area Format Version: " << std::dec << (unsigned int)m_data.formatVersion << std::endl;
  std::cout << "Product Area Length: " << (unsigned int)m_data.areaLength << std::endl;
  std::cout << "Language Code: " << (unsigned int)m_data.languageCode << std::endl;
  std::cout << "Product Manufacturer: " << m_manufacturer.getString() << std::endl;
  std::cout << "Product Name: " << m_productName.getString() << std::endl;
  std::cout << "Product Serial Number: " << m_serialNumber.getString() << std::endl;
  std::cout << "Product Part Number: " << m_partNumber.getString() << std::endl;
  std::cout << "FRU File ID: " << m_fruFileId.getString() << std::endl;
  std::cout << "Product Area Checksum: " << (unsigned int)getChecksum() << std::endl;
}

int productInfoArea::size() {
  return getBinaryData().size();
}
