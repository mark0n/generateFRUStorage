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
  std::vector<std::string> body = {"1234", "123456"};
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

BOOST_AUTO_TEST_SUITE_END()
