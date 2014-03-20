cmake_minimum_required(VERSION 2.8)
project(generateFRUStorage)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
# set(CMAKE_CXX_COMPILER "clang++")

enable_testing()

find_package(Boost COMPONENTS date_time unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR})
find_package(Sreccat)

add_executable(generateFRUStorage main.cpp commonHeader.cpp boardInfoArea.cpp productInfoArea varLengthLangCodeField.cpp varLengthField.cpp multiRecordArea.cpp multiRecord.cpp amcPtPConnectivityRecord.cpp amcChannelDescriptor.cpp amcLinkDescriptor.cpp moduleCurrentRequirementsRecord.cpp)
target_link_libraries(generateFRUStorage ${Boost_LIBRARIES})

add_custom_command(
  OUTPUT fru_data.bin
  COMMAND ./generateFRUStorage
  DEPENDS generateFRUStorage
  COMMENT "Generating binary FRU data file"
  VERBATIM
)

add_custom_target(
  binFile ALL
  DEPENDS fru_data.bin
)

if(SRECCAT_FOUND)
  add_custom_command(
    DEPENDS fru_data.bin
    OUTPUT fru_data.hex
    COMMAND srec_cat fru_data.bin -binary -output fru_data.hex -intel
    COMMENT "Converting FRU data file to Intel hex format"
    VERBATIM
  )

  add_custom_target(
    hexFile ALL
    DEPENDS fru_data.hex
  )
else(SRECCAT_FOUND)
  message(WARNING "srec_cat not found, skipping generation of hex file")
endif(SRECCAT_FOUND)

set(TEST_COMPONENTS
  testGenerateFRUStorage.cpp
  testUtils.cpp 
  checksumTests.cpp
  commonHeaderTests.cpp
  boardInfoAreaTests.cpp
  productInfoAreaTests.cpp
  multiRecordTests.cpp
  moduleCurrentRequirementsRecordTests.cpp
  amcPtPConnectivityRecordTests.cpp
  amcChannelDescriptorTests.cpp
  amcLinkDescriptorTests.cpp
  varLengthLangCodeFieldTests.cpp
  commonHeader.cpp
  boardInfoArea.cpp
  productInfoArea.cpp
  multiRecord.cpp
  moduleCurrentRequirementsRecord.cpp
  amcChannelDescriptor.cpp
  amcLinkDescriptor.cpp
  amcPtPConnectivityRecord.cpp
  varLengthLangCodeField.cpp
  varLengthField.cpp
)

add_executable(testGenerateFRUStorage ${TEST_COMPONENTS})
target_link_libraries(testGenerateFRUStorage ${Boost_LIBRARIES})

function(get_tests parent_tests target)
  get_target_property(sourceFiles ${target} SOURCES)
  set(tests "")
  set(test_suite "")
  foreach(sourceFile ${sourceFiles})
    file(READ "${sourceFile}" content)
    string(REGEX MATCHALL "[ \t]*BOOST_AUTO_TEST_(CASE|SUITE)[ \t]*\\([ \t]*([A-Za-z0-9_]+)[ \t]*\\)" test_lines ${content})
    foreach(test_line ${test_lines})
      if(${test_line} MATCHES "[ \t]*BOOST_AUTO_TEST_SUITE[ \t]*\\([ \t]*([A-Za-z0-9_]+)[ \t]*\\)")
        string(REGEX REPLACE ".*\\([ \t]*([A-Za-z0-9_]+)[ \t]*\\)" "\\1/" test_suite "${test_line}")
      else(${test_line} MATCHES "[ \t]*BOOST_AUTO_TEST_SUITE[ \t]*\\([ \t]*([A-Za-z0-9_]+)[ \t]*\\)")
        string(REGEX REPLACE ".*\\([ \t]*([A-Za-z0-9_]+)[ \t]*\\)" "\\1" test_name "${test_line}")
        set(tests ${tests} ${test_suite}${test_name})
      endif(${test_line} MATCHES "[ \t]*BOOST_AUTO_TEST_SUITE[ \t]*\\([ \t]*([A-Za-z0-9_]+)[ \t]*\\)")
    endforeach()
  endforeach()
  set(${parent_tests} ${tests} PARENT_SCOPE)
endfunction()

function(add_boost_tests target)
  get_tests(tests ${target})
  foreach(test ${tests})
    add_test(NAME ${test} COMMAND ${target} --run_test=${test})
  endforeach()
endfunction()

add_boost_tests(testGenerateFRUStorage)

if(CMAKE_BUILD_TYPE MATCHES Debug)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -W -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings -fprofile-arcs -ftest-coverage")
  include(CodeCoverage)
  setup_target_for_coverage(testGenerateFRUStorage_coverage testGenerateFRUStorage coverage '*Tests.cpp')
endif(CMAKE_BUILD_TYPE MATCHES Debug)
