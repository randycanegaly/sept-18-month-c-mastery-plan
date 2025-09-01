cmake_minimum_required(VERSION 3.10)
project(cl_arg_parser)

#Include CTest for running tests 
include(CTest)

#Add your production code as a library
#add_library(DynTwoDArr STATIC array.c)
#target_include_directories(DynTwoDArr PUBLIC ../../src/week02)

#add_executable(ArrExe array.c)
#target_link_libraries(ArrExe DynTwoDArr)
#target_compile_definitions(ArrExe PRIVATE IS_EXE)

#Add Unity from the submodule
#add_library(Unity STATIC ../../external/unity/src/unity.c)
#target_include_directories(Unity PUBLIC ../../external/unity/src)

#Add test executables
#add_executable(ArrTest ../../test/week02/test_array.c)
#target_link_libraries(ArrTest DynTwoDArr Unity)
#target_link_libraries(ArrTest Unity)

#Register the tests with CTest
#add_test(NAME ArrTest COMMAND ArrTest)

