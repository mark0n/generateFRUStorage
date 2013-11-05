cmake_minimum_required(VERSION 2.8)
project(generateFRUStorage)

set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -g")
set(CMAKE_CXX_COMPILER "clang++")

add_executable(generateFRUStorage main.cpp commonHeader.cpp boardInfoArea.cpp productInfoArea checksum.cpp varLengthField.cpp multiRecordArea.cpp multiRecord.cpp amcPtPConnectivityRecord.cpp amcChannelDescriptor.cpp amcLinkDescriptor.cpp moduleCurrentRequirementsRecord.cpp)