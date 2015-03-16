cmake_minimum_required (VERSION 2.8.11)

project (BeviamoServer)

set(CMAKE_PREFIX_PATH "/Users/mystic/Qt/5.4/clang_64/")

#set(CMAKE_VERBOSE_MAKEFILE 1)
# Tell CMake to run moc when necessary:
#	set(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}")

# Widgets finds its own dependencies (QtGui and QtCore).
find_package(Qt5 COMPONENTS Widgets Core Network REQUIRED)

# The Qt5Widgets_INCLUDES also includes the include directories for
# dependencies QtCore and QtGui
include_directories(${Qt5Widgets_INCLUDES})

# We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
add_definitions(${Qt5Widgets_DEFINITIONS})

# Executables fail to build with Qt 5 in the default configuration
# without -fPIE. We add that here.
set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} -Wall -std=c++11")

add_subdirectory(src)
