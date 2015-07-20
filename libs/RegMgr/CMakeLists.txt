project(LIB_RegMgr)

add_library(${PROJECT_NAME} STATIC
	regmgr.cpp)

include_directories(../lith)
