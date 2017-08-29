project(LIB_RegMgr)

if(WIN32)
add_library(${PROJECT_NAME} STATIC
	regmgr.cpp)
else(WIN32)
add_library(${PROJECT_NAME} STATIC
	linregmgr.cpp)
endif(WIN32)

include_directories(../lith)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS -std=c++11 ${CMAKE_CXX_FLAGS})
    set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-fpermissive -fPIC")
endif(CMAKE_COMPILER_IS_GNUCXX)

