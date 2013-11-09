#include "commonHeader.hpp"

BOOST_AUTO_TEST_SUITE( commonHeaderTests )

BOOST_AUTO_TEST_CASE( commonHeaderConstructor )
{
  commonHeader ch;
}

BOOST_AUTO_TEST_CASE( commonHeaderDefaultConstructorGetMethods )
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

BOOST_AUTO_TEST_CASE( commonHeaderDefaultConstructorGetBinaryData )
{
  commonHeader ch;
  std::vector<uint8_t> manResult = { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff };
  std::vector<uint8_t> autoResult = ch.getBinaryData();
  BOOST_CHECK( autoResult == manResult );
}

BOOST_AUTO_TEST_CASE( commonHeaderSetInternalUseAreaOffset )
{
  commonHeader ch;
  ch.setInternalUseAreaOffset( 0xd3 );
  BOOST_CHECK( ch.getInternalUseAreaOffset() == 0xd3 );
  std::vector<uint8_t> manResult = { 0x01, 0xd3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2c };
  std::vector<uint8_t> autoResult = ch.getBinaryData();
  BOOST_CHECK( autoResult == manResult );
}

BOOST_AUTO_TEST_CASE( commonHeaderSetChassisInfoAreaOffset )
{
  commonHeader ch;
  ch.setChassisInfoAreaOffset( 0xd3 );
  BOOST_CHECK( ch.getChassisInfoAreaOffset() == 0xd3 );
  std::vector<uint8_t> manResult = { 0x01, 0x00, 0xd3, 0x00, 0x00, 0x00, 0x00, 0x2c };
  std::vector<uint8_t> autoResult = ch.getBinaryData();
  BOOST_CHECK( autoResult == manResult );
}

BOOST_AUTO_TEST_CASE( commonHeaderSetBoardAreaOffset )
{
  commonHeader ch;
  ch.setBoardAreaOffset( 0xd3 );
  BOOST_CHECK( ch.getBoardAreaOffset() == 0xd3 );
  std::vector<uint8_t> manResult = { 0x01, 0x00, 0x00, 0xd3, 0x00, 0x00, 0x00, 0x2c };
  std::vector<uint8_t> autoResult = ch.getBinaryData();
  BOOST_CHECK( autoResult == manResult );
}

BOOST_AUTO_TEST_CASE( commonHeaderSetProductInfoAreaOffset )
{
  commonHeader ch;
  ch.setProductInfoAreaOffset( 0xd3 );
  BOOST_CHECK( ch.getProductInfoAreaOffset() == 0xd3 );
  std::vector<uint8_t> manResult = { 0x01, 0x00, 0x00, 0x00, 0xd3, 0x00, 0x00, 0x2c };
  std::vector<uint8_t> autoResult = ch.getBinaryData();
  BOOST_CHECK( autoResult == manResult );
}

BOOST_AUTO_TEST_CASE( commonHeaderSetMultiRecordAreaOffset )
{
  commonHeader ch;
  ch.setMultiRecordAreaOffset( 0xd3 );
  BOOST_CHECK( ch.getMultiRecordAreaOffset() == 0xd3 );
  std::vector<uint8_t> manResult = { 0x01, 0x00, 0x00, 0x00, 0x00, 0xd3, 0x00, 0x2c };
  std::vector<uint8_t> autoResult = ch.getBinaryData();
  BOOST_CHECK( autoResult == manResult );
}

BOOST_AUTO_TEST_SUITE_END()