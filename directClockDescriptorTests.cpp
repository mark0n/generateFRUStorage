#include "directClockDescriptor.hpp"
#include "testUtils.hpp"
#include <boost/test/unit_test.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/assign/std/vector.hpp>
#include <iostream>
using namespace boost::assign; // bring 'operator+=()' into scope

BOOST_AUTO_TEST_SUITE( directClockDescriptorTests )

BOOST_AUTO_TEST_CASE( constructorEmpty )
{
  directPllConnectionMap directConnMap;
  directPllConnection pll = directConnMap["Connected through PLL"];
  directClockAsymmetricMatchMap directAsymMap;
  directClockAsymmetricMatch match = directAsymMap["Clock source"];
  clockAccuracyLevelAcronymMap acronymMap;
  clockAccuracyLevelAcronym acc = acronymMap["ST4"];
  directClockDescriptor(pll, match, 0x00, acc, 0x00000000, 0x00000000, 0x00000000);
}

BOOST_AUTO_TEST_CASE( constructorEmptyGetBinaryData )
{
  directPllConnectionMap directConnMap;
  directPllConnection pll = directConnMap["Connected through PLL"];
  directClockAsymmetricMatchMap directAsymMap;
  directClockAsymmetricMatch match = directAsymMap["Clock source"];
  clockAccuracyLevelAcronymMap acronymMap;
  clockAccuracyLevelAcronym acc = acronymMap["ST4"];
  directClockDescriptor cd(pll, match, 0x01, acc, 0x00178F40, 0x00001F40, 0x0128A180);
  std::vector<uint8_t> manResult = boost::assign::list_of(0x03)(0x01)(0x50)(0x40)(0x8F)(0x17)(0x00)(0x40)(0x1F)(0x00)(0x00)(0x80)(0xA1)(0x28)(0x01);
  std::vector<uint8_t> autoResult = cd.getBinaryData();
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

BOOST_AUTO_TEST_CASE( clockFamilyReserved )
{
  directPllConnectionMap directConnMap;
  directPllConnection pll = directConnMap["Connected through PLL"];
  directClockAsymmetricMatchMap directAsymMap;
  directClockAsymmetricMatch match = directAsymMap["Clock source"];
  clockAccuracyLevelAcronymMap acronymMap;
  clockAccuracyLevelAcronym acc = acronymMap["ST4"];
  BOOST_CHECK_THROW( directClockDescriptor cd(pll, match, 0x04, acc, 0x00000000, 0x00000000, 0x00000000), std::out_of_range );
}

BOOST_AUTO_TEST_CASE( binarySize )
{
  directPllConnectionMap directConnMap;
  directPllConnection pll = directConnMap["Connected through PLL"];
  directClockAsymmetricMatchMap directAsymMap;
  directClockAsymmetricMatch match = directAsymMap["Clock source"];
  clockAccuracyLevelAcronymMap acronymMap;
  clockAccuracyLevelAcronym acc = acronymMap["ST4"];
  directClockDescriptor cd(pll, match, 0x01, acc, 0x00178F40, 0x00001F40, 0x0128A180);
  BOOST_CHECK_EQUAL( cd.getBinaryData().size(), 15 );
}

BOOST_AUTO_TEST_CASE( size )
{
  directPllConnectionMap directConnMap;
  directPllConnection pll = directConnMap["Connected through PLL"];
  directClockAsymmetricMatchMap directAsymMap;
  directClockAsymmetricMatch match = directAsymMap["Clock source"];
  clockAccuracyLevelAcronymMap acronymMap;
  clockAccuracyLevelAcronym acc = acronymMap["ST4"];
  directClockDescriptor cd(pll, match, 0x00, acc, 0x00000000, 0x00000000, 0x00000000);
  BOOST_CHECK_EQUAL( cd.size(), 15 );
}

BOOST_AUTO_TEST_SUITE_END()
