#include "varLengthField.hpp"

BOOST_AUTO_TEST_SUITE( varLengthFieldTests )

BOOST_AUTO_TEST_CASE( varLengthFieldConstructor )
{
  varLengthField vlf;
  BOOST_CHECK_EQUAL( vlf.getString(), std::string() );
}

BOOST_AUTO_TEST_CASE( varLengthFieldTooLong )
{
  varLengthField vlf;
  std::string tooLong( 64, 'X' );
  BOOST_CHECK_THROW( vlf.setString( tooLong ), std::runtime_error);
}

BOOST_AUTO_TEST_SUITE_END()