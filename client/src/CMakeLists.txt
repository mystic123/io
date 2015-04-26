SET (SOURCES
	main.cpp
	client.cpp
	)

SET (HEADERS
	client.h
	)

qt5_wrap_cpp(SOURCES ${HEADERS})

add_executable(client ${SOURCES})

target_link_libraries(client ${Qt5Widgets_LIBRARIES} ${Qt5Network_LIBRARIES} SharedLib)
