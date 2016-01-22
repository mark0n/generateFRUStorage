#ifndef INDIRECTCLOCKDESCRIPTOR_HPP
#define	INDIRECTCLOCKDESCRIPTOR_HPP

#include <list>
#include <cstdint>
#include <map>
#include <vector>
#include <bitset>

struct indirectClockFeatures
{
  uint8_t asymmetricMatch : 1;
  uint8_t pllConnection : 1;
  uint8_t reserved : 6;
};

enum indirectPllConnection
{
  IndirectConnected = 1,
  IndirectNotConnected = 0
};

struct indirectPllConnectionMap : public std::map<std::string, indirectPllConnection>
{
  indirectPllConnectionMap()
  {
    this->operator[]("Connected through PLL") = IndirectConnected;
    this->operator[]("Not connected through PLL") = IndirectNotConnected;
  };
  ~indirectPllConnectionMap() {}
};

enum indirectClockAsymmetricMatch
{
  IndirectSource = 1,
  IndirectReciever = 0
};

struct indirectClockAsymmetricMatchMap : public std::map<std::string, indirectClockAsymmetricMatch>
{
  indirectClockAsymmetricMatchMap()
  {
    this->operator[]("Clock source") = IndirectSource;
    this->operator[]("Clock receiver") = IndirectReciever;
  };
  ~indirectClockAsymmetricMatchMap() {}
};

class indirectClockDescriptor
{
public :
  indirectClockDescriptor(indirectPllConnection pll, indirectClockAsymmetricMatch match, uint8_t dClockID);
  std::vector<uint8_t> getBinaryData() const;
  void printData() const;
  int size() const;
private :
  indirectClockFeatures m_features;
  uint8_t m_dClockID;
  std::vector<uint8_t> m_payload;
};

#endif	/* INDIRECTCLOCKDESCRIPTOR_HPP */
