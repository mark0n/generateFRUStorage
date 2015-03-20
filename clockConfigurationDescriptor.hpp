#ifndef CLOCKCONFIGURATIONDESCRIPTOR_HPP
#define	CLOCKCONFIGURATIONDESCRIPTOR_HPP

#include <cstdint>
#include <vector>
#include <bitset>
#include <map>

struct clockConfigurationData {
  uint32_t clockID : 8;
  uint32_t clockControl : 8;
};

enum clockID {
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

class clockConfigurationDescriptor {
  struct clockConfigurationData m_data;
public :
  clockConfigurationDescriptor(clockID ID, uint8_t control, std::list<indirectClockDescriptors> indirect, std::list<directClockDescriptors> direct);
  std::vector<uint8_t> getBinaryData() const;
  void printData() const;
  int size() const;
  int clockLnkDescrDataSize;
};

#endif	/* CLOCKCONFIGURATIONDESCRIPTOR_HPP */

