set (SOURCES
	main.cpp
	../src/dbcontroller.cpp
	../src/fbsync.cpp
	)

set (HEADERS
	)

include_directories(${Beviamo_SOURCE_DIR}/server/src)

#qt5_add_resources (RESOURCES_RCC ${RESOURCES})
#qt5_wrap_cpp (SOURCES ${HEADERS})

add_executable(test ${SOURCES})# ${RESOURCES_RCC})

qt5_use_modules(test Sql Network)

target_link_libraries(test SharedLib)
