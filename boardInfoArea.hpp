#ifndef BOARDINFOAREA_HPP
#define BOARDINFOAREA_HPP

#include <cstdint>
#include <vector>
#include "varLengthField.hpp"

struct boardInfoAreaData {
  uint8_t formatVersion : 4;
  uint8_t formatVersionPad : 4;
  uint8_t areaLength;
  uint8_t languageCode;
  uint8_t mfgDateTime[3];
};

class boardInfoArea {
  std::vector<uint8_t> rawData;
  struct boardInfoAreaData *data;
  varLengthField manufacturer;
  varLengthField productName;
  varLengthField serialNumber;
  varLengthField partNumber;
  varLengthField fruFileId;
public :
  boardInfoArea();
  uint8_t getFormatVersion();
  uint8_t getBoardAreaLength(); // in multiples of 8 bytes
  uint8_t getLanguageCode();
  void setLanguageCode(uint8_t lang);
  time_t getMfgDateTime();
  void setMfgDateTime(const time_t posixTime);
  std::string getManufacturer();
  void setManufacturer(std::string str);
  std::string getProductName();
  void setProductName(std::string str);
  std::string getSerialNumber();
  void setSerialNumber(std::string str);
  std::string getPartNumber();
  void setPartNumber(std::string str);
  std::string getFRUFileId();
  void setFRUFileId(std::string str);
  uint8_t getChecksum();
  std::vector<uint8_t> getBinaryData();
  void printData();
  int size();
};

#endif /* BOARDINFOAREA_HPP */