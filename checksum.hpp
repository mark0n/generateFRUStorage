#ifndef CHECKSUM_HPP
#define CHECKSUM_HPP

#include <stdexcept>
#include <iterator>

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

template<class InputIterator> typename std::iterator_traits<InputIterator>::value_type calcChecksum(InputIterator cbegin, InputIterator cend)
{
  typename std::iterator_traits<InputIterator>::value_type sum = 0;
  for(InputIterator i = cbegin; i != cend; i++)
  {
    sum += *i;
  }
  return sum;
}

#endif /* CHECKSUM_HPP */