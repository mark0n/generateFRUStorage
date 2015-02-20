#include "zone3InterfaceCompatibilityRecord.hpp"
#include "testUtils.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( zone3InterfaceCompatibilityTests )
        
BOOST_AUTO_TEST_CASE( constructorEmpty )
{
  zone3InterfaceCompatibilityRecord zone(uint8_t interface, interfaceIdentifierBody* body);
}

BOOST_AUTO_TEST_CASE( constructorGetBinaryData )
{
  uint8_t interface = 4;
  std::string ident = "00000000";
  std::vector<std::string> interfaceBody;
  interfaceBody.push_back(ident);
  interfaceIdentifierBody bodyObject(interface, interfaceBody); 
  interfaceIdentifierBody* body = &bodyObject;
  zone3InterfaceCompatibilityRecord zone(interface, body);
  std::vector<uint8_t> manResult = { 0xc0, 0x02, 0x0a, 0x40, 0xf4, 0x5a, 0x31, 0x00, 0x30, 0x01, 0x04, 0x00, 0x00, 0x00, 0x00 };
  std::vector<uint8_t> autoResult = zone.getBinaryData();
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
  uint8_t interface = 1;
  std::string ident = "12345678";
  std::string major = "01";
  std::string minor = "05";
  std::string opaque = "1234567890";
  std::vector<std::string> interfaceBody;
  interfaceBody.push_back(ident);
  interfaceBody.push_back(major);
  interfaceBody.push_back(minor);
  interfaceBody.push_back(opaque);
  interfaceIdentifierBody bodyObject(interface, interfaceBody); 
  interfaceIdentifierBody* body = &bodyObject;
  zone3InterfaceCompatibilityRecord zone(interface, body);
  BOOST_CHECK_EQUAL(zone.getBinaryData().size(), 22);
}

BOOST_AUTO_TEST_CASE( size )
{
  uint8_t interface = 1;
  std::string ident = "12345678";
  std::string major = "01";
  std::string minor = "05";
  std::string opaque = "1234567890";
  std::vector<std::string> interfaceBody;
  interfaceBody.push_back(ident);
  interfaceBody.push_back(major);
  interfaceBody.push_back(minor);
  interfaceBody.push_back(opaque);
  interfaceIdentifierBody bodyObject(interface, interfaceBody); 
  interfaceIdentifierBody* body = &bodyObject;
  zone3InterfaceCompatibilityRecord zone(interface, body);
  BOOST_CHECK_EQUAL(zone.size(), 22);
}



BOOST_AUTO_TEST_SUITE_END()