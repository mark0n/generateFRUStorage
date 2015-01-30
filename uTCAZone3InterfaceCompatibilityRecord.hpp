#ifndef UTCAZONE3INTERFACECOMPATIBILITYRECORD_HPP
#define UTCAZONE3INTERFACECOMPATIBILITYRECORD_HPP

#include "multiRecord.hpp"
#include "interfaceIdentifierBody.hpp"
#include <list>
#include <string>
#include <vector>
#include <memory>


struct uTCAZone3InterfaceCompatibilityRecordHeader {
  uint8_t manufacturerId[3];
  uint8_t picmgRecordId;
  uint8_t recordFormatVersion;
  uint8_t interfaceIdentifier;
};

class uTCAZone3InterfaceCompatibilityRecord : public multiRecord {
public :
  uTCAZone3InterfaceCompatibilityRecord(uint8_t interface, interfaceIdentifierBody* body);
  void updateRecordLength();
  std::vector<uint8_t> getBinaryData();
  void printData();
  int size();
private :
  interfaceIdentifierBody* m_interfaceIdentifierBody;
  uTCAZone3InterfaceCompatibilityRecordHeader m_interfaceHeader;
  int bodySize;
};
#endif /* UTCAZONE3INTERFACECOMPATIBILITYRECORD_HPP */
