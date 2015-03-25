#include "clockConfigurationDescriptor.hpp"
#include <iostream>

clockConfigurationDescriptor::clockConfigurationDescriptor(clockID ID, clockConfigurationControl control, std::list<indirectClockDescriptor> indirect, std::list<directClockDescriptor> direct) {
  m_configurationData.clockID = ID;
  m_configurationData.clockControl = control;
  m_indirect = indirect;
  m_direct = direct;
  
  m_payload.push_back( m_configurationData );
  m_payload.push_back( m_indirect.size() );
  m_payload.push_back( m_direct.size() );
  
  for(std::list<indirectClockDescriptor>::const_iterator li = m_indirect.begin(); li != m_indirect.end(); li++) {
    std::vector<uint8_t> ind = li->getBinaryData();
    std::copy(ind.begin(), ind.end(), std::back_inserter(m_payload));
  }
  for(std::list<directClockDescriptor>::const_iterator li = m_direct.begin(); li != m_direct.end(); li++) {
    std::vector<uint8_t> dir = li->getBinaryData();
    std::copy(dir.begin(), dir.end(), std::back_inserter(m_payload));
  }
  
}

std::vector<uint8_t> clockConfigurationDescriptor::getBinaryData() const {
  return std::vector<uint8_t>( ( uint8_t * )&m_payload, ( ( uint8_t * )&m_payload ));
}

void clockConfigurationDescriptor::printData() const {
}

int clockConfigurationDescripto::size() const {
  return m_payload.size();
}