cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dac19 LANGUAGES MikroC)
else()
    project(lib_dac19 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dac19 STATIC
        src/dac19.c
        include/dac19.h
)
add_library(Click.DAC19  ALIAS lib_dac19)



target_include_directories(lib_dac19 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dac19 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dac19 PUBLIC MikroSDK.Driver)

