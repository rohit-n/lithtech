project(LIB_RegMgr)

if(WIN32)
add_library(${PROJECT_NAME} STATIC
	regmgr.cpp)
else(WIN32)
add_library(${PROJECT_NAME} STATIC
	linregmgr.cpp)
endif(WIN32)

include_directories(../lith)
