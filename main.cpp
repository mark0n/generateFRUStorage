/* This program generates the binary content of the IPMI FRU storage area according to
 * IPMI Platform Management FRU Information Storage Definition v1.0
 * PICMG AMC.0 R2.0. Advanced Mezzanine Card Base Specification
 * 
 * Note 1: Only a subset of the above specifications is supported. Sending patches and extension is greatly appreciated.
 * 
 * Note 2: This file generates the raw binary data. In many cases the resulting file can not be flashed into the EEPROM directly. With my Atmel processors I have to convert it into a hex file first: 
 * srec_cat fru_data.bin -binary -output fru_data.hex -intel
 */

#include "commonHeader.hpp"
#include "boardInfoArea.hpp"
#include "productInfoArea.hpp"
#include "multiRecordArea.hpp"
#include "amcChannelDescriptor.hpp"
#include "amcLinkDescriptor.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cassert>

#define EEPROM_SIZE 2048

int main() {
  commonHeader ch;
  boardInfoArea bia;
  productInfoArea pia;
  multiRecordArea mra;
  
  assert(ch.size() % 8 == 0);
  ch.setBoardAreaOffset(ch.size() / 8);

  bia.setLanguageCode(25);
  bia.setMfgDateTime(1341171180);
  bia.setManufacturer("Facility for Rare Isotope Beams");
  bia.setProductName("FRIB General Purpose Digital Board");
  bia.setSerialNumber("testBoardSerialNumber");
  bia.setPartNumber("testBoardPartNumber");

  assert(ch.size() % 8 == 0);
  assert(bia.size() % 8 == 0);
  ch.setProductInfoAreaOffset((ch.size() + bia.size()) / 8);

  pia.setLanguageCode(25);
  pia.setManufacturer("Facility for Rare Isotope Beams");
  pia.setProductName("FRIB General Purpose Digital Board");
  pia.setPartNumber("testProductPartNumber");
  pia.setVersion("testProductVersion");
  pia.setSerialNumber("testProductSerialNumber");

  assert(ch.size() % 8 == 0);
  assert(bia.size() % 8 == 0);
  assert(pia.size() % 8 == 0);
  ch.setMultiRecordAreaOffset((ch.size() + bia.size() + pia.size()) / 8);
  
  mra.addModuleCurrentRequirementsRecord(2.0);
  
  std::list<amcChannelDescriptor> chDescrs;
  const int ch0Ports[] = {0, 31, 31, 31};
  chDescrs.push_back(amcChannelDescriptor(ch0Ports));
  const int ch1Ports[] = {4, 31, 31, 31};
  chDescrs.push_back(amcChannelDescriptor(ch1Ports));
  std::list<amcLinkDescriptor> lnkDescrs;
  struct amcLinkDesignator lnkDesignator0 = {0, {true, false, false, false}};
  lnkDescrs.push_back(amcLinkDescriptor(lnkDesignator0, AMC2Ethernet, 0, 0, 0));
  struct amcLinkDesignator lnkDesignator1 = {1, {true, false, false, false}};
  lnkDescrs.push_back(amcLinkDescriptor(lnkDesignator1, AMC1PCIe, 0, 0, 2));
  mra.addAMCPtPConnectivityRecord(chDescrs, lnkDescrs);
  
  std::vector<uint8_t> multiRecord3Payload = {0x5a, 0x31, 0x00, 0x30, 0x01, 0x03, 0x3f, 0x05, 0x00, 0x00, 0x00, 0x02, 0x08};
  mra.addRecord(0xc0, multiRecord3Payload);

  std::cout << "COMMON-HEADER AREA:" << std::endl;
  ch.printData();
  std::cout << std::endl;
  std::cout << "BOARD-INFO AREA:" << std::endl;
  bia.printData();
  std::cout << std::endl;
  std::cout << "PRODUCT-INFO AREA:" << std::endl;
  pia.printData();
  std::cout << std::endl;
  std::cout << "MULTI-RECORD AREA:" << std::endl;
  mra.printData();

  const std::vector<uint8_t> biaVec = bia.getBinaryData();
  const std::vector<uint8_t> chVec = ch.getBinaryData();
  const std::vector<uint8_t> piaVec = pia.getBinaryData();
  const std::vector<uint8_t> mraVec = mra.getBinaryData();

  const int dataLength = chVec.size() + biaVec.size() + piaVec.size() + mraVec.size();
  if(dataLength > EEPROM_SIZE)
    throw std::runtime_error(std::string("Data does not fit into EEPROM."));
  
  const std::vector<uint8_t> padVec(EEPROM_SIZE - dataLength);

  std::ofstream outfile;
  outfile.open("fru_data.bin", std::ios::binary);
  outfile.write((char const *)chVec.data(), chVec.size());
  outfile.write((char const *)biaVec.data(), biaVec.size());
  outfile.write((char const *)piaVec.data(), piaVec.size());
  outfile.write((char const *)mraVec.data(), mraVec.size());
  outfile.write((char const *)padVec.data(), padVec.size());
  outfile.close();
  return 0;
}