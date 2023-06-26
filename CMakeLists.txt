cmake_minimum_required(VERSION 3.10)
project(Minsk)

set(CMAKE_CXX_STANDARD 11)

# Add source files indiscriminately
file(GLOB ENTRYPOINT "source/Program.cpp")
file(GLOB SOURCE_FILES "source/syntax/*.cpp")
file(GLOB HEADER_FILES "source/syntax/*.h")

add_executable(Minsk ${ENTRYPOINT} ${SOURCE_FILES} ${HEADER_FILES})
