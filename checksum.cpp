#include <vector>
#include <cstdint>
#include <stdexcept>

typedef std::vector<uint8_t>::iterator vi;

uint8_t calcChecksum(std::vector<uint8_t>& vec) {
  uint8_t sum = 0;
  for(vi i = vec.begin(); i != vec.end(); i++)
    sum += *i;
  return sum;
}

void updateAreaChecksum(std::vector<uint8_t>& vec) {
  if(vec.empty())
    throw std::out_of_range("Cannot update checksum of empty area.");

  uint8_t sum = 0;
  for(vi i = vec.begin(); i != --vec.end(); i++)
    sum += *i;
  vec.back() = -sum & 0xff;
}