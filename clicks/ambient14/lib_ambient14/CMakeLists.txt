cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ambient14 LANGUAGES MikroC)
else()
    project(lib_ambient14 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ambient14 STATIC
        src/ambient14.c
        include/ambient14.h
)
add_library(Click.Ambient14  ALIAS lib_ambient14)



target_include_directories(lib_ambient14 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ambient14 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ambient14 PUBLIC MikroSDK.Driver)

