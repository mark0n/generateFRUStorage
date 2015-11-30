#include "amcChannelDescriptor.hpp"
#include "testUtils.hpp"
#include <boost/test/unit_test.hpp>
#include <boost/assign/list_of.hpp>
#include <iostream>

BOOST_AUTO_TEST_SUITE( amcChannelDescriptorTests )

BOOST_AUTO_TEST_CASE( notEnoughPortNumbers )
{
  const std::vector<int> ports = boost::assign::list_of(0x01)(0x02)(0x03);
  BOOST_CHECK_THROW( amcChannelDescriptor acd( ports ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( tooManyPortNumbers )
{
  const std::vector<int> ports = boost::assign::list_of(0x01)(0x02)(0x03)(0x04)(0x05);
  BOOST_CHECK_THROW( amcChannelDescriptor acd( ports ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE( portNumberNegative )
{
  const std::vector<int> ports = boost::assign::list_of(0x01)(-10)(0x03)(0x04);
  BOOST_CHECK_THROW( amcChannelDescriptor acd( ports ), std::out_of_range );
}

BOOST_AUTO_TEST_CASE( portNumberTooLarge )
{
  const std::vector<int> ports = boost::assign::list_of(0x01)(32)(0x03)(0x04);
  BOOST_CHECK_THROW( amcChannelDescriptor acd( ports ), std::out_of_range );
}

BOOST_AUTO_TEST_CASE( constructorGetBinaryData )
{
  const std::vector<int> ports = boost::assign::list_of(0x01)(0x02)(0x03)(0x04);
  amcChannelDescriptor acd( ports );
  std::vector<uint8_t> manResult = boost::assign::list_of(0x41)(0x0c)(0xf2);
  std::vector<uint8_t> autoResult = acd.getBinaryData();
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
  const std::vector<int> ports = boost::assign::list_of(0x01)(0x02)(0x03)(0x04);
  amcChannelDescriptor acd( ports );
  BOOST_CHECK_EQUAL( acd.getBinaryData().size(), 3 );
}

BOOST_AUTO_TEST_CASE( size )
{
  const std::vector<int> ports = boost::assign::list_of(0x01)(0x02)(0x03)(0x04);
  amcChannelDescriptor acd( ports );
  BOOST_CHECK_EQUAL( acd.size(), 3 );
}

BOOST_AUTO_TEST_SUITE_END()