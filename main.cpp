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
#include <boost/date_time/posix_time/posix_time.hpp>
#include <config.h>
#include <getopt.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#define EEPROM_SIZE 2048

int main(int argc, char **argv) {
  int opt;
  while((opt = getopt(argc, argv, "V")) != EOF) {
    switch (opt)
    {
      case 'V':
        std::cout << argv[0] << " " << VERSION_STRING << std::endl;
        exit(0);
      default:
        exit(1);
    }
  }

  using boost::property_tree::ptree;
  ptree pt;

  read_json("../FRU_data_FGPDB.json", pt);

  commonHeader ch;
  boardInfoArea bia;
  productInfoArea pia;
  multiRecordArea mra;
  
  assert(ch.size() % 8 == 0);
  ch.setBoardAreaOffset(ch.size() / 8);

  bia.setLanguageCode(pt.get<int>("BoardInfoArea.LanguageCode"));
  bia.setMfgDateTime(boost::posix_time::ptime(boost::posix_time::second_clock::universal_time()));
  bia.setManufacturer(pt.get<std::string>("BoardInfoArea.Manufacturer"));
  bia.setProductName(pt.get<std::string>("BoardInfoArea.ProductName"));
  bia.setSerialNumber(pt.get<std::string>("BoardInfoArea.SerialNumber"));
  bia.setPartNumber(pt.get<std::string>("BoardInfoArea.PartNumber"));
  bia.setFRUFileId(pt.get<std::string>("BoardInfoArea.FRUFileId"));

  assert(ch.size() % 8 == 0);
  assert(bia.size() % 8 == 0);
  ch.setProductInfoAreaOffset((ch.size() + bia.size()) / 8);

  pia.setLanguageCode(pt.get<int>("ProductInfoArea.LanguageCode"));
  pia.setManufacturer(pt.get<std::string>("ProductInfoArea.Manufacturer"));
  pia.setProductName(pt.get<std::string>("ProductInfoArea.ProductName"));
  pia.setPartNumber(pt.get<std::string>("ProductInfoArea.PartNumber"));
  pia.setVersion(pt.get<std::string>("ProductInfoArea.Version"));
  pia.setSerialNumber(pt.get<std::string>("ProductInfoArea.SerialNumber"));
  pia.setAssetTag(pt.get<std::string>("ProductInfoArea.AssetTag"));
  pia.setFRUFileId(pt.get<std::string>("ProductInfoArea.FRUFileId"));

  assert(ch.size() % 8 == 0);
  assert(bia.size() % 8 == 0);
  assert(pia.size() % 8 == 0);
  ch.setMultiRecordAreaOffset((ch.size() + bia.size() + pia.size()) / 8);
  
  mra.addModuleCurrentRequirementsRecord(pt.get<double>("MultiRecordArea.CurrentRequirementsRecord.Current"));
  
  std::list<amcChannelDescriptor> chDescrs;
  for(const ptree::value_type &v: pt.get_child("MultiRecordArea.AMCPtPConnectivityRecord.AMCChannelDescriptors"))
  {
    std::vector<int> ports;
    for(int i = 0; i < 4; i++)
    {
      ports.push_back(v.second.get<int>("Lane" + std::to_string(i) + "PortNumber"));
    }
    chDescrs.push_back(amcChannelDescriptor(ports));
  }

  std::list<amcLinkDescriptor> lnkDescrs;
  uint8_t amcChannelId = 0;
  for(const ptree::value_type &v: pt.get_child("MultiRecordArea.AMCPtPConnectivityRecord.AMCLinkDescriptors"))
  {
    std::bitset<4> lanesIncluded;
    for(int lane = 0; lane < 4; lane++)
    {
      lanesIncluded[lane] = v.second.get<bool>("AMCLinkDesignator.Lane" + std::to_string(lane) + "Included");
    }
    struct amcLinkDesignator lnkDesignator = { amcChannelId, lanesIncluded };

    amcLinkTypeMap lnkTypeMap;
    amcLinkType lnkType = lnkTypeMap[v.second.get<std::string>("AMCLinkType")];

    amcLinkTypeExtensionMap lnkTypeExtensionMap;
    amcLinkTypeExtension lnkTypeExtension = lnkTypeExtensionMap[v.second.get<std::string>("AMCLinkTypeExtension")];

    asymmetricMatchMap asymMatchMap;
    asymmetricMatch asymMatch = asymMatchMap[v.second.get<std::string>("AsymmetricMatch")];

    int lnkGroupingId = v.second.get<int>("LinkGroupingID");
    lnkDescrs.push_back(amcLinkDescriptor(lnkDesignator, lnkType, lnkTypeExtension, lnkGroupingId, asymMatch));

    amcChannelId++;
  }

  mra.addAMCPtPConnectivityRecord(chDescrs, lnkDescrs);

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