#ifndef CLOCKCONFIGURATIONRECORD_HPP
#define	CLOCKCONFIGURATIONRECORD_HPP

#include "multiRecord.hpp"
#include "clockConfigurationDescriptor.hpp"
#include <list>
#include <cstdint>
#include <map>
#include <vector>
#include <bitset>

struct clockConfigurationRecordHeader {
  uint8_t manufacturerId[3];
  uint8_t picmgRecordId;
  uint8_t recordFormatVersion;
};

struct resourceIDDefinition {
  uint8_t deviceID : 4;
  uint8_t idType : 4;
};

enum resourceIDResourceType {
  OnCarrierDevice = 0,
  AMCModule = 4,
  Backplane = 8
};

struct resourceIDResourceTypeMap : public std::map<std::string, resourceIDResourceType>
{
  resourceIDResourceTypeMap()
  {
    this->operator[]("On-CarrierDevice") = OnCarrierDevice;
    this->operator[]("AMCModule") = AMCModule;
    this->operator[]("Backplane") = Backplane;
  };
  ~resourceIDResourceTypeMap() {}
};

class clockConfigurationRecord : public multiRecord {
public :
  clockConfigurationRecord(resourceIDResourceType rID, uint8_t dID, std::list<clockConfigurationDescriptor> clockDescriptors);
  void updateRecordLength();
  std::vector<uint8_t> getBinaryData();
  void printData();
  int size();
private:
  clockConfigurationRecordHeader m_clockConfigurationHeader;
  std::list<clockConfigurationDescriptor> m_clockDescriptors;
  uint8_t m_deviceIdentification = 0x0;
  resourceIDDefinition m_resourceIDDefinition;
};

#endif	/* CLOCKCONFIGURATIONRECORD_HPP */

