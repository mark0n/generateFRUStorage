#include "testUtils.hpp"
#include <string>
#include <stdexcept>

std::vector<uint8_t> applyMask(std::vector<uint8_t> data, std::vector<uint8_t> mask)
{
  if(data.size() != mask.size()) throw std::runtime_error(std::string("Internal Error in test case: data and mask must have the same length!"));
  std::vector<uint8_t>::iterator di, mi;
  for(di = data.begin(), mi = mask.begin(); di != data.end(); ++di, ++mi)
  {
    *di &= *mi;
  }
  return data;
}