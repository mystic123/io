set (HEADERS
   global.h
   user.h
   event.h
   comment.h
)

set (SOURCES
   global.cpp
   user.cpp
   event.cpp
   comment.cpp
)

add_library(SharedLib ${SOURCES})
qt5_use_modules(SharedLib Network)
