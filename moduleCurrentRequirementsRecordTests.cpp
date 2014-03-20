#include "moduleCurrentRequirementsRecord.hpp"
#include "testUtils.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( moduleCurrentRequirementsRecordTests )

BOOST_AUTO_TEST_CASE( constructor )
{
  moduleCurrentRequirementsRecord mcrr(1);
}

BOOST_AUTO_TEST_CASE( currentTooLow )
{
  BOOST_CHECK_THROW( moduleCurrentRequirementsRecord mcrr( -0.1 ), std::invalid_argument )
}

BOOST_AUTO_TEST_CASE( currentTooHigh )
{
  BOOST_CHECK_THROW( moduleCurrentRequirementsRecord mcrr( 6.7 ), std::invalid_argument )
}

BOOST_AUTO_TEST_CASE( constructorGetBinaryData )
{
  moduleCurrentRequirementsRecord mcrr(1);
  std::vector<uint8_t> manResult = { 0xc0, 0x02, 0x06, 0x55, 0xe3, 0x5a, 0x31, 0x00, 0x16, 0x00, 0x0a };
  std::vector<uint8_t> autoResult = mcrr.getBinaryData();
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

BOOST_AUTO_TEST_CASE( binarySize )
{
  moduleCurrentRequirementsRecord mcrr(1);
  BOOST_CHECK_EQUAL( mcrr.getBinaryData().size(), 11 );
}

BOOST_AUTO_TEST_CASE( size )
{
  moduleCurrentRequirementsRecord mcrr(1);
  BOOST_CHECK_EQUAL( mcrr.size(), 11 );
}

BOOST_AUTO_TEST_SUITE_END()