#ifndef INDIRECTCLOCKDESCRIPTOR_HPP
#define	INDIRECTCLOCKDESCRIPTOR_HPP

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

class indirectClockDescriptor {
public :
  indirectClockDescriptor(pllConnection pll, clockAsymmetricMatch match, uint8_t dClockID);
  std::vector<uint8_t> getBinaryData() const;
  void printData() const;
  int size() const;
private :
  struct clockFeatures m_features;
  uint8_t m_dClockID;
  std::vector<uint8_t> m_payload;
};

#endif	/* INDIRECTCLOCKDESCRIPTOR_HPP */

