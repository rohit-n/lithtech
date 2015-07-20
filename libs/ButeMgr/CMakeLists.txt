project(LIB_ButeMgr)

add_library(${PROJECT_NAME} STATIC
	arange.cpp
	avector.cpp
	butemgr.cpp
	stdafx.cpp)

add_definitions(-D_NOMFC)

include_directories(../cryptmgr
	../stdlith
	../lith
	../MFCStub)
