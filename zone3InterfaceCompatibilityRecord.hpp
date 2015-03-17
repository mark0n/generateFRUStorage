#ifndef ZONE3INTERFACECOMPATIBILITYRECORD_HPP
#define ZONE3INTERFACECOMPATIBILITYRECORD_HPP

#include "multiRecord.hpp"
#include "interfaceIdentifierBody.hpp"
#include <list>
#include <string>
#include <vector>
#include <memory>


struct zone3InterfaceCompatibilityRecordHeader {
  uint8_t manufacturerId[3];
  uint8_t picmgRecordId;
  uint8_t recordFormatVersion;
  uint8_t interfaceIdentifier;
};

class zone3InterfaceCompatibilityRecord : public multiRecord {
public :
  zone3InterfaceCompatibilityRecord(uint8_t interface, interfaceIdentifierBody* body);
  void updateRecordLength();
  std::vector<uint8_t> getBinaryData();
  void printData();
  int size();
private :
  interfaceIdentifierBody* m_interfaceIdentifierBody;
  zone3InterfaceCompatibilityRecordHeader m_interfaceHeader;
  int m_bodySize = 0;
};
#endif /* ZONE3INTERFACECOMPATIBILITYRECORD_HPP */
