#include "clockConfigurationDescriptor.hpp"
#include <iostream>
#include <list>

clockConfigurationDescriptor::clockConfigurationDescriptor(clockID ID, clockActivationControl control, std::list<indirectClockDescriptor> indirect, std::list<directClockDescriptor> direct) {
  m_data.clockID = ID;
  m_data.clockControl = control;
  m_data.indirectCount = indirect.size();
  m_data.directCount = direct.size();
  m_indirect = indirect;
  m_direct = direct;
  
  m_payload = std::vector<uint8_t>( (uint8_t *)&m_data, (uint8_t *)(&m_data + 1) );
  
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
  return m_payload;
}

void clockConfigurationDescriptor::printData() const {
  std::cout << "Clock Configuration Clock ID: " << (int)m_data.clockID << std::endl;
  std::cout << "Clock Configuration Clock Control: " << m_data.clockControl << std::endl;
  int i = 0;
  for(std::list<indirectClockDescriptor>::const_iterator li = m_indirect.begin(); li != m_indirect.end(); li++, i++) {
    std::cout << "Indirect Clock Descriptor #" << std::dec << i << ":" << std::endl;
    li->printData();
  }
  i = 0;
  for(std::list<directClockDescriptor>::const_iterator li = m_direct.begin(); li != m_direct.end(); li++, i++) {
    std::cout << "Direct Clock Descriptor #" << std::dec << i << ":" << std::endl;
    li->printData();
  }
}

int clockConfigurationDescriptor::size() const {
  return m_payload.size();
}

