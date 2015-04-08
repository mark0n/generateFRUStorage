#include "indirectClockDescriptor.hpp"

const uint8_t reserved = 0;

indirectClockDescriptor::indirectClockDescriptor(indirectPllConnection pll, indirectClockAsymmetricMatch match, uint8_t dClockID)
{
  m_features.reserved = reserved;
  m_features.pllConnection = pll;
  m_features.asymmetricMatch = match;
  m_dClockID = dClockID;
  
  m_payload = std::vector<uint8_t>( (uint8_t *)&m_features, (uint8_t *)(&m_features + 1) );
  m_payload.push_back( m_dClockID );
}

std::vector<uint8_t> indirectClockDescriptor::getBinaryData() const
{
  return std::vector<uint8_t>( ( uint8_t * )&m_payload, ( ( uint8_t * )&m_payload ));
}

void indirectClockDescriptor::printData() const
{
  
}

int indirectClockDescriptor::size() const
{
  return m_payload.size();
}
