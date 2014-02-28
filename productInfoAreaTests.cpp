#include "productInfoArea.hpp"
#include "testUtils.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( productInfoAreaTests )

BOOST_AUTO_TEST_CASE( constructor )
{
  productInfoArea pia;
}

BOOST_AUTO_TEST_CASE( defaultConstructorGetMethods )
{
  productInfoArea pia;
  BOOST_CHECK_EQUAL( pia.getFormatVersion(), 1 );
  BOOST_CHECK_EQUAL( pia.getProductAreaLength(), 2 );
  BOOST_CHECK_EQUAL( pia.getLanguageCode(), 0 );
  BOOST_CHECK_EQUAL( pia.getManufacturer(), "" );
  BOOST_CHECK_EQUAL( pia.getProductName(), "" );
  BOOST_CHECK_EQUAL( pia.getPartNumber(), "" );
  BOOST_CHECK_EQUAL( pia.getVersion(), "" );
  BOOST_CHECK_EQUAL( pia.getSerialNumber(), "" );
  BOOST_CHECK_EQUAL( pia.getAssetTag(), "" );
  BOOST_CHECK_EQUAL( pia.getFRUFileId(), "" );
  BOOST_CHECK_EQUAL( pia.getChecksum(), 0xfc );
  BOOST_CHECK_EQUAL( pia.size(), 16 );
  std::vector<uint8_t> autoResult = pia.getBinaryData();
}

BOOST_AUTO_TEST_CASE( defaultConstructorGetBinaryData )
{
  productInfoArea pia;
  std::vector<uint8_t> manResult =   { 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc1, 0x00, 0x00, 0x00, 0x00, 0xfc };
  std::vector<uint8_t> compareMask = { 0xff, 0xff, 0xff, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
  std::vector<uint8_t> autoResult = pia.getBinaryData();
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

BOOST_AUTO_TEST_CASE( setLanguageCode )
{
  productInfoArea pia;
  pia.setLanguageCode( 25 );
  BOOST_CHECK( pia.getLanguageCode() == 25 );
  std::vector<uint8_t> manResult =   { 0x01, 0x02, 25,   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc1, 0x00, 0x00, 0x00, 0x00, 0xe3 };
  std::vector<uint8_t> compareMask = { 0xff, 0xff, 0xff, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
  std::vector<uint8_t> autoResult = pia.getBinaryData();
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

BOOST_AUTO_TEST_CASE( setManufacturerName )
{
  productInfoArea pia;
  std::string manufacturerName("Manufacturer Name");
  pia.setManufacturer( manufacturerName );
  BOOST_CHECK( pia.getManufacturer() == manufacturerName );
  std::vector<uint8_t> manResult =   { 0x01, 0x04, 0x00, 0xc0 + 0x11, 'M',  'a',  'n',  'u',  'f',  'a',  'c',  't',  'u',  'r',  'e',  'r',  ' ',  'N',  'a',  'm',  'e',  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc1, 0x00, 0x00, 0x00, 0x5b };
  std::vector<uint8_t> compareMask = { 0xff, 0xff, 0xff, 0xff,        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff };
  std::vector<uint8_t> autoResult = pia.getBinaryData();
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

BOOST_AUTO_TEST_CASE( setProductName )
{
  productInfoArea pia;
  std::string productName("Product Name");
  pia.setProductName( productName );
  BOOST_CHECK( pia.getProductName() == productName );
  std::vector<uint8_t> manResult =   { 0x01, 0x03, 0x00, 0x00, 0xc0 + 0x0c, 'P',  'r',  'o',  'd',  'u',  'c',  't',  ' ',  'N',  'a',  'm',  'e',  0x00, 0x00, 0x00, 0x00, 0x00, 0xc1, 0x6d };
  std::vector<uint8_t> compareMask = { 0xff, 0xff, 0xff, 0x3f, 0xff,        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0xff, 0xff };
  std::vector<uint8_t> autoResult = pia.getBinaryData();
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

BOOST_AUTO_TEST_CASE( setPartNumber )
{
  productInfoArea pia;
  std::string partNumber("Part Number");
  pia.setPartNumber( partNumber );
  BOOST_CHECK( pia.getPartNumber() == partNumber );
  std::vector<uint8_t> manResult =   { 0x01, 0x03, 0x00, 0x00, 0x00, 0xc0 + 0x0b, 'P',  'a',  'r',  't',  ' ',  'N',  'u',  'm',  'b',  'e',  'r',  0x00, 0x00, 0x00, 0x00, 0xc1, 0x00, 0xd0 };
  std::vector<uint8_t> compareMask = { 0xff, 0xff, 0xff, 0x3f, 0x3f, 0xff,        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x3f, 0x3f, 0x3f, 0xff, 0xff, 0xff };
  std::vector<uint8_t> autoResult = pia.getBinaryData();
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

BOOST_AUTO_TEST_CASE( setVersion )
{
  productInfoArea pia;
  std::string version("Version");
  pia.setVersion( version );
  BOOST_CHECK( pia.getVersion() == version );
  std::vector<uint8_t> manResult =   { 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0xc0 + 0x07, 'V',  'e',  'r',  's',  'i',  'o',  'n',  0x00, 0x00, 0x00, 0xc1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e };
  std::vector<uint8_t> compareMask = { 0xff, 0xff, 0xff, 0x3f, 0x3f, 0x3f, 0xff,        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x3f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
  std::vector<uint8_t> autoResult = pia.getBinaryData();
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

BOOST_AUTO_TEST_CASE( setSerialNumber )
{
  productInfoArea pia;
  std::string serialNumber("Serial Number");
  pia.setSerialNumber( serialNumber );
  BOOST_CHECK( pia.getSerialNumber() == serialNumber );
  std::vector<uint8_t> manResult =   { 0x01, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0 + 0x0d, 'S',  'e',  'r',  'i',  'a',  'l',  ' ',  'N',  'u',  'm',  'b',  'e',  'r',  0x00, 0x00, 0xc1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04 };
  std::vector<uint8_t> compareMask = { 0xff, 0xff, 0xff, 0x3f, 0x3f, 0x3f, 0x3f, 0xff,        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
  std::vector<uint8_t> autoResult = pia.getBinaryData();
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

BOOST_AUTO_TEST_CASE( setAssetTag )
{
  productInfoArea pia;
  std::string assetTag("Asset Tag");
  pia.setAssetTag( assetTag );
  BOOST_CHECK( pia.getAssetTag() == assetTag );
  std::vector<uint8_t> manResult =   { 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0 + 0x09, 'A',  's',  's',  'e',  't',  ' ',  'T',  'a',  'g',  0x00, 0xc1, 0x00, 0x00, 0x00, 0xb6 };
  std::vector<uint8_t> compareMask = { 0xff, 0xff, 0xff, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0xff,        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff };
  std::vector<uint8_t> autoResult = pia.getBinaryData();
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

BOOST_AUTO_TEST_CASE( setFRUFileId )
{
  productInfoArea pia;
  std::string fruFileId("FRU File Id");
  pia.setFRUFileId( fruFileId );
  BOOST_CHECK( pia.getFRUFileId() == fruFileId );
  std::vector<uint8_t> manResult =   { 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0 + 0x0b, 'F',  'R',  'U',  ' ',  'F',  'i',  'l',  'e',  ' ',  'I',  'd',  0xc1, 0x00, 0x96 };
  std::vector<uint8_t> compareMask = { 0xff, 0xff, 0xff, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f,        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
  std::vector<uint8_t> autoResult = pia.getBinaryData();
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

BOOST_AUTO_TEST_CASE( binarySize16 )
{
  productInfoArea pia;
  pia.setManufacturer( "XXXX" );
  BOOST_CHECK_EQUAL( pia.getBinaryData().size(), 16 );
}

BOOST_AUTO_TEST_CASE( size16 )
{
  productInfoArea pia;
  pia.setManufacturer( "XXXX" );
  BOOST_CHECK_EQUAL( pia.size(), 16 );
}

BOOST_AUTO_TEST_CASE( length16 )
{
  productInfoArea pia;
  pia.setManufacturer( "XXXX" );
  BOOST_CHECK_EQUAL( 8 * pia.getProductAreaLength(), 16 );
}

BOOST_AUTO_TEST_CASE( binarySize24 )
{
  productInfoArea pia;
  pia.setManufacturer( "XXXXX" );
  BOOST_CHECK_EQUAL( pia.getBinaryData().size(), 24 );
}

BOOST_AUTO_TEST_CASE( size24 )
{
  productInfoArea pia;
  pia.setManufacturer( "XXXXX" );
  BOOST_CHECK_EQUAL( pia.size(), 24 );
}

BOOST_AUTO_TEST_CASE( length24 )
{
  productInfoArea pia;
  pia.setManufacturer( "XXXXX" );
  BOOST_CHECK_EQUAL( 8 * pia.getProductAreaLength(), 24 );
}

BOOST_AUTO_TEST_CASE( binarySize80 )
{
  productInfoArea pia;
  pia.setManufacturer( std::string( 63, 'X' ) );
  BOOST_CHECK_EQUAL( pia.getBinaryData().size(), 80 );
}

BOOST_AUTO_TEST_CASE( size80 )
{
  productInfoArea pia;
  pia.setManufacturer( std::string( 63, 'X' ) );
  BOOST_CHECK_EQUAL( pia.size(), 80 );
}

BOOST_AUTO_TEST_CASE( length80 )
{
  productInfoArea pia;
  pia.setManufacturer( std::string( 63, 'X' ) );
  BOOST_CHECK_EQUAL( 8 * pia.getProductAreaLength(), 80 );
}

BOOST_AUTO_TEST_CASE( binarySizeMaximum )
{
  productInfoArea pia;
  pia.setManufacturer( std::string( 63, 'X' ) );
  pia.setProductName( std::string( 63, 'X' ) );
  pia.setPartNumber( std::string( 63, 'X' ) );
  pia.setVersion( std::string( 63, 'X' ) );
  pia.setSerialNumber( std::string( 63, 'X' ) );
  pia.setAssetTag( std::string( 63, 'X' ) );
  pia.setFRUFileId( std::string( 63, 'X' ) );
  BOOST_CHECK_EQUAL( pia.getBinaryData().size(), 456 );
}

BOOST_AUTO_TEST_CASE( sizeMaximum )
{
  productInfoArea pia;
  pia.setManufacturer( std::string( 63, 'X' ) );
  pia.setProductName( std::string( 63, 'X' ) );
  pia.setPartNumber( std::string( 63, 'X' ) );
  pia.setVersion( std::string( 63, 'X' ) );
  pia.setSerialNumber( std::string( 63, 'X' ) );
  pia.setAssetTag( std::string( 63, 'X' ) );
  pia.setFRUFileId( std::string( 63, 'X' ) );
  BOOST_CHECK_EQUAL( pia.size(), 456 );
}

BOOST_AUTO_TEST_CASE( lengthMaximum )
{
  productInfoArea pia;
  pia.setManufacturer( std::string( 63, 'X' ) );
  pia.setProductName( std::string( 63, 'X' ) );
  pia.setPartNumber( std::string( 63, 'X' ) );
  pia.setVersion( std::string( 63, 'X' ) );
  pia.setSerialNumber( std::string( 63, 'X' ) );
  pia.setAssetTag( std::string( 63, 'X' ) );
  pia.setFRUFileId( std::string( 63, 'X' ) );
  BOOST_CHECK_EQUAL( 8 * pia.getProductAreaLength(), 456 );
}

BOOST_AUTO_TEST_SUITE_END()