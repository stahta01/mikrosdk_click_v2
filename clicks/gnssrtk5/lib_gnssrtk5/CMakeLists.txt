cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_gnssrtk5 LANGUAGES MikroC)
else()
    project(lib_gnssrtk5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_gnssrtk5 STATIC
        src/gnssrtk5.c
        include/gnssrtk5.h
)
add_library(Click.GNSSRTK5  ALIAS lib_gnssrtk5)



target_include_directories(lib_gnssrtk5 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_gnssrtk5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_gnssrtk5 PUBLIC MikroSDK.Driver)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_gnssrtk5 PUBLIC MikroSDK.GenericPointer)

