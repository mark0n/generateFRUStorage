#ifndef CLOCKCONFIGURATIONDESCRIPTOR_HPP
#define	CLOCKCONFIGURATIONDESCRIPTOR_HPP

#include "indirectClockDescriptor.hpp"
#include "directClockDescriptor.hpp"
#include <cstdint>
#include <vector>
#include <bitset>
#include <map>
#include <list>

struct clockConfigurationData
{
  uint8_t clockID : 8;
  uint8_t clockControl : 8;
  uint8_t indirectCount : 8;
  uint8_t directCount : 8;
};

enum clockID
{
  TCLKA = 0x01,
  TCLKB = 0x02,
  TCLKC = 0x03,
  TCLKD = 0x04,
  FCLKA = 0x05,
  CLK1A = 0x01,
  CLK1B = 0x02,
  CLK1 = 0x03,
  CLK2A = 0x04,
  CLK2B = 0x05,
  CLK2 = 0x06,
  CLK3A = 0x07,
  CLK3B = 0x08,
  CLK3 = 0x09
};

struct clockIDMap : public std::map<std::string, clockID>
{
  clockIDMap()
  {
    this->operator[]("TCLKA") = TCLKA;
    this->operator[]("TCLKB") = TCLKB;
    this->operator[]("TCLKC") = TCLKC;
    this->operator[]("TCLKD") = TCLKD;
    this->operator[]("FCLKA") = FCLKA;
    this->operator[]("CLK1A") = CLK1A;
    this->operator[]("CLK1B") = CLK1B;
    this->operator[]("CLK1") = CLK1;
    this->operator[]("CLK2A") = CLK2A;
    this->operator[]("CLK2B") = CLK2B;
    this->operator[]("CLK2") = CLK2;
    this->operator[]("CLK3A") = CLK3A;
    this->operator[]("CLK3B") = CLK3B;
    this->operator[]("CLK3") = CLK3;
  };
  ~clockIDMap() {}
};

enum clockActivationControl
{
  ABCarrierIPMC = 0x00,
  ABApp = 0x01
};

struct clockActivationControlMap : public std::map<std::string, clockActivationControl>
{
  clockActivationControlMap()
  {
    this->operator[]("Activated by Carrier IPMC") = ABCarrierIPMC;
    this->operator[]("Activated by application") = ABApp;
  };
  ~clockActivationControlMap() {}
};

class clockConfigurationDescriptor
{
public :
  clockConfigurationDescriptor(clockID ID, clockActivationControl control, int inCount, int dCount);
  std::vector<uint8_t> getBinaryData() const;
  void printData() const;
  int size() const;
  void addIndirectDescrs(std::list<indirectClockDescriptor> indirectDescrs);
  void addDirectDescrs(std::list<directClockDescriptor> directDescrs);
private :
  clockConfigurationData m_data;
  std::list<indirectClockDescriptor> m_indirect;
  std::list<directClockDescriptor> m_direct;
  std::vector<uint8_t> m_payload;
};

#endif	/* CLOCKCONFIGURATIONDESCRIPTOR_HPP */
