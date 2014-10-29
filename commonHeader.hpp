#ifndef COMMONHEADER_HPP
#define COMMONHEADER_HPP

#include <cstdint>
#include <vector>

struct commonHeaderData {
  uint8_t formatVersion;
  uint8_t internalUseAreaOffset;
  uint8_t chassisInfoAreaOffset;
  uint8_t boardAreaOffset;
  uint8_t productInfoAreaOffset;
  uint8_t multiRecordAreaOffset;
  uint8_t pad;
  uint8_t checksum;
};

class commonHeader {
  struct commonHeaderData m_data;
public :
  commonHeader();
  uint8_t getFormatVersion();
  uint8_t getInternalUseAreaOffset(); // in multiples of 8 bytes
  void setInternalUseAreaOffset(uint8_t offset); // in multiples of 8 bytes
  uint8_t getChassisInfoAreaOffset(); // in multiples of 8 bytes
  void setChassisInfoAreaOffset(uint8_t offset); // in multiples of 8 bytes
  uint8_t getBoardAreaOffset(); // in multiples of 8 bytes
  void setBoardAreaOffset(uint8_t offset); // in multiples of 8 bytes
  uint8_t getProductInfoAreaOffset(); // in multiples of 8 bytes
  void setProductInfoAreaOffset(uint8_t offset); // in multiples of 8 bytes
  uint8_t getMultiRecordAreaOffset(); // in multiples of 8 bytes
  void setMultiRecordAreaOffset(uint8_t offset); // in multiples of 8 bytes
  uint8_t getChecksum();
  std::vector<uint8_t> getBinaryData();
  void printData();
  int size();
};

#endif /* COMMONHEADER_HPP */