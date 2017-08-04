project(LIB_MFCStub)

add_library(${PROJECT_NAME} STATIC
	mfcs_point.cpp
	mfcs_rect.cpp
	mfcs_string.cpp)

include_directories(../stdlith)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS -std=c++11 ${CMAKE_CXX_FLAGS})
    set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-fpermissive")
endif(CMAKE_COMPILER_IS_GNUCXX)
