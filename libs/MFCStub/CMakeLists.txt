project(LIB_MFCStub)

add_library(${PROJECT_NAME} STATIC
	mfcs_point.cpp
	mfcs_rect.cpp
	mfcs_string.cpp)

include_directories(../stdlith)

if(CMAKE_COMPILER_IS_GNUCXX)
        set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-fpermissive -std=c++11")
endif(CMAKE_COMPILER_IS_GNUCXX)
