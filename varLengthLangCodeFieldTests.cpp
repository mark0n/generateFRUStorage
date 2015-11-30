#include "varLengthLangCodeField.hpp"
#include "testUtils.hpp"
#include <boost/test/unit_test.hpp>
#include <boost/assign/list_of.hpp>
#include <iostream>

BOOST_AUTO_TEST_SUITE( varLengthLangCodeFieldTests )

BOOST_AUTO_TEST_CASE( defaultConstructorGetString )
{
  varLengthLangCodeField vlf;
  BOOST_CHECK_EQUAL( vlf.getString(), std::string() );
}

BOOST_AUTO_TEST_CASE( defaultConstructorGetBinaryData )
{
  varLengthLangCodeField vlf;
  std::vector<uint8_t> manResult = boost::assign::list_of(0x00);
  std::vector<uint8_t> compareMask = boost::assign::list_of(0x3f);
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

BOOST_AUTO_TEST_CASE( setString )
{
  varLengthLangCodeField vlf;
  vlf.setString("Test string");
  std::vector<uint8_t> manResult = boost::assign::list_of(0xc0 | 0x0b)('T')('e')('s')('t')(' ')('s')('t')('r')('i')('n')('g');
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

BOOST_AUTO_TEST_CASE( setStringEmpty )
{
  varLengthLangCodeField vlf;
  vlf.setString("");
  std::vector<uint8_t> manResult = boost::assign::list_of(0xc0 | 0x00);
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

BOOST_AUTO_TEST_CASE( setStringMaxLength )
{
  varLengthLangCodeField vlf;
  std::string longString( 63, 'X' );
  vlf.setString( longString );
  BOOST_CHECK_EQUAL( vlf.getString().size() , 63);
  BOOST_CHECK_EQUAL( vlf.size(), 64 );
}

BOOST_AUTO_TEST_CASE( tooLong )
{
  varLengthLangCodeField vlf;
  std::string tooLongStr( 64, 'X' );
  BOOST_CHECK_THROW( vlf.setString( tooLongStr ), std::runtime_error);
}

BOOST_AUTO_TEST_SUITE_END()