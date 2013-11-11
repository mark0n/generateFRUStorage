#ifndef CHECKSUM_HPP
#define CHECKSUM_HPP

#include <vector>
#include <cstdint>
#include <stdexcept>

uint8_t calcChecksum(std::vector<uint8_t>& vec);

template<class InputIterator> void updateAreaChecksum(InputIterator begin, InputIterator end)
{
  if(begin == end)
    throw std::out_of_range("Cannot update checksum of empty area.");

  uint8_t sum = 0;
  for(InputIterator i = begin; i != (end - 1); i++)
  {
    sum += *i;
  }
  *(end - 1) = -sum & 0xff;
};

#endif /* CHECKSUM_HPP */