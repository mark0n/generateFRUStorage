#include "varLengthLangCodeField.hpp"

BOOST_AUTO_TEST_SUITE( varLengthLangCodeFieldTests )

BOOST_AUTO_TEST_CASE( varLengthLangCodeFieldDefaultConstructorGetString )
{
  varLengthLangCodeField vlf;
  BOOST_CHECK_EQUAL( vlf.getString(), std::string() );
}

BOOST_AUTO_TEST_CASE( varLengthLangCodeFieldDefaultConstructorGetBinaryData )
{
  varLengthLangCodeField vlf;
  std::vector<uint8_t> manResult = { 0x00 };
  std::vector<uint8_t> compareMask = { 0x3f };
  std::vector<uint8_t> autoResult = vlf.getBinaryData();
  std::vector<uint8_t> autoResultMasked = applyMask(autoResult, compareMask);
  BOOST_CHECK( autoResultMasked == manResult );
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

BOOST_AUTO_TEST_CASE( varLengthLangCodeFieldSetString )
{
  varLengthLangCodeField vlf;
  vlf.setString("Test string");
  std::vector<uint8_t> manResult = { 0xc0 | 0x0b, 'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g' };
  std::vector<uint8_t> autoResult = vlf.getBinaryData();
  BOOST_CHECK( autoResult == manResult );
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

BOOST_AUTO_TEST_CASE( varLengthLangCodeFieldSetStringEmpty )
{
  varLengthLangCodeField vlf;
  vlf.setString("");
  std::vector<uint8_t> manResult = { 0xc0 | 0x00 };
  std::vector<uint8_t> autoResult = vlf.getBinaryData();
  BOOST_CHECK( autoResult == manResult );
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

BOOST_AUTO_TEST_CASE( varLengthLangCodeFieldTooLong )
{
  varLengthLangCodeField vlf;
  std::string tooLong( 64, 'X' );
  BOOST_CHECK_THROW( vlf.setString( tooLong ), std::runtime_error);
}

BOOST_AUTO_TEST_SUITE_END()