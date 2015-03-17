#include "interfaceIdentifierBody.hpp"
#include "testUtils.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( interfaceIdentifierBodyTests )

BOOST_AUTO_TEST_CASE( identifierOutOfRange )
{
  std::vector<std::string> body;
  BOOST_CHECK_THROW( interfaceIdentifierBody iib(0, body), std::out_of_range);
  BOOST_CHECK_THROW( interfaceIdentifierBody iib(5, body), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( identifierValue1 )
{
  std::vector<std::string> body = {"123456", "1", "1", "1"};
  BOOST_CHECK_THROW( interfaceIdentifierBody iib(1, body), std::out_of_range);
  body = {"1234567890", "123", "123", "12345678901234567890"};
  BOOST_CHECK_THROW( interfaceIdentifierBody iib(1, body), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( identifierValue2 )
{
  std::vector<std::string> body = {"123456789012345678901234567890"};
  BOOST_CHECK_THROW( interfaceIdentifierBody iib(2, body), std::out_of_range);
  body = {"1234567890123456789012345678901234"};
  BOOST_CHECK_THROW( interfaceIdentifierBody iib(2, body), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( identifierValue3 )
{
  std::vector<std::string> body = {"0234", "123456"};
  BOOST_CHECK_THROW( interfaceIdentifierBody iib(3, body), std::out_of_range);
  body = {"12345678", "1234567890"};
  BOOST_CHECK_THROW( interfaceIdentifierBody iib(3, body), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( identifierValue4 )
{
  std::vector<std::string> body = {"1234"};
  BOOST_CHECK_THROW( interfaceIdentifierBody iib(4, body), std::out_of_range);
  body = {"1234567890"};
  BOOST_CHECK_THROW( interfaceIdentifierBody iib(4, body), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( constructorGetBinaryData1 )
{
  std::vector<std::string> body = { "12345678", "01", "02", "0123" };
  interfaceIdentifierBody iib( 1, body );
  std::vector<uint8_t> manResult = { 0x78, 0x56, 0x34, 0x12, 0x01, 0x02, 0x23, 0x01 };
  std::vector<uint8_t> autoResult = iib.getBinaryData();
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

BOOST_AUTO_TEST_CASE( constructorGetBinaryData2 )
{
  std::vector<std::string> body = { "0123456789ABCDEF0000000000000000" };
  interfaceIdentifierBody iib(2, body);
  std::vector<uint8_t> manResult = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xEF, 0xCD, 0xAB, 0x89, 0x67, 0x45, 0x23, 0x01 };
  std::vector<uint8_t> autoResult = iib.getBinaryData();
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

BOOST_AUTO_TEST_CASE( constructorGetBinaryData3 )
{
  std::vector<std::string> body = { "123456", "12345678" };
  interfaceIdentifierBody iib(3, body);
  std::vector<uint8_t> manResult = { 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12 };
  std::vector<uint8_t> autoResult = iib.getBinaryData();
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

BOOST_AUTO_TEST_CASE( constructorGetBinaryData4 )
{
  std::vector<std::string> body = { "12345678" };
  interfaceIdentifierBody iib(4, body);
  std::vector<uint8_t> manResult = { 0x78, 0x56, 0x34, 0x12 };
  std::vector<uint8_t> autoResult = iib.getBinaryData();
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

BOOST_AUTO_TEST_CASE( binarySize1 )
{
  std::vector<std::string> body = { "12345678", "01", "02", "0123" };
  interfaceIdentifierBody iib( 1, body );
  BOOST_CHECK_EQUAL(iib.getBinaryData().size(), 8);
}

BOOST_AUTO_TEST_CASE( binarySize2 )
{
  std::vector<std::string> body = { "0123456789ABCDEF0000000000000000" };
  interfaceIdentifierBody iib(2, body);
  BOOST_CHECK_EQUAL(iib.getBinaryData().size(), 16);
}

BOOST_AUTO_TEST_CASE( binarySize3 )
{
  std::vector<std::string> body = { "123456", "12345678" };
  interfaceIdentifierBody iib(3, body);
  BOOST_CHECK_EQUAL(iib.getBinaryData().size(), 7);
}

BOOST_AUTO_TEST_CASE( binarySize4 )
{
  std::vector<std::string> body = { "12345678" };
  interfaceIdentifierBody iib(4, body);
  BOOST_CHECK_EQUAL(iib.getBinaryData().size(), 4);
}

BOOST_AUTO_TEST_CASE( size1 )
{
  std::vector<std::string> body = { "12345678", "01", "02", "0123" };
  interfaceIdentifierBody iib( 1, body );
  BOOST_CHECK_EQUAL(iib.size(), 8);
}

BOOST_AUTO_TEST_CASE( size2 )
{
  std::vector<std::string> body = { "0123456789ABCDEF0000000000000000" };
  interfaceIdentifierBody iib(2, body);
  BOOST_CHECK_EQUAL(iib.size(), 16);
}

BOOST_AUTO_TEST_CASE( size3 )
{
  std::vector<std::string> body = { "123456", "12345678" };
  interfaceIdentifierBody iib(3, body);
  BOOST_CHECK_EQUAL(iib.size(), 7);
}

BOOST_AUTO_TEST_CASE( size4 )
{
  std::vector<std::string> body = { "12345678" };
  interfaceIdentifierBody iib(4, body);
  BOOST_CHECK_EQUAL(iib.size(), 4);
}

BOOST_AUTO_TEST_SUITE_END()
