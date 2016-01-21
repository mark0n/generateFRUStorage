#ifndef INTERFACEIDENTIFIERBODY_HPP
#define	INTERFACEIDENTIFIERBODY_HPP

#include <vector>
#include <string>
#include <stdexcept>

struct picmgSpecificationInterfaceIdentifier {
  uint8_t identifier[4] = {0x00};
  uint8_t major = 0x00;
  uint8_t minor = 0x00;
};

struct interfaceIdentifierGUID {
  uint8_t guid[16] = {0x00};
};

struct interfaceIdentifierOEM {
  uint8_t idana[3] = {0x00};
  uint8_t designator[4] = {0x00};
};

struct picmgMTCAREPNumber {
  uint8_t mtcaRepNumber[4] = {0x00};
};

class interfaceIdentifierBody {
public:
  interfaceIdentifierBody(uint8_t interfaceIdentifier, std::vector<std::string> body);
  virtual ~interfaceIdentifierBody();
  std::vector<uint8_t> getBinaryData() const;
  void printData();
  int size() const;
private:
  struct picmgSpecificationInterfaceIdentifier m_data1;
  struct interfaceIdentifierGUID m_data2;
  struct interfaceIdentifierOEM m_data3;
  struct picmgMTCAREPNumber m_data4;
  uint8_t m_identifier = 0x00;
  int m_interfaceIdentifierBodyDataSize = 0;
  std::vector<uint8_t> m_opaque;
};

#endif	/* INTERFACEIDENTIFIERBODY_HPP */

