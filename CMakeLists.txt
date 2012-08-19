project(HomeAutomationManager)


if(NOT DEFINED ProjectVersion)
	find_package(Git)
	if(EXISTS ${GIT_EXECUTABLE})
		execute_process(COMMAND "${GIT_EXECUTABLE}"	describe --tags
			RESULT_VARIABLE GIT_RESULT
			OUTPUT_VARIABLE ProjectVersion
			WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
		)
		string(STRIP "${ProjectVersion}" ProjectVersion)
		if(NOT GIT_RESULT EQUAL 0)
			message(FATAL_ERROR "Cannot get 'git describe' version!")
		endif()
	else()
		message(FATAL_ERROR "No Git executable or valid project version argument found.\nPlease pass a version to CMake e.g. cmake -DProjectVersion=1.0.0")
	endif()
endif()

string(REGEX MATCH "([0-9]+)\\.([0-9]+)\\.([0-9]+)-?([0-9]+)?-?([a-z0-9]+)?" ProjectVersion "${ProjectVersion}")
set(ProjectVersion_Major "${CMAKE_MATCH_1}")
set(ProjectVersion_Minor "${CMAKE_MATCH_2}")
set(ProjectVersion_Patch "${CMAKE_MATCH_3}")
set(ProjectVersion_Revision "${CMAKE_MATCH_5}")

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()


message(STATUS "Building Home Automation Manager ${ProjectVersion} in ${CMAKE_BUILD_TYPE} mode" )


# Treat link_directories as relative
cmake_policy(SET CMP0015 NEW)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-Wall")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
find_package(Qt4 4.8.0 COMPONENTS QtMain QtCore QtGui QtSql QtXml QtNetwork REQUIRED)
include(UseQt4)
enable_testing()

if(CMAKE_BUILD_TYPE MATCHES "^[Rr]elease$")
	add_definitions(-DQT_NO_DEBUG_OUTPUT)
else()
	message(WARNING	"Only run in debug mode if you are doing development!")
endif()

include_directories(.)
add_subdirectory("HomeAutomation")
add_subdirectory("Backend")
add_subdirectory("Frontend")
add_subdirectory("Tests")

set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/ReadMe.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Home Automation Manager")
set(CPACK_PACKAGE_EXECUTABLES "HomeAutomationFrontend" "Home Automation Frontend")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "MadeByAI Software\\\\HomeAutomation")

set(CPACK_PACKAGE_VENDOR "MadeByAI Software")
set(CPACK_PACKAGE_VERSION_MAJOR "${ProjectVersion_Major}")
set(CPACK_PACKAGE_VERSION_MINOR "${ProjectVersion_Minor}")
set(CPACK_PACKAGE_VERSION_PATCH "${ProjectVersion_Patch}")

set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")


if(WIN32 AND NOT UNIX)
	# There is a bug in NSI that does not handle full unix paths properly. Make
	# sure there is at least one set of four (4) backlasshes.
	set(CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/Frontend/Resources/Icons\\\\MainIcon.png")
	set(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\HomeAutomationFrontend.exe")
	set(CPACK_NSIS_DISPLAY_NAME "Home Automation Frontend")
	set(CPACK_NSIS_HELP_LINK "https://redmine.techtonium.com/projects/home-automation")
	set(CPACK_NSIS_URL_INFO_ABOUT "https://redmine.techtonium.com/projects/home-automation")
	set(CPACK_NSIS_CONTACT "madebyai@madebyai.com")
	set(CPACK_NSIS_MODIFY_PATH ON)
else()
endif()
set(CPACK_STRIP_FILES TRUE)
include(CPack)

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND AND NOT Skip_Doxygen)
	configure_file("${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in" "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile" @ONLY)
	add_custom_target(Documentation ALL
		"${DOXYGEN_EXECUTABLE}" "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
		WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
		COMMENT "Generating API documentation with Doxygen" VERBATIM
	)
endif()
