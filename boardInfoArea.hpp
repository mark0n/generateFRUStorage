#ifndef BOARDINFOAREA_HPP
#define BOARDINFOAREA_HPP

#include <cstdint>
#include <vector>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "varLengthLangCodeField.hpp"

struct boardInfoAreaData {
  uint8_t formatVersion : 4;
  uint8_t formatVersionPad : 4;
  uint8_t areaLength;
  uint8_t languageCode;
  uint8_t mfgDateTime[3];
};

class boardInfoArea {
  struct boardInfoAreaData m_data;
  varLengthLangCodeField m_manufacturer;
  varLengthLangCodeField m_productName;
  varLengthLangCodeField m_serialNumber;
  varLengthLangCodeField m_partNumber;
  varLengthLangCodeField m_fruFileId;
  static const boost::posix_time::ptime m_epoch;
  void updateAreaLength();
public :
  boardInfoArea();
  uint8_t getFormatVersion();
  uint8_t getBoardAreaLength(); // in multiples of 8 bytes
  uint8_t getLanguageCode();
  void setLanguageCode(uint8_t lang);
  boost::posix_time::ptime getMfgDateTime();
  void setMfgDateTime(const boost::posix_time::ptime time);
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