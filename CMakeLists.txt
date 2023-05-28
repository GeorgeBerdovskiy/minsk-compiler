cmake_minimum_required(VERSION 3.10)
project(Minsk)

set(CMAKE_CXX_STANDARD 11)

# Add source files indiscriminately
file(GLOB SOURCE_FILES "source/*.cpp")
file(GLOB HEADER_FILES "source/*.h")

add_executable(Minsk ${SOURCE_FILES} ${HEADER_FILES})

