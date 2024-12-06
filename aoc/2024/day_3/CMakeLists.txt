cmake_minimum_required(VERSION 3.30)
project(day_3 C)

set(CMAKE_C_STANDARD 23)

add_executable(day_3 main.c)

# Include the PCRE directories
include_directories(${CMAKE_INCLUDE_PATH})
link_directories(${CMAKE_LIBRARY_PATH})

# Link against PCRE library
target_link_libraries(day_3 pcre)