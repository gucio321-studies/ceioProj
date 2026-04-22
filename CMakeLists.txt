cmake_minimum_required(VERSION 3.16)
project(CEIOProj)

find_package(ROOT REQUIRED COMPONENTS RIO Net Hist)

include(${ROOT_USE_FILE})

add_executable(main 
        main.c)
target_link_libraries(main ${ROOT_LIBRARIES})
