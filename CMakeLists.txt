cmake_minimum_required(VERSION 2.8)
project(generateFRUStorage)

set(generateFRUStorage_VERSION_MAJOR 0)
set(generateFRUStorage_VERSION_MINOR 1)
set(generateFRUStorage_VERSION_PATCH 0)

set(VERSION_STRING "${generateFRUStorage_VERSION_MAJOR}.${generateFRUStorage_VERSION_MINOR}.${generateFRUStorage_VERSION_PATCH}")

if(EXISTS "${PROJECT_SOURCE_DIR}/.git")
  set(VERSION_STRING "${VERSION_STRING}-git")
endif(EXISTS "${PROJECT_SOURCE_DIR}/.git")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
# set(CMAKE_CXX_COMPILER "clang++")

enable_testing()

find_package(Boost COMPONENTS date_time unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR})
find_package(Sreccat)

# configure a header file to pass some of the CMake settings to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)

# add the binary tree to the search path for include files so that we will find
# config.h
include_directories("${PROJECT_BINARY_DIR}")

set(GENERATEFRUSTORAGE_SRC
  main.cpp
  commonHeader.cpp
  boardInfoArea.cpp
  productInfoArea.cpp
  varLengthLangCodeField.cpp
  varLengthField.cpp
  multiRecordArea.cpp
  multiRecord.cpp
  amcPtPConnectivityRecord.cpp
  amcChannelDescriptor.cpp
  amcLinkDescriptor.cpp
  moduleCurrentRequirementsRecord.cpp
  interfaceIdentifierBody.cpp
  uTCAZone3InterfaceCompatibilityRecord.cpp
)

add_executable(generateFRUStorage ${GENERATEFRUSTORAGE_SRC})
target_link_libraries(generateFRUStorage ${Boost_LIBRARIES})

add_custom_command(
  OUTPUT ${PROJECT_BINARY_DIR}/FRU_data_FGPDB.bin
  COMMAND ./generateFRUStorage -i ${PROJECT_SOURCE_DIR}/FRU_data_FGPDB.json -o ${PROJECT_BINARY_DIR}/FRU_data_FGPDB.bin
  DEPENDS generateFRUStorage
  COMMENT "Generating binary FRU data file"
  VERBATIM
)

add_custom_target(
  binFile ALL
  DEPENDS ${PROJECT_BINARY_DIR}/FRU_data_FGPDB.bin
)

if(SRECCAT_FOUND)
  add_custom_command(
    DEPENDS ${PROJECT_BINARY_DIR}/FRU_data_FGPDB.bin
    OUTPUT ${PROJECT_BINARY_DIR}/FRU_data_FGPDB.hex
    COMMAND srec_cat ${PROJECT_BINARY_DIR}/FRU_data_FGPDB.bin -binary -output ${PROJECT_BINARY_DIR}/FRU_data_FGPDB.hex -intel
    COMMENT "Converting FRU data file to Intel hex format"
    VERBATIM
  )

  add_custom_target(
    hexFile ALL
    DEPENDS ${PROJECT_BINARY_DIR}/FRU_data_FGPDB.hex
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
  multiRecordAreaTests.cpp
  multiRecordTests.cpp
  moduleCurrentRequirementsRecordTests.cpp
  amcPtPConnectivityRecordTests.cpp
  amcChannelDescriptorTests.cpp
  amcLinkDescriptorTests.cpp
  varLengthLangCodeFieldTests.cpp
  interfaceIdentifierBodyTests.cpp
  commonHeader.cpp
  boardInfoArea.cpp
  productInfoArea.cpp
  multiRecordArea.cpp
  multiRecord.cpp
  moduleCurrentRequirementsRecord.cpp
  amcChannelDescriptor.cpp
  amcLinkDescriptor.cpp
  amcPtPConnectivityRecord.cpp
  varLengthLangCodeField.cpp
  varLengthField.cpp
  interfaceIdentifierBody.cpp
  uTCAZone3InterfaceCompatibilityRecord.cpp
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
