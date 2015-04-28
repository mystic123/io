cmake_minimum_required (VERSION 2.8.11)

qt5_add_resources(BeviamoRsrc qml.qrc)

add_executable(Beviamo
	main.cpp
	client.cpp
	${BeviamoRsrc}
	)

qt5_use_modules(Beviamo Widgets Gui Quick)

target_link_libraries(Beviamo SharedLib)