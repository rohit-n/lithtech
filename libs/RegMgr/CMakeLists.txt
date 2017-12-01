project(LIB_RegMgr)

if(WIN32)
add_library(${PROJECT_NAME} STATIC
	regmgr.cpp)
else(WIN32)
add_library(${PROJECT_NAME} STATIC
	linregmgr.cpp)
endif(WIN32)

include_directories(../lith
    ../../cppcodec)

if(LINUX)
    set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-fpermissive -fPIC")
endif(LINUX)

