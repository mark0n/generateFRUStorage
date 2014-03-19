#ifndef MULTIRECORD_HPP
#define MULTIRECORD_HPP

#include <cstdint>
#include <vector>

#define RECORD_TYPE_OEM 0xc0
#define PICMG_MANUFACTURER_ID_MSB 0x00
#define PICMG_MANUFACTURER_ID_MID 0x31
#define PICMG_MANUFACTURER_ID_LSB 0x5a

struct multiRecordHeader {
  uint8_t recordTypeId;
  uint8_t recordFormatVersion : 4;
  uint8_t reserved : 3;
  uint8_t endOfList : 1;
  uint8_t recordLength;
  uint8_t recordChecksum;
  uint8_t headerChecksum;
};

class multiRecord {
protected :
  struct multiRecordHeader header;
  std::vector<uint8_t> payload;
  void updateRecordChecksum();
  void updateHeaderChecksum();
public :
  multiRecord(uint8_t typeId, std::vector<uint8_t> payload);
  uint8_t getFormatVersion();
  uint8_t getEndOfList();
  void setEndOfList(bool endOfList);
  uint8_t getRecordLength();
  uint8_t getChecksum();
  uint8_t getHeaderChecksum();
  virtual std::vector<uint8_t> getBinaryData();
  virtual void printData();
  virtual int size();
};

#endif /* MULTIRECORD_HPP */