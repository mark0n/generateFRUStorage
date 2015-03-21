#include "multiRecord.hpp"
#include "testUtils.hpp"
#include <boost/test/unit_test.hpp>
#include <boost/assign/list_of.hpp>

BOOST_AUTO_TEST_SUITE( multiRecordTests )

BOOST_AUTO_TEST_CASE( constructorEmptyPayload )
{
  std::vector<uint8_t> payload;
  multiRecord mr(0x01, payload);
}

BOOST_AUTO_TEST_CASE( constructorEmptyPayloadGetMethods )
{
  std::vector<uint8_t> payload;
  multiRecord mr(0x01, payload);
  BOOST_CHECK_EQUAL( mr.getFormatVersion(), 2 );
  BOOST_CHECK_EQUAL( mr.getEndOfList(), 0 );
  BOOST_CHECK_EQUAL( mr.getRecordLength(), 0 );
  BOOST_CHECK_EQUAL( mr.getChecksum(), 0 );
  BOOST_CHECK_EQUAL( mr.getHeaderChecksum(), 0xfd );
}

BOOST_AUTO_TEST_CASE( constructorGetMethods )
{
  std::vector<uint8_t> payload = boost::assign::list_of(0x02)(0x03)(0x04);
  multiRecord mr(0x01, payload);
  BOOST_CHECK_EQUAL( mr.getFormatVersion(), 2 );
  BOOST_CHECK_EQUAL( mr.getEndOfList(), 0 );
  BOOST_CHECK_EQUAL( mr.getRecordLength(), payload.size() );
  BOOST_CHECK_EQUAL( mr.getChecksum(), 0xf7 );
  BOOST_CHECK_EQUAL( mr.getHeaderChecksum(), 0x03 );
}

BOOST_AUTO_TEST_CASE( constructorGetBinaryData )
{
  std::vector<uint8_t> payload = boost::assign::list_of(0x11)(0x12)(0x13);
  multiRecord mr(0x01, payload);
  std::vector<uint8_t> manResult = boost::assign::list_of(0x01)(0x02)(0x03)(0xca)(0x30)(0x11)(0x12)(0x13);
  std::vector<uint8_t> autoResult = mr.getBinaryData();
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

BOOST_AUTO_TEST_CASE( setEndOfList )
{
  std::vector<uint8_t> payload = boost::assign::list_of(0x11)(0x12)(0x13);
  multiRecord mr(0x01, payload);
  mr.setEndOfList(true);
  std::vector<uint8_t> manResult = boost::assign::list_of(0x01)(0x82)(0x03)(0xca)(0xb0)(0x11)(0x12)(0x13);
  std::vector<uint8_t> autoResult = mr.getBinaryData();
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
  std::vector<uint8_t> payload = boost::assign::list_of(0x11)(0x12)(0x13);
  multiRecord mr(0x01, payload);
  BOOST_CHECK_EQUAL( mr.getBinaryData().size(), 8 );
}

BOOST_AUTO_TEST_CASE( binarySizeMaximum )
{
  std::vector<uint8_t> payload(255);
  std::fill(payload.begin(), payload.end(), 0xa3);
  multiRecord mr(0x01, payload);
  BOOST_CHECK_EQUAL( mr.getBinaryData().size(), 260 );
}

BOOST_AUTO_TEST_CASE( payloadTooLong )
{
  std::vector<uint8_t> payload(256);
  BOOST_CHECK_THROW( multiRecord mr(0x01, payload), std::runtime_error );
}

BOOST_AUTO_TEST_SUITE_END()