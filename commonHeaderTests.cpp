#include "commonHeader.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( commonHeaderTests )

BOOST_AUTO_TEST_CASE( constructor )
{
  commonHeader ch;
}

BOOST_AUTO_TEST_CASE( defaultConstructorGetMethods )
{
  commonHeader ch;
  BOOST_CHECK_EQUAL( ch.getFormatVersion(), 1 );
  BOOST_CHECK_EQUAL( ch.getInternalUseAreaOffset(), 0x00 );
  BOOST_CHECK_EQUAL( ch.getChassisInfoAreaOffset(), 0x00 );
  BOOST_CHECK_EQUAL( ch.getBoardAreaOffset(), 0x00 );
  BOOST_CHECK_EQUAL( ch.getProductInfoAreaOffset(), 0x00 );
  BOOST_CHECK_EQUAL( ch.getMultiRecordAreaOffset(), 0x00 );
  BOOST_CHECK_EQUAL( ch.getChecksum(), 0xff );
  BOOST_CHECK_EQUAL( ch.size(), 8 );
}

BOOST_AUTO_TEST_CASE( defaultConstructorGetBinaryData )
{
  commonHeader ch;
  std::vector<uint8_t> manResult = { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff };
  std::vector<uint8_t> autoResult = ch.getBinaryData();
  BOOST_CHECK( autoResult == manResult );
}

BOOST_AUTO_TEST_CASE( setInternalUseAreaOffset )
{
  commonHeader ch;
  ch.setInternalUseAreaOffset( 0xd3 );
  BOOST_CHECK( ch.getInternalUseAreaOffset() == 0xd3 );
  std::vector<uint8_t> manResult = { 0x01, 0xd3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2c };
  std::vector<uint8_t> autoResult = ch.getBinaryData();
  BOOST_CHECK( autoResult == manResult );
}

BOOST_AUTO_TEST_CASE( setChassisInfoAreaOffset )
{
  commonHeader ch;
  ch.setChassisInfoAreaOffset( 0xd3 );
  BOOST_CHECK( ch.getChassisInfoAreaOffset() == 0xd3 );
  std::vector<uint8_t> manResult = { 0x01, 0x00, 0xd3, 0x00, 0x00, 0x00, 0x00, 0x2c };
  std::vector<uint8_t> autoResult = ch.getBinaryData();
  BOOST_CHECK( autoResult == manResult );
}

BOOST_AUTO_TEST_CASE( setBoardAreaOffset )
{
  commonHeader ch;
  ch.setBoardAreaOffset( 0xd3 );
  BOOST_CHECK( ch.getBoardAreaOffset() == 0xd3 );
  std::vector<uint8_t> manResult = { 0x01, 0x00, 0x00, 0xd3, 0x00, 0x00, 0x00, 0x2c };
  std::vector<uint8_t> autoResult = ch.getBinaryData();
  BOOST_CHECK( autoResult == manResult );
}

BOOST_AUTO_TEST_CASE( setProductInfoAreaOffset )
{
  commonHeader ch;
  ch.setProductInfoAreaOffset( 0xd3 );
  BOOST_CHECK( ch.getProductInfoAreaOffset() == 0xd3 );
  std::vector<uint8_t> manResult = { 0x01, 0x00, 0x00, 0x00, 0xd3, 0x00, 0x00, 0x2c };
  std::vector<uint8_t> autoResult = ch.getBinaryData();
  BOOST_CHECK( autoResult == manResult );
}

BOOST_AUTO_TEST_CASE( setMultiRecordAreaOffset )
{
  commonHeader ch;
  ch.setMultiRecordAreaOffset( 0xd3 );
  BOOST_CHECK( ch.getMultiRecordAreaOffset() == 0xd3 );
  std::vector<uint8_t> manResult = { 0x01, 0x00, 0x00, 0x00, 0x00, 0xd3, 0x00, 0x2c };
  std::vector<uint8_t> autoResult = ch.getBinaryData();
  BOOST_CHECK( autoResult == manResult );
}

BOOST_AUTO_TEST_SUITE_END()