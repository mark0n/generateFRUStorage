#include "clockConfigurationDescriptor.hpp"
#include <iostream>
#include <stdexcept>

clockConfigurationDescriptor::clockConfigurationDescriptor(clockID ID, clockActivationControl control, int inCount, int dCount)
{
  if(inCount != 0 && dCount != 0)
  {
    throw std::runtime_error("ERROR: Indirect and Direct Clock Descriptors Found!");
    exit(1);
  }else if(inCount ==0 && dCount == 0)
  {
    throw std::runtime_error("ERROR: No Indirect or Direct Clock Descriptors Found!");
    exit(1);
  }
  m_data.indirectCount = inCount;
  m_data.directCount = dCount;
  m_data.clockID = ID;
  m_data.clockControl = control;
  m_payload = std::vector<uint8_t>( (uint8_t *)&m_data, (uint8_t *)(&m_data + 1) );
}

void clockConfigurationDescriptor:: addIndirectDescrs(std::list<indirectClockDescriptor> indirectDescrs)
{
  m_indirect = indirectDescrs;
  for(std::list<indirectClockDescriptor>::const_iterator li = m_indirect.begin(); li != m_indirect.end(); li++)
  {
    std::vector<uint8_t> ind = li->getBinaryData();
    std::copy(ind.begin(), ind.end(), std::back_inserter(m_payload));
  }
}

void clockConfigurationDescriptor:: addDirectDescrs(std::list<directClockDescriptor> directDescrs)
{
  m_direct = directDescrs;
  for(std::list<directClockDescriptor>::const_iterator li = m_direct.begin(); li != m_direct.end(); li++)
  {
    std::vector<uint8_t> dir = li->getBinaryData();
    std::copy(dir.begin(), dir.end(), std::back_inserter(m_payload));
  }
}

std::vector<uint8_t> clockConfigurationDescriptor::getBinaryData() const
{
  return m_payload;
}

void clockConfigurationDescriptor::printData() const
{
  std::cout << "Clock Configuration Clock ID: " << (int)m_data.clockID << std::endl;
  std::cout << "Clock Configuration Clock Control: " << (int)m_data.clockControl << std::endl;
  int i = 0;
  for(std::list<indirectClockDescriptor>::const_iterator li = m_indirect.begin(); li != m_indirect.end(); li++, i++)
  {
    std::cout << "Indirect Clock Descriptor #" << i << ":" << std::endl;
    li->printData();
  }
  i = 0;
  for(std::list<directClockDescriptor>::const_iterator li = m_direct.begin(); li != m_direct.end(); li++, i++)
  {
    std::cout << "Direct Clock Descriptor #" << i << ":" << std::endl;
    li->printData();
  }
}

int clockConfigurationDescriptor::size() const
{
  return m_payload.size();
}