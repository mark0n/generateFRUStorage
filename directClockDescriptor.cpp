#include "directClockDescriptor.hpp"
#include <stdexcept>
#include <iostream>

const uint8_t reserved = 0;

directClockDescriptor::directClockDescriptor(directPllConnection pll, directClockAsymmetricMatch match, uint8_t fam, clockAccuracyLevelAcronym acc, uint32_t freq, uint32_t min, uint32_t max)
{
  if(fam > 2 && fam < 201)
  {
    throw std::out_of_range("Clock Family definition out of valid range");
  }
  
  m_features.reserved = reserved;
  m_features.pllConnection = pll;
  m_features.asymmetricMatch = match;
  m_payload = std::vector<uint8_t>( (uint8_t *)&m_features, (uint8_t *)(&m_features + 1) );
  
  m_fam = fam;
  m_payload.push_back(m_fam);
  m_acc = acc;
  m_payload.push_back(m_acc);
  m_freq = freq;
  for (int i = 0; i < 4; i++)
  {
    uint8_t byte = freq % 0x100;
    m_payload.push_back(byte);
    freq /= 0x100;
  }
  m_min = min;
  for (int i = 0; i < 4; i++)
  {
    uint8_t byte = min % 0x100;
    m_payload.push_back(byte);
    min /= 0x100;
  }
  m_max = max;
  for (int i = 0; i < 4; i++)
  {
    uint8_t byte = max % 0x100;
    m_payload.push_back(byte);
    max /= 0x100;
  }
}

std::vector<uint8_t> directClockDescriptor::getBinaryData() const
{
  return m_payload;
}
void directClockDescriptor::printData() const
{
  std::cout << "PLL Connection: " << std::dec << (int)m_features.pllConnection << std::endl;
  std::cout << "Clock Asymmetric Match: " << std::dec << (int)m_features.asymmetricMatch << std::endl;
  std::cout << "Clock Family: " << std::hex << m_fam << std::endl;
  std::cout << "Clock Accuracy Level: " << std::dec << (int)m_acc << std::endl;
  std::cout << "Clock Frequency: " << std::dec << (int)m_freq << std::endl;
  std::cout << "Minimum Clock Frequency: " << std::dec << (int)m_min << std::endl;
  std::cout << "Maximum Clock Frequency: " << std::dec << (int)m_max << std::endl;
}
int directClockDescriptor::size() const
{
  return m_payload.size();
}