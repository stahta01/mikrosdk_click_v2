cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_ryb080i LANGUAGES MikroC)
else()
    project(example_ryb080i LANGUAGES C ASM)
endif()

include(mikroeUtils)

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_ryb080i
        example/main.c
    
)


############################ example_ryb080i GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_ryb080i PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_ryb080i PUBLIC MikroSDK.Board)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(example_ryb080i PUBLIC MikroSDK.GenericPointer)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_ryb080i PUBLIC MikroSDK.Log)
add_subdirectory(lib_ryb080i)
target_link_libraries(example_ryb080i PUBLIC Click.RYB080I)
############################ example_ryb080i GENERATED CODE END ###########################

if(COMPILER_REVISION)
    if(${COMPILER_REVISION} VERSION_GREATER_EQUAL "1.0")
        if(${TOOLCHAIN_LANGUAGE} STREQUAL "GNU")
            if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/.meproject)
                fetch_startup_name(${CMAKE_CURRENT_SOURCE_DIR}/.meproject startupName)
                if(startupName)
                    add_startup_all_targets(. ${CMAKE_CURRENT_SOURCE_DIR} ${startupName})
                endif()
                fetch_linker_name(${CMAKE_CURRENT_SOURCE_DIR}/.meproject linkerName)
                if(linkerName)
                    add_ld_all_targets(. ${CMAKE_CURRENT_SOURCE_DIR} ${linkerName})
                endif()
            endif()
        endif()
    endif()
endif()
