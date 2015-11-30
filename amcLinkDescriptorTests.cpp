#include "amcLinkDescriptor.hpp"
#include "testUtils.hpp"
#include <boost/test/unit_test.hpp>
#include <boost/assign/list_of.hpp>
#include <iostream>

BOOST_AUTO_TEST_SUITE( amcLinkDescriptorTests )

BOOST_AUTO_TEST_CASE( constructorEmpty )
{
  struct amcLinkDesignator lnkDesignator = { 0x5a, std::bitset<4>( "1010" ) };
  amcLinkDescriptor ald(lnkDesignator, AMC1PCIe, 2, 0xac, 1);
}

BOOST_AUTO_TEST_CASE( constructorEmptyGetBinaryData )
{
  struct amcLinkDesignator lnkDesignator = { 0x5a, std::bitset<4>( "1010" ) };
  amcLinkDescriptor ald(lnkDesignator, AMC1PCIe, 2, 0xac, 1);
  std::vector<uint8_t> manResult = boost::assign::list_of(0x5a)(0x2a)(0x20)(0xac)(0xfd);
  std::vector<uint8_t> autoResult = ald.getBinaryData();
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
  struct amcLinkDesignator lnkDesignator = { 0x5a, std::bitset<4>( "1010" ) };
  amcLinkDescriptor ald(lnkDesignator, AMC1PCIe, 2, 0xac, 1);
  BOOST_CHECK_EQUAL( ald.getBinaryData().size(), 5 );
}

BOOST_AUTO_TEST_CASE( size )
{
  struct amcLinkDesignator lnkDesignator = { 0x5a, std::bitset<4>( "1010" ) };
  amcLinkDescriptor ald(lnkDesignator, AMC1PCIe, 2, 0xac, 1);
  BOOST_CHECK_EQUAL( ald.size(), 5 );
}

BOOST_AUTO_TEST_SUITE_END()