set (HEADERS
   global.h
   user.h
   event.h
   serializationexception.h
)

set (QOBJSH
   user.h
   event.h
)

set (QOBJSS
   user.cpp
   event.cpp
)

set (SOURCES
   global.cpp
   user.cpp
   event.cpp
   serializationexception.cpp
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

qt5_wrap_cpp (QOBJSS ${QOBJSH})

add_library(SharedLib SHARED ${SOURCES} ${QOBJSS})
target_link_libraries(SharedLib ${Qt5Widgets_LIBRARIES})

target_include_directories (SharedLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
