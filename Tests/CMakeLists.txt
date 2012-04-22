set(
	TestLib_Sources

	MockQSettings.cpp
)


set(
	TestLib_Headers

	MockQSettings.h
)

# qt4_wrap_cpp(
# 	TestLib_Sources
# 	${TestLib_Headers}
# )

#add_library(
#	TestLib
#	STATIC
#
#	${TestLib_Sources}
#)

set(
	test_libraries

	BackingStore
	Core

	CuteWrappers

	TestLib

	${QT_QTTEST_LIBRARY}
	${QT_LIBRARIES}
)

# Needed for generated MOC files
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# set(BackingStoreTest_Sources BackingStoreTest.cpp)
# qt4_automoc(${BackingStoreTest_Sources})
# add_executable(BackingStoreTest ${BackingStoreTest_Sources})
# target_link_libraries(BackingStoreTest ${test_libraries})
# add_test(NAME BackingStoreTest COMMAND BackingStoreTest)
#
#
# set(KeyValueNoteStorageDriverTest_Sources KeyValueNoteStorageDriverTest.cpp)
# qt4_automoc(${KeyValueNoteStorageDriverTest_Sources})
# add_executable(KeyValueNoteStorageDriverTest ${KeyValueNoteStorageDriverTest_Sources})
# target_link_libraries(KeyValueNoteStorageDriverTest ${test_libraries})
# add_test(NAME KeyValueNoteStorageDriverTest COMMAND KeyValueNoteStorageDriverTest)
