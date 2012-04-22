set(
	Frontend_Sources

	Main.cpp
	MainWindow.cpp
)

set(
	Frontend_Headers

	MainWindow.h
)

set(
	Frontend_Forms

	MainWindow.ui
)

qt4_wrap_cpp(Frontend_Sources ${Frontend_Headers})
qt4_wrap_ui(Frontend_Sources ${Frontend_Forms})


if(MINGW)
	# resource compilation for MinGW
	add_custom_command(
		OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/Resources.o"
		COMMAND windres.exe -I"${CMAKE_CURRENT_SOURCE_DIR}" -i"${CMAKE_CURRENT_SOURCE_DIR}/Resources.rc" -o "${CMAKE_CURRENT_BINARY_DIR}/Resources.o"
	)
	list(APPEND Frontend_Sources "${CMAKE_CURRENT_BINARY_DIR}/Resources.o")
endif()


# Needed for generated UI header files
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(
	HomeAutomationManagerFrontend
	WIN32
	${Frontend_Sources}
)

target_link_libraries(
	HomeAutomationManagerFrontend

	HomeAutomationManager
	qextserialport-1.2
	xosd

	${QT_LIBRARIES}
)

install(TARGETS HomeAutomationManagerFrontend RUNTIME DESTINATION bin)

if(WIN32)
	install(FILES
		"${CUTEWRAPPERS_LIB_DIR}/CuteWrappers.dll"
		"${QT_BINARY_DIR}/libgcc_s_dw2-1.dll"
		"${QT_BINARY_DIR}/mingwm10.dll"
		DESTINATION bin
	)

	if(CMAKE_BUILD_TYPE MATCHES Release)
		install(FILES
			"${QT_BINARY_DIR}/QtCore${QT_VERSION_MAJOR}.dll"
			"${QT_BINARY_DIR}/QtGui${QT_VERSION_MAJOR}.dll"
			DESTINATION bin
		)
	else()
		install(FILES
			"${QT_BINARY_DIR}/QtCored${QT_VERSION_MAJOR}.dll"
			"${QT_BINARY_DIR}/QtGuid${QT_VERSION_MAJOR}.dll"
			DESTINATION bin
		)
	endif()
endif()
