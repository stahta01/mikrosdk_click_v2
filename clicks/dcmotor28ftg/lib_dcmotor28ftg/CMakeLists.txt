cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dcmotor28ftg LANGUAGES MikroC)
else()
    project(lib_dcmotor28ftg LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dcmotor28ftg STATIC
        src/dcmotor28ftg.c
        include/dcmotor28ftg.h
)
add_library(Click.DCMotor28FTG  ALIAS lib_dcmotor28ftg)



target_include_directories(lib_dcmotor28ftg PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dcmotor28ftg PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dcmotor28ftg PUBLIC MikroSDK.Driver)

