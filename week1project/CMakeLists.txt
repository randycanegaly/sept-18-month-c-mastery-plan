cmake_minimum_required(VERSION 3.10)
project(CLArgsParser)

#Include CTest for running tests 
include(CTest)

#create library for tdd Unity framework
message("the starting path here is ${CMAKE_SOURCE_DIR}")
add_library(Unity STATIC ../external/unity/src/unity.c)
target_include_directories(Unity PUBLIC ../external/unity/src)

#create program code as a library 
add_library(CLArgs STATIC src/cl_args.c)
target_include_directories(CLArgs PUBLIC src)

#create the test executable
add_executable(CLArgsTest test/test_cl_args.c)
target_link_libraries(CLArgsTest CLArgs Unity)

#add the test
add_test(NAME CLArgsTest COMMAND CLArgsTest)

#create program executable
add_executable(CLArgsExe src/cl_args.c)
target_link_libraries(CLArgsExe CLArgs)
target_compile_definitions(CLArgsExe PRIVATE IS_EXE)
