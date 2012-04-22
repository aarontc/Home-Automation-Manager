set(
	Core_Sources

	HarmanKardonAVR645Receiver.cpp
)

set(
	Core_Headers

	#IReceiver.h
	HarmanKardonAVR645Receiver.h
)

set(
	Core_Interfaces

)

set(
	Core_Forms

)

#include_directories(${CMAKE_CURRENT_BINARY_DIR})

qt4_wrap_cpp(Core_Sources ${Core_Headers})
qt4_wrap_ui(Core_Form_Headers ${Core_Forms})

add_library(
	HomeAutomationManager
	STATIC

	${Core_Sources}
	${Core_Form_Headers}
	${Core_Interfaces}
)
