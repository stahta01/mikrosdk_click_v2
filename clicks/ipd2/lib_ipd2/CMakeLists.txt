cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ipd2 LANGUAGES MikroC)
else()
    project(lib_ipd2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ipd2 STATIC
        src/ipd2.c
        include/ipd2.h
)
add_library(Click.IPD2  ALIAS lib_ipd2)



target_include_directories(lib_ipd2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ipd2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ipd2 PUBLIC MikroSDK.Driver)

