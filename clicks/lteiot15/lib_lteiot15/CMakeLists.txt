cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lteiot15 LANGUAGES MikroC)
else()
    project(lib_lteiot15 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lteiot15 STATIC
        src/lteiot15.c
        include/lteiot15.h
)
add_library(Click.LTEIoT15  ALIAS lib_lteiot15)



target_include_directories(lib_lteiot15 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lteiot15 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lteiot15 PUBLIC MikroSDK.Driver)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_lteiot15 PUBLIC MikroSDK.GenericPointer)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_lteiot15 PUBLIC MikroSDK.Conversions)

