project(LIB_MFCStub)

add_library(${PROJECT_NAME} STATIC
	mfcs_point.cpp
	mfcs_rect.cpp
	mfcs_string.cpp)

include_directories(../stdlith)
