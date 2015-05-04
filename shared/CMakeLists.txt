set (HEADERS
   global.h
   user.h
   event.h
   fbsync.h
)

set (SOURCES
   global.cpp
   user.cpp
   event.cpp
   fbsync.cpp
)

add_library(SharedLib ${SOURCES})
qt5_use_modules(SharedLib Network)