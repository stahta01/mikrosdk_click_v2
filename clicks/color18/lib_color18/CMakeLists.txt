cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_color18 LANGUAGES MikroC)
else()
    project(lib_color18 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_color18 STATIC
        src/color18.c
        include/color18.h
)
add_library(Click.Color18  ALIAS lib_color18)



target_include_directories(lib_color18 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_color18 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_color18 PUBLIC MikroSDK.Driver)

