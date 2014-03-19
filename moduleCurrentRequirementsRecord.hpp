#ifndef MODULECURRENTREQUIREMENTSRECORD_HPP
#define MODULECURRENTREQUIREMENTSRECORD_HPP

#include "multiRecord.hpp"

struct payloadFormat {
  uint8_t manufacturerId[3];
  uint8_t picmgRecordId;
  uint8_t recordFormatVersion;
  uint8_t currentDraw;
};

class moduleCurrentRequirementsRecord : public multiRecord {
  payloadFormat data;
public :
  moduleCurrentRequirementsRecord(double currentDraw);
  std::vector<uint8_t> getBinaryData();
  void printData();
};

#endif /* MODULECURRENTREQUIREMENTSRECORD_HPP */