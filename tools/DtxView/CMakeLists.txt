project(TOOLS_DtxView)

add_definitions(-DDIRECTEDITOR_BUILD -DSTDLITH_MFC -DBDEFS_MFC -DPRE_FLOAT -DPREPROCESSOR_BUILD -DNO_PRAGMA_LIBS -DLT15_COMPAT -D_AFXDLL -D_WIN32_WINNT=0x500)
link_directories("${CMAKE_CURRENT_SOURCE_DIR}/../shared/world/")

add_executable(${PROJECT_NAME} WIN32
	AboutDlg.cpp
	../shared/engine/bdefs.cpp
	../shared/engine/dtxmgr.cpp
	DtxView.cpp
	DtxViewDoc.cpp
	DtxViewView.cpp
	../shared/engine/genltstream.cpp
	MainFrm.cpp
	../shared/engine/pixelformat.cpp
	../shared/world/s3tc_compress.cpp
	stdafx.cpp
	../shared/engine/streamsim.cpp
	TextureProp.cpp)

set_target_properties(${PROJECT_NAME}
	PROPERTIES OUTPUT_NAME DtxView)

include_directories(../shared/engine
	../../libs/stdlith
	../../sdk/inc
	../PreProcessor
	../shared/world
	../dedit/misc)

target_link_libraries(${PROJECT_NAME}
	LIB_StdLith
	s3tc)

if(MSVC)
	set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/SAFESEH:NO /NODEFAULTLIB:libc.lib")	# needed for s3tc.lib :/
endif(MSVC)
