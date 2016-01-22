#ifndef DIRECTCLOCKDESCRIPTOR_HPP
#define	DIRECTCLOCKDESCRIPTOR_HPP

#include <list>
#include <cstdint>
#include <map>
#include <vector>
#include <bitset>

struct directClockFeatures
{
  uint8_t asymmetricMatch : 1;
  uint8_t pllConnection : 1;
  uint8_t reserved : 6;
};

enum directPllConnection
{
  DirectConnected = 1,
  DirectNotConnected = 0
};

struct directPllConnectionMap : public std::map<std::string, directPllConnection>
{
  directPllConnectionMap()
  {
    this->operator[]("Connected through PLL") = DirectConnected;
    this->operator[]("Not connected through PLL") = DirectNotConnected;
  };
  ~directPllConnectionMap() {}
};

enum directClockAsymmetricMatch
{
  DirectSource = 1,
  DirectReciever = 0
};

struct directClockAsymmetricMatchMap : public std::map<std::string, directClockAsymmetricMatch>
{
  directClockAsymmetricMatchMap()
  {
    this->operator[]("Clock source") = DirectSource;
    this->operator[]("Clock receiver") = DirectReciever;
  };
  ~directClockAsymmetricMatchMap() {}
};

enum clockAccuracyLevelAcronym
{
  PRS = 0x0A,
  STU = 0x14,
  ST2 = 0x1E,
  TNC = 0x28,
  ST3E = 0x32,
  ST3 = 0x3C,
  SMC = 0x46,
  ST4 = 0x50,
  DUS = 0x5a
};

struct clockAccuracyLevelAcronymMap : public std::map<std::string, clockAccuracyLevelAcronym>
{
  clockAccuracyLevelAcronymMap()
  {
    this->operator[]("PRS") = PRS;
    this->operator[]("STU") = STU;
    this->operator[]("ST2") = ST2;
    this->operator[]("TNC") = TNC;
    this->operator[]("ST3E") = ST3E;
    this->operator[]("ST3") = ST3;
    this->operator[]("SMC") = SMC;
    this->operator[]("ST4") = ST4;
    this->operator[]("DUS") = DUS;
  };
  ~clockAccuracyLevelAcronymMap() {}
};

class directClockDescriptor
{
public :
  directClockDescriptor(directPllConnection pll, directClockAsymmetricMatch match, uint8_t fam, clockAccuracyLevelAcronym acc, uint32_t freq, uint32_t min, uint32_t max);
  std::vector<uint8_t> getBinaryData() const;
  void printData() const;
  int size() const;
private :
  directClockFeatures m_features;
  uint8_t m_fam;
  clockAccuracyLevelAcronym m_acc;
  uint32_t m_freq;
  uint32_t m_min;
  uint32_t m_max;
  std::vector<uint8_t> m_payload;
};

#endif	/* DIRECTCLOCKDESCRIPTOR_HPP */
