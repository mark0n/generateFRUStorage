#include "multiRecordArea.hpp"
#include "testUtils.hpp"
#include <boost/test/unit_test.hpp>
#include <boost/assign/list_of.hpp>
#include <iostream>

BOOST_AUTO_TEST_SUITE( multiRecordAreaTests )

BOOST_AUTO_TEST_CASE( constructor )
{
  multiRecordArea mra;
}

BOOST_AUTO_TEST_CASE( defaultConstructorGetBinaryData )
{
  multiRecordArea mra;
  std::vector<uint8_t> manResult;
  std::vector<uint8_t> autoResult = mra.getBinaryData();
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

BOOST_AUTO_TEST_CASE( addOneRecord )
{
  multiRecordArea mra;
  std::vector<uint8_t> payload = boost::assign::list_of(0x01)(0x02)(0x03);
  mra.addRecord(0x23, payload);
  std::vector<uint8_t> manResult = boost::assign::list_of(0x23)(0x82)(0x03)(0xfa)(0x5e)(0x01)(0x02)(0x03);
  std::vector<uint8_t> autoResult = mra.getBinaryData();
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

BOOST_AUTO_TEST_CASE( addThreeRecords )
{
  multiRecordArea mra;
  std::vector<uint8_t> payload1 = boost::assign::list_of(0x01)(0x02)(0x03);
  mra.addRecord(0x23, payload1);
  std::vector<uint8_t> payload2 = boost::assign::list_of(0x04)(0x05);
  mra.addRecord(0xe3, payload2);
  std::vector<uint8_t> payload3 = boost::assign::list_of(0x06)(0x07)(0x08);
  mra.addRecord(0x78, payload3);
  std::vector<uint8_t> manResult = boost::assign::list_of(0x23)(0x02)(0x03)(0xfa)(0xde)(0x01)(0x02)(0x03)
                                     (0xe3)(0x02)(0x02)(0xf7)(0x22)(0x04)(0x05)
                                     (0x78)(0x82)(0x03)(0xeb)(0x18)(0x06)(0x07)(0x08);
  std::vector<uint8_t> autoResult = mra.getBinaryData();
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

BOOST_AUTO_TEST_CASE( addAMCPtPConnectivityRecord )
{
  multiRecordArea mra;
  std::list<amcChannelDescriptor> acl;
  const std::vector<int> ports = boost::assign::list_of(1)(2)(3)(4);
  acl.push_back( amcChannelDescriptor(ports) );
  std::list<amcLinkDescriptor> ald;
  mra.addAMCPtPConnectivityRecord( acl, ald );
  std::vector<uint8_t> manResult = boost::assign::list_of(0xc0)(0x82)(0x0b)(0x9c)(0x17)(0x5a)(0x31)(0x00)(0x19)(0x00)(0x00)(0x80)(0x01)(0x41)(0x0c)(0xf2);
  std::vector<uint8_t> autoResult = mra.getBinaryData();
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

BOOST_AUTO_TEST_CASE( addModuleCurrentRequirementsRecord )
{
  multiRecordArea mra;
  mra.addModuleCurrentRequirementsRecord( 1.0 );
  std::vector<uint8_t> manResult = boost::assign::list_of(0xc0)(0x82)(0x06)(0x55)(0x63)(0x5a)(0x31)(0x00)(0x16)(0x00)(0x0a);
  std::vector<uint8_t> autoResult = mra.getBinaryData();
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

BOOST_AUTO_TEST_CASE( binarySizeEmpty )
{
  multiRecordArea mra;
  BOOST_CHECK_EQUAL( mra.getBinaryData().size(), 0 );
}

BOOST_AUTO_TEST_CASE( sizeEmpty )
{
  multiRecordArea mra;
  BOOST_CHECK_EQUAL( mra.size(), 0 );
}

BOOST_AUTO_TEST_CASE( binarySizeAMCPtPConnectivityRecord )
{
  multiRecordArea mra;
  std::list<amcChannelDescriptor> acl;
  const std::vector<int> ports = boost::assign::list_of(1)(2)(3)(4);
  acl.push_back( amcChannelDescriptor(ports) );
  std::list<amcLinkDescriptor> ald;
  mra.addAMCPtPConnectivityRecord( acl, ald );
  BOOST_CHECK_EQUAL( mra.getBinaryData().size(), 16 );
}

BOOST_AUTO_TEST_CASE( sizeAMCPtPConnectivityRecord )
{
  multiRecordArea mra;
  std::list<amcChannelDescriptor> acl;
  const std::vector<int> ports = boost::assign::list_of(1)(2)(3)(4);
  acl.push_back( amcChannelDescriptor(ports) );
  std::list<amcLinkDescriptor> ald;
  mra.addAMCPtPConnectivityRecord( acl, ald );
  BOOST_CHECK_EQUAL( mra.size(), 16 );
}

BOOST_AUTO_TEST_CASE( binarySizeMultipleRecords )
{
  multiRecordArea mra;
  std::vector<uint8_t> payload1 = boost::assign::list_of(0x01)(0x02)(0x03);
  mra.addRecord(0x23, payload1);
  std::list<amcChannelDescriptor> acl;
  const std::vector<int> ports = boost::assign::list_of(1)(2)(3)(4);
  acl.push_back( amcChannelDescriptor(ports) );
  std::list<amcLinkDescriptor> ald;
  mra.addAMCPtPConnectivityRecord( acl, ald );
  mra.addModuleCurrentRequirementsRecord( 1.0 );
  BOOST_CHECK_EQUAL( mra.getBinaryData().size(), 35 );
}

BOOST_AUTO_TEST_CASE( sizeMultipleRecords )
{
  multiRecordArea mra;
  std::vector<uint8_t> payload1 = boost::assign::list_of(0x01)(0x02)(0x03);
  mra.addRecord(0x23, payload1);
  std::list<amcChannelDescriptor> acl;
  const std::vector<int> ports = boost::assign::list_of(1)(2)(3)(4);
  acl.push_back( amcChannelDescriptor(ports) );
  std::list<amcLinkDescriptor> ald;
  mra.addAMCPtPConnectivityRecord( acl, ald );
  mra.addModuleCurrentRequirementsRecord( 1.0 );
  BOOST_CHECK_EQUAL( mra.size(), 35 );
}

BOOST_AUTO_TEST_SUITE_END()