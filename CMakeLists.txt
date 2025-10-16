cmake_minimum_required(VERSION 3.15)
project(ds18b20 LANGUAGES C)

set(DS18B20_VERSION_MAJOR 1)
set(DS18B20_VERSION_MINOR 0)
set(DS18B20_VERSION_PATCH 0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Os
    )
endif()

add_library(ds18b20 STATIC
    src/ds18b20.c
)

target_include_directories(ds18b20 PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if(CMAKE_C_COMPILER_ID MATCHES "GNU")
    target_compile_options(ds18b20 PRIVATE
        -ffunction-sections
        -fdata-sections
    )
    
    target_link_options(ds18b20 PRIVATE
        -Wl,--gc-sections
    )
endif()

install(TARGETS ds18b20
    DESTINATION lib
)

install(FILES include/ds18b20.h
    DESTINATION include
)

message(STATUS "DS18B20 library configured successfully")
message(STATUS "Data structure will be placed at address: ${DS18B20_DATA_ADDRESS}")