cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_grideye2 LANGUAGES MikroC)
else()
    project(lib_grideye2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_grideye2 STATIC
        src/grideye2.c
        include/grideye2.h
)
add_library(Click.GridEYE2  ALIAS lib_grideye2)



target_include_directories(lib_grideye2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_grideye2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_grideye2 PUBLIC MikroSDK.Driver)

