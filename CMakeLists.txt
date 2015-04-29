cmake_minimum_required (VERSION 2.8.11)

project(Beviamo)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
#tylko dla maca, bez tego jakies warningi sa
   cmake_policy(SET CMP0042 NEW)
   set(CMAKE_PREFIX_PATH "/Users/mystic/Qt/5.4/clang_64/")
ELSE(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
   set(CMAKE_PREFIX_PATH "/opt/Qt/5.4/gcc/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

set(CMAKE_CXX_FLAGS "-Wall -std=c++11")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -ggdb -W -fsanitize=address")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3")
set(EXECUTABLE_OUTPUT_PATH "${Beviamo_SOURCE_DIR}/build/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${Beviamo_BINARY_DIR}/bin)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

# Widgets finds its own dependencies (QtGui and QtCore).
find_package(Qt5Widgets)
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Quick)
find_package(Qt5Sql)
find_package(Qt5Network)

include_directories(${Beviamo_SOURCE_DIR}/shared)

add_subdirectory(server)
add_subdirectory(shared)
add_subdirectory(beviamo)