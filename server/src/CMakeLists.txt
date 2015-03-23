set (SOURCES
	connectionthread.cpp
	server.cpp
	main.cpp
)

set (HEADERS
	connectionthread.h
	server.h
)

#qt5_add_resources (RESOURCES_RCC ${RESOURCES})
qt5_wrap_cpp (SOURCES ${HEADERS})
	
add_executable(BeviamoServer ${SOURCES} ${RESOURCES_RCC})

  # The Qt5Widgets_LIBRARIES variable also includes QtGui and QtCore
target_link_libraries(BeviamoServer ${Qt5Widgets_LIBRARIES} ${Qt5Network_LIBRARIES})
