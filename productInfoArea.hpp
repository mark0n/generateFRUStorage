#ifndef PRODUCTINFOAREA_HPP
#define PRODUCTINFOAREA_HPP

#include "varLengthField.hpp"
#include <cstdint>
#include <vector>

struct productInfoAreaData {
  uint8_t formatVersion : 4;
  uint8_t formatVersionPad : 4;
  uint8_t areaLength;
  uint8_t languageCode;
};

class productInfoArea {
  std::vector<uint8_t> rawData;
  struct productInfoAreaData *data;
  varLengthField manufacturer;
  varLengthField productName;
  varLengthField partNumber;
  varLengthField version;
  varLengthField serialNumber;
  varLengthField assertTag;
  varLengthField fruFileId;
public :
  productInfoArea();
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
  std::string getAssertTag();
  void setAssertTag(std::string str);
  std::string getFRUFileId();
  void setFRUFileId(std::string str);
  uint8_t getChecksum();
  std::vector<uint8_t> getBinaryData();
  void printData();
  int size();
};

#endif /* PRODUCTINFOAREA_HPP */