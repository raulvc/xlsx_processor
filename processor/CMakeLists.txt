cmake_minimum_required(VERSION 3.4)
project(XLSX_Processor)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Manager.cpp Manager.h Parser.cpp Parser.h DataRow.cpp DataRow.h ForceParser.cpp ForceParser.h DeformationParser.cpp DeformationParser.h Parser.cpp Parser.h)
find_package(Threads)
add_executable(XLSX_Processor ${SOURCE_FILES})
target_link_libraries(XLSX_Processor ${CMAKE_THREAD_LIBS_INIT})
