#include "indirectClockDescriptor.hpp"
#include "testUtils.hpp"
#include <boost/test/unit_test.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/assign/std/vector.hpp>
using namespace boost::assign; // bring 'operator+=()' into scope

BOOST_AUTO_TEST_SUITE( indirectClockDescriptorTests )

BOOST_AUTO_TEST_CASE( constructorEmpty )
{
  indirectPllConnectionMap indirectConnMap;
  indirectPllConnection pll = indirectConnMap["ConnectedThroughPLL"];
  indirectClockAsymmetricMatchMap indirectAsymMap;
  indirectClockAsymmetricMatch match = indirectAsymMap["ClockSource"];
  indirectClockDescriptor icd(pll, match, 0x0a);
}

BOOST_AUTO_TEST_CASE( constructorEmptyGetBinaryData )
{
  indirectPllConnectionMap indirectConnMap;
  indirectPllConnection pll = indirectConnMap["ConnectedThroughPLL"];
  indirectClockAsymmetricMatchMap indirectAsymMap;
  indirectClockAsymmetricMatch match = indirectAsymMap["ClockSource"];
  indirectClockDescriptor icd(pll, match, 0x0a);
  std::vector<uint8_t> manResult = boost::assign::list_of(0x03)(0x0a);
  std::vector<uint8_t> autoResult = icd.getBinaryData();
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
  indirectPllConnectionMap indirectConnMap;
  indirectPllConnection pll = indirectConnMap["ConnectedThroughPLL"];
  indirectClockAsymmetricMatchMap indirectAsymMap;
  indirectClockAsymmetricMatch match = indirectAsymMap["ClockSource"];
  indirectClockDescriptor icd(pll, match, 0x0a);
  BOOST_CHECK_EQUAL( icd.getBinaryData().size(), 2 );
}

BOOST_AUTO_TEST_CASE( size )
{
  indirectPllConnectionMap indirectConnMap;
  indirectPllConnection pll = indirectConnMap["ConnectedThroughPLL"];
  indirectClockAsymmetricMatchMap indirectAsymMap;
  indirectClockAsymmetricMatch match = indirectAsymMap["ClockSource"];
  indirectClockDescriptor icd(pll, match, 0x0a);
  BOOST_CHECK_EQUAL( icd.size(), 2 );
}

BOOST_AUTO_TEST_SUITE_END()