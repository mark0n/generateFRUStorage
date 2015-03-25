#ifndef CLOCKCONFIGURATIONRECORD_HPP
#define	CLOCKCONFIGURATIONRECORD_HPP

#include "multiRecord.hpp"
#include "clockConfigurationDescriptor.hpp"
#include <list>
#include <cstdint>

struct clockConfigurationRecordHeader {
  uint8_t manufacturerId[3];
  uint8_t picmgRecordId;
  uint8_t recordFormatVersion;
};

struct resourceIDDefinition {
  uint8_t idType;
  unit8_t reserved;
  uint8_t deviceID;
};

enum resourceIDResourceType {
  On-CarrierDevice = 0x00;
  AMCModule = 0x40;
  Backplane = 0x80;
};

struct resourceIDResourceTypeMap : public std::map<std::string, resourceIDResourceType>
{
  resourceIDResourceTypeMap()
  {
    this->operator[]("On-Carrier Device") = On-CarrierDevice;
    this->operator[]("AMC Module") = AMCModule;
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

