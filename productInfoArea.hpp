#ifndef PRODUCTINFOAREA_HPP
#define PRODUCTINFOAREA_HPP

#include "varLengthLangCodeField.hpp"
#include <cstdint>
#include <vector>

struct productInfoAreaData {
  uint8_t formatVersion : 4;
  uint8_t formatVersionPad : 4;
  uint8_t areaLength;
  uint8_t languageCode;
};

class productInfoArea {
  struct productInfoAreaData m_data;
  varLengthLangCodeField m_manufacturer;
  varLengthLangCodeField m_productName;
  varLengthLangCodeField m_partNumber;
  varLengthLangCodeField m_version;
  varLengthLangCodeField m_serialNumber;
  varLengthLangCodeField m_assetTag;
  varLengthLangCodeField m_fruFileId;
public :
  productInfoArea();
  void updateAreaLength();
  uint8_t getFormatVersion();
  uint8_t getProductAreaLength(); // in multiples of 8 bytes
  uint8_t getLanguageCode();
  void setLanguageCode(uint8_t lang);
  std::string getManufacturer();
  void setManufacturer(std::string str);
  std::string getProductName();
  void setProductName(std::string str);
  std::string getPartNumber();
  void setPartNumber(std::string str);
  std::string getVersion();
  void setVersion(std::string str);
  std::string getSerialNumber();
  void setSerialNumber(std::string str);
  std::string getAssetTag();
  void setAssetTag(std::string str);
  std::string getFRUFileId();
  void setFRUFileId(std::string str);
  uint8_t getChecksum();
  std::vector<uint8_t> getBinaryData();
  void printData();
  int size();
};

#endif /* PRODUCTINFOAREA_HPP */
