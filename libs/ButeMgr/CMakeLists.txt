project(LIB_ButeMgr)

add_library(${PROJECT_NAME} STATIC
	arange.cpp
	avector.cpp
	butemgr.cpp
	stdafx.cpp)

add_definitions(-D_NOMFC)
if(MSVC)
	add_definitions(-D_SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS)	# VC14 deprecated stdext::hash_*
endif(MSVC)

include_directories(../CryptMgr
	../stdlith
	../lith
	../MFCStub)
