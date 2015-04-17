#include "directClockDescriptor.hpp"

const uint8_t reserved = 0;

directClockDescriptor::directClockDescriptor(directPllConnection pll, directClockAsymmetricMatch match, uint8_t fam, clockAccuracyLevelAcronym acc, uint32_t freq, uint32_t min, uint32_t max)
{
  m_features.reserved = reserved;
  m_features.pllConnection = pll;
  m_features.asymmetricMatch = match;
  m_payload = std::vector<uint8_t>( (uint8_t *)&m_features, (uint8_t *)(&m_features + 1) );
  
  m_fam = fam;
  m_payload.push_back(m_fam);
  m_acc = acc;
  m_payload.push_back(m_acc);
  m_freq = freq;
  while (freq > 0)
  {
    uint8_t byte = freq % 0x100;
    m_payload.push_back(byte);
    freq /= 0x100;
  }
  m_min = min;
  while (min > 0)
  {
    uint8_t byte = min % 0x100;
    m_payload.push_back(byte);
    min /= 0x100;
  }
  m_max = max;
  while (max > 0)
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
  
}
int directClockDescriptor::size() const
{
  return m_payload.size();
}