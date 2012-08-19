set(
	Backend_Sources

	Main.cpp
	TCPServer.cpp
	TCPServerThread.cpp
)

set(
	Backend_Headers

	TCPServer.h
	TCPServerThread.h
)

if(MINGW)
	# resource compilation for MinGW
	add_custom_command(
		OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/Resources.o"
		COMMAND windres.exe -I"${CMAKE_CURRENT_SOURCE_DIR}" -i"${CMAKE_CURRENT_SOURCE_DIR}/Resources.rc" -o "${CMAKE_CURRENT_BINARY_DIR}/Resources.o"
	)
	list(APPEND Backend_Sources "${CMAKE_CURRENT_BINARY_DIR}/Resources.o")
endif()


qt4_wrap_cpp(Backend_Sources ${Backend_Headers})


add_executable(
	HomeAutomationBackend
	WIN32
	${Backend_Sources}
)

target_link_libraries(
	HomeAutomationBackend

	HomeAutomation

	${QT_LIBRARIES}
)

install(TARGETS HomeAutomationBackend RUNTIME DESTINATION bin)

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
