#include "clockConfigurationRecord.hpp"
#include "testUtils.hpp"
#include <boost/test/unit_test.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/assign/std/vector.hpp>
using namespace boost::assign; // bring 'operator+=()' into scope

BOOST_AUTO_TEST_SUITE( clockConfigurationRecordTests )     
        
BOOST_AUTO_TEST_CASE( constructorEmpty )
{
  resourceIDResourceTypeMap ridrtm;
  resourceIDResourceType type = ridrtm["Backplane"];
  clockIDMap cidm;
  clockID cid = cidm["TCLKA"];
  clockActivationControlMap cacm;
  clockActivationControl cac = cacm["ActivatedbyCarrierIPMC"];
  indirectPllConnectionMap indirectConnMap;
  indirectPllConnection ipll = indirectConnMap["ConnectedThroughPLL"];
  indirectClockAsymmetricMatchMap indirectAsymMap;
  indirectClockAsymmetricMatch imatch = indirectAsymMap["ClockSource"];
  indirectClockDescriptor icd(ipll, imatch, 0x0a);
  std::list<indirectClockDescriptor> indirect;
  indirect.push_back(icd);
  directPllConnectionMap directConnMap;
  directPllConnection dpll = directConnMap["ConnectedThroughPLL"];
  directClockAsymmetricMatchMap directAsymMap;
  directClockAsymmetricMatch dmatch = directAsymMap["ClockSource"];
  clockAccuracyLevelAcronymMap acronymMap;
  clockAccuracyLevelAcronym acc = acronymMap["ST4"];
  directClockDescriptor dcd(dpll, dmatch, 0x00, acc, 0x00000000, 0x00000000, 0x00000000);
  std::list<directClockDescriptor> direct;
  direct.push_back(dcd);
  clockConfigurationDescriptor ccd(cid, cac, indirect, direct);
  std::list<clockConfigurationDescriptor> desc;
  desc.push_back(ccd);
  clockConfigurationRecord(type, 1, desc);
}

BOOST_AUTO_TEST_CASE( constructorEmptyGetBinaryData )
{
  resourceIDResourceTypeMap ridrtm;
  resourceIDResourceType type = ridrtm["Backplane"];
  clockIDMap cidm;
  clockID cid = cidm["TCLKA"];
  clockActivationControlMap cacm;
  clockActivationControl cac = cacm["ActivatedbyCarrierIPMC"];
  indirectPllConnectionMap indirectConnMap;
  indirectPllConnection ipll = indirectConnMap["ConnectedThroughPLL"];
  indirectClockAsymmetricMatchMap indirectAsymMap;
  indirectClockAsymmetricMatch imatch = indirectAsymMap["ClockSource"];
  indirectClockDescriptor icd(ipll, imatch, 0x0a);
  std::list<indirectClockDescriptor> indirect;
  indirect.push_back(icd);
  directPllConnectionMap directConnMap;
  directPllConnection dpll = directConnMap["ConnectedThroughPLL"];
  directClockAsymmetricMatchMap directAsymMap;
  directClockAsymmetricMatch dmatch = directAsymMap["ClockSource"];
  clockAccuracyLevelAcronymMap acronymMap;
  clockAccuracyLevelAcronym acc = acronymMap["ST4"];
  directClockDescriptor dcd(dpll, dmatch, 0x01, acc, 0x00178F40, 0x00001F40, 0x0128A180);
  std::list<directClockDescriptor> direct;
  direct.push_back(dcd);
  clockConfigurationDescriptor ccd(cid, cac, indirect, direct);
  std::list<clockConfigurationDescriptor> desc;
  desc.push_back(ccd);
  clockConfigurationRecord ccr(type, 1, desc);
  std::vector<uint8_t> manResult = boost::assign::list_of(0xC0)(0x02)(0x1c)(0xd3)(0x4f)(0x5a)(0x31)(0x00)(0x2d)(0x00)(0x81)(0x01)(0x01)(0x00)(0x01)(0x01)(0x03)(0x0a)(0x03)(0x01)(0x50)(0x40)(0x8F)(0x17)(0x00)(0x40)(0x1F)(0x00)(0x00)(0x80)(0xA1)(0x28)(0x01);
  std::vector<uint8_t> autoResult = ccr.getBinaryData();
  BOOST_CHECK_EQUAL_COLLECTIONS( autoResult.cbegin(), autoResult.cend(), manResult.cbegin(), manResult.cend() );
  if( autoResult != manResult )
  {
    std::cout << "should be: ";
    std::copy(manResult.cbegin(), manResult.cend(), std::ostream_iterator<int>(std::cout << std::hex, " "));
    std::cout << std::endl;
    std::cout << "is:        ";
    std::copy(autoResult.cbegin(), autoResult.cend(), std::ostream_iterator<int>(std::cout << std::hex, " "));
    std::cout << std::endl;
  }
}

BOOST_AUTO_TEST_CASE( binarySize )
{
  resourceIDResourceTypeMap ridrtm;
  resourceIDResourceType type = ridrtm["Backplane"];
  clockIDMap cidm;
  clockID cid = cidm["TCLKA"];
  clockActivationControlMap cacm;
  clockActivationControl cac = cacm["ActivatedbyCarrierIPMC"];
  indirectPllConnectionMap indirectConnMap;
  indirectPllConnection ipll = indirectConnMap["ConnectedThroughPLL"];
  indirectClockAsymmetricMatchMap indirectAsymMap;
  indirectClockAsymmetricMatch imatch = indirectAsymMap["ClockSource"];
  indirectClockDescriptor icd(ipll, imatch, 0x0a);
  std::list<indirectClockDescriptor> indirect;
  indirect.push_back(icd);
  directPllConnectionMap directConnMap;
  directPllConnection dpll = directConnMap["ConnectedThroughPLL"];
  directClockAsymmetricMatchMap directAsymMap;
  directClockAsymmetricMatch dmatch = directAsymMap["ClockSource"];
  clockAccuracyLevelAcronymMap acronymMap;
  clockAccuracyLevelAcronym acc = acronymMap["ST4"];
  directClockDescriptor dcd(dpll, dmatch, 0x01, acc, 0x00178F40, 0x00001F40, 0x0128A180);
  std::list<directClockDescriptor> direct;
  direct.push_back(dcd);
  clockConfigurationDescriptor ccd(cid, cac, indirect, direct);
  std::list<clockConfigurationDescriptor> desc;
  desc.push_back(ccd);
  clockConfigurationRecord ccr(type, 1, desc);
  BOOST_CHECK_EQUAL( ccr.getBinaryData().size(), 33 );
}

BOOST_AUTO_TEST_CASE( size )
{
  resourceIDResourceTypeMap ridrtm;
  resourceIDResourceType type = ridrtm["Backplane"];
  clockIDMap cidm;
  clockID cid = cidm["TCLKA"];
  clockActivationControlMap cacm;
  clockActivationControl cac = cacm["ActivatedbyCarrierIPMC"];
  indirectPllConnectionMap indirectConnMap;
  indirectPllConnection ipll = indirectConnMap["ConnectedThroughPLL"];
  indirectClockAsymmetricMatchMap indirectAsymMap;
  indirectClockAsymmetricMatch imatch = indirectAsymMap["ClockSource"];
  indirectClockDescriptor icd(ipll, imatch, 0x0a);
  std::list<indirectClockDescriptor> indirect;
  indirect.push_back(icd);
  directPllConnectionMap directConnMap;
  directPllConnection dpll = directConnMap["ConnectedThroughPLL"];
  directClockAsymmetricMatchMap directAsymMap;
  directClockAsymmetricMatch dmatch = directAsymMap["ClockSource"];
  clockAccuracyLevelAcronymMap acronymMap;
  clockAccuracyLevelAcronym acc = acronymMap["ST4"];
  directClockDescriptor dcd(dpll, dmatch, 0x01, acc, 0x00178F40, 0x00001F40, 0x0128A180);
  std::list<directClockDescriptor> direct;
  direct.push_back(dcd);
  clockConfigurationDescriptor ccd(cid, cac, indirect, direct);
  std::list<clockConfigurationDescriptor> desc;
  desc.push_back(ccd);
  clockConfigurationRecord ccr(type, 1, desc);
  BOOST_CHECK_EQUAL( ccr.size(), 33 );
}
        
BOOST_AUTO_TEST_SUITE_END()