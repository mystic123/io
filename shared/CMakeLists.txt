set (HEADERS
   global.h
   user.h
   event.h
   serializationexception.h
)

set (SOURCES
   user.cpp
   event.cpp
   serializationexception.cpp
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(SharedLib SHARED ${SOURCES} ${HEADERS})
target_link_libraries(SharedLib ${Qt5Widgets_LIBRARIES})

target_include_directories (SharedLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
