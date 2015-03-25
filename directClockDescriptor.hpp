#ifndef DIRECTCLOCKDESCRIPTOR_HPP
#define	DIRECTCLOCKDESCRIPTOR_HPP

struct clockFeatures {
  uint8_t reserved : 6;
  uint8_t pllConnection : 1;
  uint8_t asymmetricMatch : 1;
};

enum pllConnection {
  Connected = 1,
  NotConnected = 0
};

struct pllConnectionMap : public std::map<std::string, pllConnectionID>
{
  pllConnectionMap()
  {
    this->operator[]("ConnectedThroughPLL") = Connected;
    this->operator[]("NotConnectedThroughPLL") = NotConnected;
  };
  ~pllConnectionMap() {}
};

enum clockAsymmetricMatch {
  Source = 1,
  Reciever = 0
};

struct clockAsymmetricMatchMap : public std::map<std::string, clockAsymmetricMatch>
{
  clockAsymmetricMatchMap()
  {
    this->operator[]("ClockSource") = Source;
    this->operator[]("ClockReciever") = Reciever;
  };
  ~clockAsymmetricMatchMap() {}
};

enum clockAccuracyLevelAcronym {
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

struct clockAccuracyLevelAcronym : public std::map<std::string, clockAccuracyLevelAcronym>
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

class directClockDescriptor {
public :
  directClockDescriptor(pllConnection pll, clockAsymmetricMatch match, uint8_t fam, clockAccuracyLevelAcronym acc, uint32_t freq, uint32_t min, uint32_t max);
  std::vector<uint8_t> getBinaryData() const;
  void printData() const;
  int size() const;
private :
  struct pllConnection m_pll;
  struct clockAsymmetricMatch m_match;
  uint8_t m_fam;
  struct clockAccuracyLevelAcronym m_acc;
  uint32_t m_freq;
  uint32_t m_min;
  uint32_t m_max;
  std::vector<uint8_t> m_payload;
};

#endif	/* DIRECTCLOCKDESCRIPTOR_HPP */

