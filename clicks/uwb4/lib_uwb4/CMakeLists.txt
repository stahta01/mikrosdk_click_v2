cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_uwb4 LANGUAGES MikroC)
else()
    project(lib_uwb4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_uwb4 STATIC
        src/uwb4.c
        include/uwb4.h
)
add_library(Click.UWB4  ALIAS lib_uwb4)



target_include_directories(lib_uwb4 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_uwb4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_uwb4 PUBLIC MikroSDK.Driver)

