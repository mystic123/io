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

add_library(SharedLib ${SOURCES} ${QOBJSS})
qt5_use_modules(SharedLib Network)