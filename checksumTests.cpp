#include "checksum.hpp"
#include <boost/test/unit_test.hpp>
#include <boost/assign/list_of.hpp>

BOOST_AUTO_TEST_SUITE( checksumTests )

BOOST_AUTO_TEST_CASE( empty )
{
  std::vector<uint8_t> data;
  BOOST_CHECK_EQUAL( calcChecksum(data.cbegin(), data.cend()), 0 );
}

BOOST_AUTO_TEST_CASE( length1 )
{
  std::vector<uint8_t> data = boost::assign::list_of(0x05);
  BOOST_CHECK_EQUAL( calcChecksum(data.cbegin(), data.cend()), 0x05 );
}

BOOST_AUTO_TEST_CASE( simple )
{
  std::vector<uint8_t> data = boost::assign::list_of(0x01)(0x02)(0x03);
  BOOST_CHECK_EQUAL( calcChecksum(data.cbegin(), data.cend()), 0x06 );
}

BOOST_AUTO_TEST_CASE( overflow )
{
  std::vector<uint8_t> data = boost::assign::list_of(0xcc)(0x3a)(0x28);
  BOOST_CHECK_EQUAL( calcChecksum(data.cbegin(), data.cend()), 0x2e );
}

BOOST_AUTO_TEST_CASE( huge )
{
  std::vector<uint8_t> data(1013, 0x4d);
  BOOST_CHECK_EQUAL( calcChecksum(data.cbegin(), data.cend()), 0xb1 );
}

BOOST_AUTO_TEST_SUITE_END()