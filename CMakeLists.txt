cmake_minimum_required(VERSION 2.8)
project(generateFRUStorage)

set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -g")
set(CMAKE_CXX_COMPILER "clang++")

enable_testing()

find_package(Boost COMPONENTS date_time unit_test_framework)

add_executable(generateFRUStorage main.cpp commonHeader.cpp boardInfoArea.cpp productInfoArea checksum.cpp varLengthField.cpp multiRecordArea.cpp multiRecord.cpp amcPtPConnectivityRecord.cpp amcChannelDescriptor.cpp amcLinkDescriptor.cpp moduleCurrentRequirementsRecord.cpp)
target_link_libraries(generateFRUStorage ${Boost_LIBRARIES})

add_executable(testGenerateFRUStorage testGenerateFRUStorage.cpp commonHeader.cpp checksum.cpp)
target_link_libraries(testGenerateFRUStorage ${Boost_LIBRARIES})

function(get_tests parent_tests target)
        get_target_property(sourceFiles ${target} SOURCES)
        set(tests "")
        foreach(sourceFile ${sourceFiles})
                file(READ "${sourceFile}" content)
                string(REGEX MATCHALL "[ \t]*BOOST_AUTO_TEST_CASE[ \t]*\\([ \t]*([A-Za-z0-9_]+)[ \t]*\\)" test_lines ${content})
                foreach(test_line ${test_lines})
                        string(REGEX REPLACE ".*\\([ \t]*([A-Za-z0-9_]+)[ \t]*\\)" "\\1" test_name "${test_line}")
                        set(tests ${tests} ${test_name})
                endforeach()
        endforeach()
        set(${parent_tests} ${tests} PARENT_SCOPE)
endfunction()

function(add_boost_tests target)
        get_tests(tests ${target})
        foreach(test ${tests})
                add_test(NAME ${target}-${test} COMMAND ${target} --run-test=${test})
        endforeach()
endfunction()

add_boost_tests(testGenerateFRUStorage)