#include "boardInfoArea.hpp"
#include "testUtils.hpp"
#include <boost/test/unit_test.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

BOOST_AUTO_TEST_SUITE( boardInfoAreaTests )

BOOST_AUTO_TEST_CASE( boardInfoAreaConstructor )
{
  boardInfoArea bia;
}

BOOST_AUTO_TEST_CASE( boardInfoAreaDefaultConstructorGetMethods )
{
  boardInfoArea bia;
  BOOST_CHECK_EQUAL( bia.getFormatVersion(), 1 );
  BOOST_CHECK_EQUAL( bia.getBoardAreaLength(), 2 );
  BOOST_CHECK_EQUAL( bia.getLanguageCode(), 0 );
  BOOST_CHECK_EQUAL( bia.getMfgDateTime(), boost::posix_time::ptime(boost::posix_time::time_from_string("1996-01-01 00:00:00.000")) );
  BOOST_CHECK_EQUAL( bia.getManufacturer(), "" );
  BOOST_CHECK_EQUAL( bia.getProductName(), "" );
  BOOST_CHECK_EQUAL( bia.getSerialNumber(), "" );
  BOOST_CHECK_EQUAL( bia.getPartNumber(), "" );
  BOOST_CHECK_EQUAL( bia.getFRUFileId(), "" );
  BOOST_CHECK_EQUAL( bia.getChecksum(), 0x7c );
  BOOST_CHECK_EQUAL( bia.size(), 16 );
}

BOOST_AUTO_TEST_CASE( boardInfoAreaDefaultConstructorGetBinaryData )
{
  boardInfoArea bia;
  std::vector<uint8_t> manResult =   { 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc1, 0x00, 0x00, 0x00, 0x7c };
  std::vector<uint8_t> compareMask = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff };
  std::vector<uint8_t> autoResult = bia.getBinaryData();
  std::vector<uint8_t> autoResultMasked = applyMask(autoResult, compareMask);
  BOOST_CHECK_EQUAL_COLLECTIONS( autoResultMasked.cbegin(), autoResultMasked.cend(), manResult.cbegin(), manResult.cend() );
  if( autoResultMasked != manResult )
  {
    std::cout << "should be: ";
    std::copy(manResult.cbegin(), manResult.cend(), std::ostream_iterator<int>(std::cout << std::hex, " "));
    std::cout << std::endl;
    std::cout << "is:        ";
    std::copy(autoResult.cbegin(), autoResult.cend(), std::ostream_iterator<int>(std::cout << std::hex, " "));
    std::cout << std::endl;
  }
}

BOOST_AUTO_TEST_CASE( boardInfoAreaSetLanguageCode )
{
  boardInfoArea bia;
  bia.setLanguageCode( 25 );
  BOOST_CHECK( bia.getLanguageCode() == 25 );
  std::vector<uint8_t> manResult =   { 0x01, 0x02, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc1, 0x00, 0x00, 0x00, 0x63 };
  std::vector<uint8_t> compareMask = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff };
  std::vector<uint8_t> autoResult = bia.getBinaryData();
  std::vector<uint8_t> autoResultMasked = applyMask(autoResult, compareMask);
  BOOST_CHECK_EQUAL_COLLECTIONS( autoResultMasked.cbegin(), autoResultMasked.cend(), manResult.cbegin(), manResult.cend() );
  if( autoResultMasked != manResult )
  {
    std::cout << "should be: ";
    std::copy(manResult.cbegin(), manResult.cend(), std::ostream_iterator<int>(std::cout << std::hex, " "));
    std::cout << std::endl;
    std::cout << "is:        ";
    std::copy(autoResult.cbegin(), autoResult.cend(), std::ostream_iterator<int>(std::cout << std::hex, " "));
    std::cout << std::endl;
  }
}

BOOST_AUTO_TEST_CASE( boardInfoAreaSetMfgDateTime )
{
  boardInfoArea bia;
  boost::posix_time::ptime dt(boost::posix_time::time_from_string("2013-11-06 16:45:00.000"));
  bia.setMfgDateTime( dt );
  BOOST_CHECK( bia.getMfgDateTime() == dt );
  std::vector<uint8_t> manResult =   { 0x01, 0x02, 0x00, 0x4d, 0x41, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc1, 0x00, 0x00, 0x00, 0x5f };
  std::vector<uint8_t> compareMask = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff };
  std::vector<uint8_t> autoResult = bia.getBinaryData();
  std::vector<uint8_t> autoResultMasked = applyMask(autoResult, compareMask);
  BOOST_CHECK_EQUAL_COLLECTIONS( autoResultMasked.cbegin(), autoResultMasked.cend(), manResult.cbegin(), manResult.cend() );
  if( autoResultMasked != manResult )
  {
    std::cout << "should be: ";
    std::copy(manResult.cbegin(), manResult.cend(), std::ostream_iterator<int>(std::cout << std::hex, " "));
    std::cout << std::endl;
    std::cout << "is:        ";
    std::copy(autoResult.cbegin(), autoResult.cend(), std::ostream_iterator<int>(std::cout << std::hex, " "));
    std::cout << std::endl;
  }
}

BOOST_AUTO_TEST_CASE( boardInfoAreaSetManufacturerName )
{
  boardInfoArea bia;
  std::string manufacturerName("Manufacturer Name");
  bia.setManufacturer( manufacturerName );
  BOOST_CHECK( bia.getManufacturer() == manufacturerName );
  std::vector<uint8_t> manResult =   { 0x01, 0x04, 0x00, 0x00, 0x00, 0x00, 0xc0 + 0x11, 'M',  'a',  'n',  'u',  'f',  'a',  'c',  't',  'u',  'r',  'e',  'r',  ' ',  'N',  'a',  'm',  'e',  0x00, 0x00, 0x00, 0x00, 0xc1, 0x00, 0x00, 0xdb };
  std::vector<uint8_t> compareMask = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x3f, 0x3f, 0x3f, 0xff, 0xff, 0xff, 0xff };
  std::vector<uint8_t> autoResult = bia.getBinaryData();
  std::vector<uint8_t> autoResultMasked = applyMask(autoResult, compareMask);
  BOOST_CHECK_EQUAL_COLLECTIONS( autoResultMasked.cbegin(), autoResultMasked.cend(), manResult.cbegin(), manResult.cend() );
  if( autoResultMasked != manResult )
  {
    std::cout << "should be: ";
    std::copy(manResult.cbegin(), manResult.cend(), std::ostream_iterator<int>(std::cout << std::hex, " "));
    std::cout << std::endl;
    std::cout << "is:        ";
    std::copy(autoResult.cbegin(), autoResult.cend(), std::ostream_iterator<int>(std::cout << std::hex, " "));
    std::cout << std::endl;
  }
}

BOOST_AUTO_TEST_CASE( boardInfoAreaSetProductName )
{
  boardInfoArea bia;
  std::string productName("Product Name");
  bia.setProductName( productName );
  BOOST_CHECK( bia.getProductName() == productName );
  std::vector<uint8_t> manResult =   { 0x01, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0 + 0x0c, 'P',  'r',  'o',  'd',  'u',  'c',  't',  ' ',  'N',  'a',  'm',  'e',  0x00, 0x00, 0x00, 0xc1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xec };
  std::vector<uint8_t> compareMask = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff,        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x3f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
  std::vector<uint8_t> autoResult = bia.getBinaryData();
  std::vector<uint8_t> autoResultMasked = applyMask(autoResult, compareMask);
  BOOST_CHECK_EQUAL_COLLECTIONS( autoResultMasked.cbegin(), autoResultMasked.cend(), manResult.cbegin(), manResult.cend() );
  if( autoResultMasked != manResult )
  {
    std::cout << "should be: ";
    std::copy(manResult.cbegin(), manResult.cend(), std::ostream_iterator<int>(std::cout << std::hex, " "));
    std::cout << std::endl;
    std::cout << "is:        ";
    std::copy(autoResult.cbegin(), autoResult.cend(), std::ostream_iterator<int>(std::cout << std::hex, " "));
    std::cout << std::endl;
  }
}

BOOST_AUTO_TEST_CASE( boardInfoAreaSetSerialNumber )
{
  boardInfoArea bia;
  std::string serialNumber("Serial Number");
  bia.setSerialNumber( serialNumber );
  BOOST_CHECK( bia.getSerialNumber() == serialNumber );
  std::vector<uint8_t> manResult =   { 0x01, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0 + 0x0d, 'S',  'e',  'r',  'i',  'a',  'l',  ' ',  'N',  'u',  'm',  'b',  'e',  'r',  0x00, 0x00, 0xc1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x84 };
  std::vector<uint8_t> compareMask = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x3f, 0xff,        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
  std::vector<uint8_t> autoResult = bia.getBinaryData();
  std::vector<uint8_t> autoResultMasked = applyMask(autoResult, compareMask);
  BOOST_CHECK_EQUAL_COLLECTIONS( autoResultMasked.cbegin(), autoResultMasked.cend(), manResult.cbegin(), manResult.cend() );
  if( autoResultMasked != manResult )
  {
    std::cout << "should be: ";
    std::copy(manResult.cbegin(), manResult.cend(), std::ostream_iterator<int>(std::cout << std::hex, " "));
    std::cout << std::endl;
    std::cout << "is:        ";
    std::copy(autoResult.cbegin(), autoResult.cend(), std::ostream_iterator<int>(std::cout << std::hex, " "));
    std::cout << std::endl;
  }
}

BOOST_AUTO_TEST_CASE( boardInfoAreaSetBoardPartNumber )
{
  boardInfoArea bia;
  std::string partNumber("Part Number");
  bia.setPartNumber( partNumber );
  BOOST_CHECK( bia.getPartNumber() == partNumber );
  std::vector<uint8_t> manResult =   { 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0 + 0x0b, 'P',  'a',  'r',  't',  ' ',  'N',  'u',  'm',  'b',  'e',  'r',  0x00, 0xc1, 0x50 };
  std::vector<uint8_t> compareMask = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x3f, 0x3f, 0xff,        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff };
  std::vector<uint8_t> autoResult = bia.getBinaryData();
  std::vector<uint8_t> autoResultMasked = applyMask(autoResult, compareMask);
  BOOST_CHECK_EQUAL_COLLECTIONS( autoResultMasked.cbegin(), autoResultMasked.cend(), manResult.cbegin(), manResult.cend() );
  if( autoResultMasked != manResult )
  {
    std::cout << "should be: ";
    std::copy(manResult.cbegin(), manResult.cend(), std::ostream_iterator<int>(std::cout << std::hex, " "));
    std::cout << std::endl;
    std::cout << "is:        ";
    std::copy(autoResult.cbegin(), autoResult.cend(), std::ostream_iterator<int>(std::cout << std::hex, " "));
    std::cout << std::endl;
  }
}

BOOST_AUTO_TEST_CASE( boardInfoAreaSetFRUFileId )
{
  boardInfoArea bia;
  std::string fruFileId("FRU File Id");
  bia.setFRUFileId( fruFileId );
  BOOST_CHECK( bia.getFRUFileId() == fruFileId );
  std::vector<uint8_t> manResult =   { 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0 + 0x0b, 'F',  'R',  'U',  ' ',  'F',  'i',  'l',  'e',  ' ',  'I',  'd',  0xc1, 0x16 };
  std::vector<uint8_t> compareMask = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x3f, 0x3f, 0x3f, 0xff,        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
  std::vector<uint8_t> autoResult = bia.getBinaryData();
  std::vector<uint8_t> autoResultMasked = applyMask(autoResult, compareMask);
  BOOST_CHECK_EQUAL_COLLECTIONS( autoResultMasked.cbegin(), autoResultMasked.cend(), manResult.cbegin(), manResult.cend() );
  if( autoResultMasked != manResult )
  {
    std::cout << "should be: ";
    std::copy(manResult.cbegin(), manResult.cend(), std::ostream_iterator<int>(std::cout << std::hex, " "));
    std::cout << std::endl;
    std::cout << "is:        ";
    std::copy(autoResult.cbegin(), autoResult.cend(), std::ostream_iterator<int>(std::cout << std::hex, " "));
    std::cout << std::endl;
  }
}

BOOST_AUTO_TEST_CASE( boardInfoAreaBinarySize16 )
{
  boardInfoArea bia;
  bia.setManufacturer( "XXX" );
  BOOST_CHECK_EQUAL( bia.getBinaryData().size(), 16 );
}

BOOST_AUTO_TEST_CASE( boardInfoAreaSize16 )
{
  boardInfoArea bia;
  bia.setManufacturer( "XXX" );
  BOOST_CHECK_EQUAL( bia.size(), 16 );
}

BOOST_AUTO_TEST_CASE( boardInfoAreaLength16 )
{
  boardInfoArea bia;
  bia.setManufacturer( "XXX" );
  BOOST_CHECK_EQUAL( 8 * bia.getBoardAreaLength(), 16 );
}

BOOST_AUTO_TEST_CASE( boardInfoAreaBinarySize24 )
{
  boardInfoArea bia;
  bia.setManufacturer( "XXXX" );
  BOOST_CHECK_EQUAL( bia.getBinaryData().size(), 24 );
}

BOOST_AUTO_TEST_CASE( boardInfoAreaSize24 )
{
  boardInfoArea bia;
  bia.setManufacturer( "XXXX" );
  BOOST_CHECK_EQUAL( bia.size(), 24 );
}

BOOST_AUTO_TEST_CASE( boardInfoAreaLength24 )
{
  boardInfoArea bia;
  bia.setManufacturer( "XXXX" );
  BOOST_CHECK_EQUAL( 8 * bia.getBoardAreaLength(), 24 );
}

BOOST_AUTO_TEST_CASE( boardInfoAreaBinarySize80 )
{
  boardInfoArea bia;
  bia.setManufacturer( std::string( 63, 'X' ) );
  BOOST_CHECK_EQUAL( bia.getBinaryData().size(), 80 );
}

BOOST_AUTO_TEST_CASE( boardInfoAreaSize80 )
{
  boardInfoArea bia;
  bia.setManufacturer( std::string( 63, 'X' ) );
  BOOST_CHECK_EQUAL( bia.size(), 80 );
}

BOOST_AUTO_TEST_CASE( boardInfoAreaLength80 )
{
  boardInfoArea bia;
  bia.setManufacturer( std::string( 63, 'X' ) );
  BOOST_CHECK_EQUAL( 8 * bia.getBoardAreaLength(), 80 );
}

BOOST_AUTO_TEST_CASE( boardInfoAreaBinarySizeMaximum )
{
  boardInfoArea bia;
  bia.setManufacturer( std::string( 63, 'X' ) );
  bia.setProductName( std::string( 63, 'X' ) );
  bia.setSerialNumber( std::string( 63, 'X' ) );
  bia.setPartNumber( std::string( 46, 'X' ) );
  BOOST_CHECK_EQUAL( bia.getBinaryData().size(), 248 );
}

BOOST_AUTO_TEST_CASE( boardInfoAreaSizeMaximum )
{
  boardInfoArea bia;
  bia.setManufacturer( std::string( 63, 'X' ) );
  bia.setProductName( std::string( 63, 'X' ) );
  bia.setSerialNumber( std::string( 63, 'X' ) );
  bia.setPartNumber( std::string( 46, 'X' ) );
  BOOST_CHECK_EQUAL( bia.size(), 248 );
}

BOOST_AUTO_TEST_CASE( boardInfoAreaLengthMaximum )
{
  boardInfoArea bia;
  bia.setManufacturer( std::string( 63, 'X' ) );
  bia.setProductName( std::string( 63, 'X' ) );
  bia.setSerialNumber( std::string( 63, 'X' ) );
  bia.setPartNumber( std::string( 46, 'X' ) );
  BOOST_CHECK_EQUAL( 8 * bia.getBoardAreaLength(), 248 );
}

BOOST_AUTO_TEST_SUITE_END()