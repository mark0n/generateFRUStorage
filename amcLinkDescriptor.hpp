#ifndef AMCLINKDESCRIPTOR_HPP
#define AMCLINKDESCRIPTOR_HPP

#include <cstdint>
#include <vector>
#include <bitset>
#include <map>

struct amcLnkDescrData {
  uint32_t amcLinkDesignator : 12;
  uint32_t amcLinkType : 8;
  uint32_t amcLinkTypeExtension : 4;
  uint32_t amcLinkGroupingId : 8;
  uint8_t amcAsymmetricMatch : 2;
  uint8_t reserved : 6;
};

const int amcLnkDescrDataSize = 5;

struct amcLinkDesignator {
  uint8_t channelId;
  std::bitset<4> laneFlag;
};

enum amcLinkType {
  AMC1PCIe = 0x02,
  AMC1PCIeAdvancedSwitching3 = 0x03,
  AMC1PCIeAdvancedSwitching4 = 0x04,
  AMC2Ethernet = 0x05,
  AMC4SerialRapidIO = 0x06,
  AMC3Storage = 0x07
};

struct amcLinkTypeMap : public std::map<std::string, amcLinkType>
{
  amcLinkTypeMap()
  {
    this->operator[]("AMC.1 PCI Express") = AMC1PCIe;
    this->operator[]("AMC.1 PCI Express Advanced Switching 3") = AMC1PCIeAdvancedSwitching3;
    this->operator[]("AMC.1 PCI Express Advanced Switching 4") = AMC1PCIeAdvancedSwitching4;
    this->operator[]("AMC.2 Ethernet") = AMC2Ethernet;
    this->operator[]("AMC.4 Serial RapidIO") = AMC4SerialRapidIO;
    this->operator[]("AMC.3 Storage") = AMC3Storage;
  };
  ~amcLinkTypeMap() {}
};

enum amcLinkTypeExtension {
  Gen1NoSpreadSpectrum = 0x00,
  Gen1SpreadSpectrum = 0x01,
  Gen2NoSpreadSpectrum = 0x02,
  Gen2SpreadSpectrum = 0x03
};

struct amcLinkTypeExtensionMap : public std::map<std::string, amcLinkTypeExtension>
{
  amcLinkTypeExtensionMap()
  {
    this->operator[]("Gen 1 non spread spectrum clock") = Gen1NoSpreadSpectrum;
    this->operator[]("Gen 1 spread spectrum clock") = Gen1SpreadSpectrum;
    this->operator[]("Gen 2 non spread spectrum clock") = Gen2NoSpreadSpectrum;
    this->operator[]("Gen 2 spread spectrum clock") = Gen2SpreadSpectrum;
  };
  ~amcLinkTypeExtensionMap() {}
};

enum asymmetricMatch {
  ExactMatch = 0x00, // matches with 00
  MatchesWith10 = 0x01, // e.g. upstream port (regular device on AMC)
  MatchesWith01 = 0x02 // e.g. downstream port (root complex or PCIe switch on AMC)
};

struct asymmetricMatchMap : public std::map<std::string, asymmetricMatch>
{
  asymmetricMatchMap()
  {
    this->operator[]("Matches with '00b' (exact match)") = ExactMatch;
    this->operator[]("Matches with '10b'") = MatchesWith10;
    this->operator[]("Matches with '01b'") = MatchesWith01;
  };
  ~asymmetricMatchMap() {}
};

class amcLinkDescriptor {
  struct amcLnkDescrData m_data;
public :
  amcLinkDescriptor(struct amcLinkDesignator, amcLinkType lnkType, int amcLinkTypeExtension, int linkGroupingId, int amcSymmetricMatch);
  std::vector<uint8_t> getBinaryData() const;
  void printData() const;
  int size() const;
};

#endif /* AMCLINKDESCRIPTOR_HPP */