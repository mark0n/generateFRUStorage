#include "amcPtPConnectivityRecord.hpp"
#include "testUtils.hpp"
#include <boost/test/unit_test.hpp>
#include <boost/assign/list_of.hpp>

BOOST_AUTO_TEST_SUITE( amcPtPConnectivityRecordTests )

BOOST_AUTO_TEST_CASE( constructorEmpty )
{
  amcPtPConnectivityRecord apcr( std::list<amcChannelDescriptor>(), std::list<amcLinkDescriptor>() );
}

BOOST_AUTO_TEST_CASE( constructorEmptyGetBinaryData )
{
  std::list<amcChannelDescriptor> acl;
  std::list<amcLinkDescriptor> ald;
  amcPtPConnectivityRecord apcr( acl, ald );
  std::vector<uint8_t> manResult = boost::assign::list_of(0xc0)(0x02)(0x08)(0xdc)(0x5a)(0x5a)(0x31)(0x00)(0x19)(0x00)(0x00)(0x80)(0x00);
  std::vector<uint8_t> autoResult = apcr.getBinaryData();
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

BOOST_AUTO_TEST_CASE( tooManyChannelDescriptors )
{
  std::list<amcChannelDescriptor> acl;
  std::list<amcLinkDescriptor> ald;
  const std::vector<int> ports = boost::assign::list_of(1)(2)(3)(4);
  for( int i = 0; i < 256; i++ )
  {
    acl.push_back( amcChannelDescriptor(ports) );
  }
  BOOST_CHECK_THROW( amcPtPConnectivityRecord apcr( acl, ald ), std::length_error );
}  

BOOST_AUTO_TEST_CASE( tooManyLinkDescriptors )
{
  std::list<amcChannelDescriptor> acl;
  std::list<amcLinkDescriptor> ald;
  struct amcLinkDesignator lnkDesignator = {0x5a, std::bitset<4>( "1010" ) };
  for( int i = 0; i < 256; i++ )
  {
    ald.push_back(amcLinkDescriptor(lnkDesignator, AMC1PCIe, 2, 0xac, 1));
  }
  BOOST_CHECK_THROW( amcPtPConnectivityRecord apcr( acl, ald ), std::length_error );
}  

BOOST_AUTO_TEST_CASE( tooMuchPayload )
{
  std::list<amcChannelDescriptor> acl;
  std::list<amcLinkDescriptor> ald;
  const std::vector<int> ports = boost::assign::list_of(1)(2)(3)(4);
  for( int i = 0; i < 83; i++ )
  {
    acl.push_back( amcChannelDescriptor(ports) );
  }
  BOOST_CHECK_THROW( amcPtPConnectivityRecord apcr( acl, ald ), std::length_error );
}  

BOOST_AUTO_TEST_CASE( oneChannelDescriptorGetBinaryData )
{
  std::list<amcChannelDescriptor> acl;
  const std::vector<int> ports = boost::assign::list_of(1)(2)(3)(4);
  acl.push_back( amcChannelDescriptor(ports) );
  std::list<amcLinkDescriptor> ald;
  amcPtPConnectivityRecord apcr( acl, ald );
  std::vector<uint8_t> manResult = boost::assign::list_of(0xc0)(0x02)(0x0b)(0x9c)(0x97)(0x5a)(0x31)(0x00)(0x19)(0x00)(0x00)(0x80)(0x01)(0x41)(0x0c)(0xf2);
  std::vector<uint8_t> autoResult = apcr.getBinaryData();
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

BOOST_AUTO_TEST_CASE( oneLinkDesignatorGetBinaryData )
{
  std::list<amcChannelDescriptor> acl;
  std::list<amcLinkDescriptor> ald;
  struct amcLinkDesignator lnkDesignator = {0x5a, std::bitset<4>( "1010" ) };
  ald.push_back(amcLinkDescriptor(lnkDesignator, AMC1PCIe, 2, 0xac, 1));
  amcPtPConnectivityRecord apcr( acl, ald );
  std::vector<uint8_t> manResult = boost::assign::list_of(0xc0)(0x02)(0x0d)(0x8f)(0xa2)(0x5a)(0x31)(0x00)(0x19)(0x00)(0x00)(0x80)(0x00)(0x5a)(0x2a)(0x20)(0xac)(0xfd);
  std::vector<uint8_t> autoResult = apcr.getBinaryData();
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

BOOST_AUTO_TEST_CASE( multipleEntriesGetBinaryData )
{
  std::list<amcChannelDescriptor> acl;
  const std::vector<int> ports1 = boost::assign::list_of(1)(2)(3)(4);
  acl.push_back( amcChannelDescriptor(ports1) );
  const std::vector<int> ports2 = boost::assign::list_of(5)(6)(7)(8);
  acl.push_back( amcChannelDescriptor(ports2) );
  const std::vector<int> ports3 = boost::assign::list_of(9)(10)(11)(12);
  acl.push_back( amcChannelDescriptor(ports3) );
  std::list<amcLinkDescriptor> ald;
  struct amcLinkDesignator lnkDesignator1 = { 0x5a, std::bitset<4>( "1010" ) };
  ald.push_back(amcLinkDescriptor(lnkDesignator1, AMC1PCIe, 2, 0xac, 1));
  struct amcLinkDesignator lnkDesignator2 = { 0x5b, std::bitset<4>( "0011" ) };
  ald.push_back(amcLinkDescriptor(lnkDesignator2, AMC2Ethernet, 3, 0xdd, 2));
  amcPtPConnectivityRecord apcr( acl, ald );
  std::vector<uint8_t> manResult = boost::assign::list_of(0xc0)(0x02)(0x1b)(0x53)(0xd0)(0x5a)(0x31)(0x00)(0x19)(0x00)(0x00)(0x80)(0x03)(0x41)(0x0c)(0xf2)(0xc5)(0x1c)(0xf4)(0x49)(0x2d)(0xf6)(0x5a)(0x2a)(0x20)(0xac)(0xfd)(0x5b)(0x53)(0x30)(0xdd)(0xfe);
  std::vector<uint8_t> autoResult = apcr.getBinaryData();
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
  std::list<amcChannelDescriptor> acl;
  const std::vector<int> ports1 = boost::assign::list_of(1)(2)(3)(4);
  acl.push_back( amcChannelDescriptor(ports1) );
  const std::vector<int> ports2 = boost::assign::list_of(5)(6)(7)(8);
  acl.push_back( amcChannelDescriptor(ports2) );
  const std::vector<int> ports3 = boost::assign::list_of(9)(10)(11)(12);
  acl.push_back( amcChannelDescriptor(ports3) );
  std::list<amcLinkDescriptor> ald;
  struct amcLinkDesignator lnkDesignator1 = { 0x5a, std::bitset<4>( "1010" ) };
  ald.push_back(amcLinkDescriptor(lnkDesignator1, AMC1PCIe, 2, 0xac, 1));
  struct amcLinkDesignator lnkDesignator2 = { 0x5b, std::bitset<4>( "0011" ) };
  ald.push_back(amcLinkDescriptor(lnkDesignator2, AMC2Ethernet, 3, 0xdd, 2));
  amcPtPConnectivityRecord apcr( acl, ald );
  BOOST_CHECK_EQUAL( apcr.getBinaryData().size(), 32 );
}

BOOST_AUTO_TEST_CASE( size )
{
  std::list<amcChannelDescriptor> acl;
  const std::vector<int> ports1 = boost::assign::list_of(1)(2)(3)(4);
  acl.push_back( amcChannelDescriptor(ports1) );
  const std::vector<int> ports2 = boost::assign::list_of(5)(6)(7)(8);
  acl.push_back( amcChannelDescriptor(ports2) );
  const std::vector<int> ports3 = boost::assign::list_of(9)(10)(11)(12);
  acl.push_back( amcChannelDescriptor(ports3) );
  std::list<amcLinkDescriptor> ald;
  struct amcLinkDesignator lnkDesignator1 = { 0x5a, std::bitset<4>( "1010" ) };
  ald.push_back(amcLinkDescriptor(lnkDesignator1, AMC1PCIe, 2, 0xac, 1));
  struct amcLinkDesignator lnkDesignator2 = { 0x5b, std::bitset<4>( "0011" ) };
  ald.push_back(amcLinkDescriptor(lnkDesignator2, AMC2Ethernet, 3, 0xdd, 2));
  amcPtPConnectivityRecord apcr( acl, ald );
  BOOST_CHECK_EQUAL( apcr.size(), 32 );
}

BOOST_AUTO_TEST_SUITE_END()