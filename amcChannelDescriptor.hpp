#ifndef AMCCHANNELDESCRIPTOR_HPP
#define AMCCHANNELDESCRIPTOR_HPP

#include <cstdint>
#include <vector>

struct amcChDescrData {
  uint32_t portLane0 : 5;
  uint32_t portLane1 : 5;
  uint32_t portLane2 : 5;
  uint32_t portLane3 : 5;
  uint32_t pad : 4;
};

const int amcChDescrDataSize = 3;

class amcChannelDescriptor {
  amcChDescrData data;
public :
  amcChannelDescriptor(const std::vector<int> port);
  std::vector<uint8_t> getBinaryData() const;
  void printData() const;
  int size() const;
};

#endif /* AMCCHANNELDESCRIPTOR_HPP */