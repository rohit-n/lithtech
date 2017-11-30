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
if(CMAKE_COMPILER_IS_GNUCXX)
    set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-fPIC")
endif(CMAKE_COMPILER_IS_GNUCXX)

include_directories(../CryptMgr
	../stdlith
	../lith
	../MFCStub)
