cmake_minimum_required(VERSION 3.15)
project(TcppNet)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

file(GLOB SOURCE_FILES "${SOURCE_DIR}/*.c*")
file(GLOB INCLUDE_FILES "${INCLUDE_DIR}/*.h*")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})
target_sources(${PROJECT_NAME} PUBLIC ${INCLUDE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE /usr/include)
target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
