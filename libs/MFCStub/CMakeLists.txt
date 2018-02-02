project(LIB_MFCStub)

add_library(${PROJECT_NAME} STATIC
	mfcs_point.cpp
	mfcs_rect.cpp
	mfcs_string.cpp)

include_directories(../stdlith)

if(LINUX)
    set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-fpermissive -fPIC")
endif(LINUX)
