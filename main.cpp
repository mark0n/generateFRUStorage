/* This program generates the binary content of the IPMI FRU storage area
 * according to IPMI Platform Management FRU Information Storage Definition
 * v1.0 PICMG AMC.0 R2.0. Advanced Mezzanine Card Base Specification
 * 
 * Note 1: Only a subset of the above specifications is supported. Sending
 * patches and extension is greatly appreciated.
 * 
 * Note 2: This program generates the raw binary data. In some cases the
 * resulting file can not be flashed into the EEPROM directly using JTAG. When
 * using my Atmel programmer I have to convert it into a hex file first:
 * srec_cat fru_data.bin -binary -output fru_data.hex -intel
 */

#include "commonHeader.hpp"
#include "boardInfoArea.hpp"
#include "productInfoArea.hpp"
#include "multiRecordArea.hpp"
#include "amcChannelDescriptor.hpp"
#include "amcLinkDescriptor.hpp"
#include "interfaceIdentifierBody.hpp"
#include "zone3InterfaceCompatibilityRecord.hpp"
#include "clockConfigurationDescriptor.hpp"
#include "clockConfigurationRecord.hpp"
#include "indirectClockDescriptor.hpp"
#include "directClockDescriptor.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cassert>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "config.h"
#include <getopt.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/optional.hpp>
#include <string>

#define EEPROM_SIZE 2048

int main(int argc, char **argv) {
  int opt;
  bool debugMode;
  std::string inFileName;
  std::string outFileName;
  while((opt = getopt(argc, argv, "Vdi:o:")) != EOF) {
    switch (opt)
    {
      case 'V':
        std::cout << argv[0] << " " << VERSION_STRING << std::endl;
        exit(0);
      case 'd':
        debugMode = true;
        break;
      case 'i':
        inFileName = optarg;
        break;
      case 'o':
        outFileName = optarg;
        break;
      case '?':
        if(optopt == 'i' or optopt == 'o')
        {
          std::cerr << "ERROR: Option -" << static_cast<char>(optopt) << " requires an argument!" << std::endl;
          exit(1);
        }
        else
        {
          std::cerr << "ERROR: Invalid argument '" << static_cast<char>(opt) << "'!" << std::endl;
          exit(2);
        }
      default:
        assert("Error reading arguments.");
    }
  }
  if(inFileName.empty())
  {
    std::cerr << "ERROR: No input file name specified!" << std::endl;
    exit(3);
  }
  if(outFileName.empty())
  {
    std::cerr << "ERROR: No output file name specified!" << std::endl;
    exit(4);
  }

  using boost::property_tree::ptree;
  ptree pt;

  read_json(inFileName, pt);

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
  
  boost::optional<double> current = pt.get_optional<double>("MultiRecordArea.CurrentRequirementsRecord.Current");
  if(current)
  {
      mra.addModuleCurrentRequirementsRecord(*current);
  }
  
  
  boost::optional<ptree&> ptpRecord = pt.get_child_optional("MultiRecordArea.AMCPtPConnectivityRecord");
  if(ptpRecord)
  {
    std::list<amcChannelDescriptor> chDescrs;
    std::list<amcLinkDescriptor> lnkDescrs;
    uint8_t amcChannelId = 0;
    for(const ptree::value_type &v: pt.get_child("MultiRecordArea.AMCPtPConnectivityRecord.AMCChannelDescriptors"))
    {
      std::vector<int> ports;
      for(int i = 0; i < 4; i++)
      {
        ports.push_back(v.second.get<int>("Lane" + std::to_string(i) + "PortNumber"));
      }
      
      for(const ptree::value_type &w: v.second.get_child("AMCLinkDescriptors"))
      {
        std::bitset<4> lanesIncluded;
        for(int lane = 0; lane < 4; lane++)
        {
          lanesIncluded[lane] = w.second.get<bool>("AMCLinkDesignator.Lane" + std::to_string(lane) + "Included");
        }
        struct amcLinkDesignator lnkDesignator = { amcChannelId, lanesIncluded };

        amcLinkTypeMap lnkTypeMap;
        amcLinkType lnkType = lnkTypeMap[w.second.get<std::string>("AMCLinkType")];

        amcLinkTypeExtensionMap lnkTypeExtensionMap;
        amcLinkTypeExtension lnkTypeExtension = lnkTypeExtensionMap[w.second.get<std::string>("AMCLinkTypeExtension")];

        asymmetricMatchMap asymMatchMap;
        asymmetricMatch asymMatch = asymMatchMap[w.second.get<std::string>("AsymmetricMatch")];

        int lnkGroupingId = w.second.get<int>("LinkGroupingID");
        lnkDescrs.push_back(amcLinkDescriptor(lnkDesignator, lnkType, lnkTypeExtension, lnkGroupingId, asymMatch));
      }
      
      chDescrs.push_back(amcChannelDescriptor(ports));
      amcChannelId++;
    }
  
    mra.addAMCPtPConnectivityRecord(chDescrs, lnkDescrs);
  }
  
  boost::optional<ptree&> zone3Records = pt.get_child_optional("MultiRecordArea.Zone3Records");
  if(zone3Records)
  {
    for(const ptree::value_type &v: pt.get_child("MultiRecordArea.Zone3Records"))
    {
      std::vector<std::string> interfaceBody;
      uint8_t interfaceIdentifier = v.second.get<uint8_t>("InterfaceIdentifier");
      switch(interfaceIdentifier)
      {
        case 1:
          interfaceBody.push_back(v.second.get<std::string>("IdentifierBody.PICMGSpecificationUniqueIdentifier"));
          interfaceBody.push_back(v.second.get<std::string>("IdentifierBody.PICMGSpecificationMajorRevisionNumber"));
          interfaceBody.push_back(v.second.get<std::string>("IdentifierBody.PICMGSpecificationMinorRevisionNumber"));
          interfaceBody.push_back(v.second.get<std::string>("IdentifierBody.OpaqueInterfaceIdentifierBody"));
          break;
        case 2:
          interfaceBody.push_back(v.second.get<std::string>("IdentifierBody.InterfaceIdentifierGUID"));
          break;
        case 3:
          interfaceBody.push_back(v.second.get<std::string>("IdentifierBody.ManufacturerIDIANA"));
          interfaceBody.push_back(v.second.get<std::string>("IdentifierBody.OEMDefinedInterfaceDesignator"));
          break;
        case 4:
          interfaceBody.push_back(v.second.get<std::string>("IdentifierBody.PICMGMTCARepNumber"));
          break;
        default:
          throw std::out_of_range("Interface Identifier out of valid range");
          break;
      }
      if(interfaceIdentifier>0)
      {
        interfaceIdentifierBody interface(interfaceIdentifier, interfaceBody);
        interfaceIdentifierBody *iib = &interface;
        if(interfaceBody.size() > 0)
        {
          mra.addZone3InterfaceCompatibilityRecord(interfaceIdentifier, iib);
        }
      }
    }
  }
  
  boost::optional<ptree&> clockRecords = pt.get_child_optional("MultiRecordArea.ClockConfigurationRecords");
  if(clockRecords)
  {
    for(const ptree::value_type &v: pt.get_child("MultiRecordArea.ClockConfigurationRecords"))
    {
      resourceIDResourceTypeMap rMap;
      resourceIDResourceType rID = rMap[v.second.get<std::string>("ClockResourceIDResourceType")];
      uint8_t dID = v.second.get<uint8_t>("ClockResourceIDDeviceIdentification");
      
      std::list<clockConfigurationDescriptor> clockDescrs;
      for(const ptree::value_type &w: v.second.get_child("ClockConfigurationDescriptors"))
      {
        clockIDMap clockMap;
        clockID ID = clockMap[w.second.get<std::string>("ClockID")];
        clockActivationControlMap controlMap;
        clockActivationControl control = controlMap[w.second.get<std::string>("ClockControl")];
        int inCount = w.second.count("IndirectClockDescriptors");
        int dCount = w.second.count("DirectClockDescriptors");
        clockConfigurationDescriptor desc(ID, control, inCount, dCount);
        
        if(inCount != 0)
        {
            std::list<indirectClockDescriptor> indirectDescrs;
            for(const ptree::value_type &x: w.second.get_child("IndirectClockDescriptors"))
            {
                indirectPllConnectionMap indirectConnMap;
                indirectPllConnection pll = indirectConnMap[x.second.get<std::string>("PLLConnection")];
                indirectClockAsymmetricMatchMap indirectAsymMap;
                indirectClockAsymmetricMatch match = indirectAsymMap[x.second.get<std::string>("ClockAsymmetricMatch")];
                uint8_t dClockID = x.second.get<uint8_t>("DependentClockID");
                indirectClockDescriptor ind(pll, match, dClockID);
                indirectDescrs.push_back(ind);
            }
            desc.addIndirectDescrs(indirectDescrs);
        }
        else if(dCount != 0)
        {
            std::list<directClockDescriptor> directDescrs;
            for(const ptree::value_type &x: w.second.get_child("DirectClockDescriptors"))
            {
                directPllConnectionMap directConnMap;
                directPllConnection pll = directConnMap[x.second.get<std::string>("PLLConnection")];
                directClockAsymmetricMatchMap directAsymMap;
                directClockAsymmetricMatch match = directAsymMap[x.second.get<std::string>("ClockAsymmetricMatch")];
                uint8_t fam = x.second.get<uint8_t>("ClockFamily");
                clockAccuracyLevelAcronymMap acronymMap;
                clockAccuracyLevelAcronym acc = acronymMap[x.second.get<std::string>("ClockAccuracyLevelAcronym")];
                uint32_t freq = x.second.get<uint32_t>("ClockFrequency");
                uint32_t min = x.second.get<uint32_t>("MinimumClockFrequency");
                uint32_t max = x.second.get<uint32_t>("MaximumClockFrequency");
                directClockDescriptor dir(pll, match, fam, acc, freq, min, max);
                directDescrs.push_back (dir);
            }
            desc.addDirectDescrs(directDescrs);
        }
        clockDescrs.push_back(desc);
      }
      mra.addClockConfigurationRecord(rID, dID, clockDescrs);
    }
  }
  
  if(debugMode)
  {
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
  }

  const std::vector<uint8_t> biaVec = bia.getBinaryData();
  const std::vector<uint8_t> chVec = ch.getBinaryData();
  const std::vector<uint8_t> piaVec = pia.getBinaryData();
  const std::vector<uint8_t> mraVec = mra.getBinaryData();

  const int dataLength = chVec.size() + biaVec.size() + piaVec.size() + mraVec.size();
  if(dataLength > EEPROM_SIZE)
    throw std::runtime_error(std::string("Data does not fit into EEPROM."));
  
  const std::vector<uint8_t> padVec(EEPROM_SIZE - dataLength);

  std::ofstream outfile;
  outfile.open(outFileName, std::ios::binary);
  outfile.write((char const *)chVec.data(), chVec.size());
  outfile.write((char const *)biaVec.data(), biaVec.size());
  outfile.write((char const *)piaVec.data(), piaVec.size());
  outfile.write((char const *)mraVec.data(), mraVec.size());
  outfile.write((char const *)padVec.data(), padVec.size());
  outfile.close();
  return 0;
}
