set (SOURCES
	dbcontroller.cpp
	connectionthread.cpp
	server.cpp
	fbsync.cpp
	main.cpp
)

set (HEADERS
	dbcontroller.h
	connectionthread.h
	fbsync.h
	server.h
)

#qt5_add_resources (RESOURCES_RCC ${RESOURCES})
#qt5_wrap_cpp (SOURCES ${HEADERS})
	
add_executable(BeviamoServer ${SOURCES})# ${RESOURCES_RCC})

qt5_use_modules(BeviamoServer Sql Network)

target_link_libraries(BeviamoServer SharedLib)
