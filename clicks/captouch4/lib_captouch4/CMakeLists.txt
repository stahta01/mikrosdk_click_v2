cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_captouch4 LANGUAGES MikroC)
else()
    project(lib_captouch4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_captouch4 STATIC
        src/captouch4.c
        include/captouch4.h
)
add_library(Click.CapTouch4  ALIAS lib_captouch4)



target_include_directories(lib_captouch4 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_captouch4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_captouch4 PUBLIC MikroSDK.Driver)

