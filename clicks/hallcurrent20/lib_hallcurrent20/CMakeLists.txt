cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_hallcurrent20 LANGUAGES MikroC)
else()
    project(lib_hallcurrent20 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_hallcurrent20 STATIC
        src/hallcurrent20.c
        include/hallcurrent20.h
)
add_library(Click.HallCurrent20  ALIAS lib_hallcurrent20)



target_include_directories(lib_hallcurrent20 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_hallcurrent20 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_hallcurrent20 PUBLIC MikroSDK.Driver)

