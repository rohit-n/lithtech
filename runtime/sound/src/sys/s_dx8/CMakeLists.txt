project(DLL_SndDrvDX8)

if(CMAKE_CL_64)
	link_directories("C:\\Program Files (x86)\\Microsoft DirectX SDK (August 2007)\\Lib\\x64")
else(CMAKE_CL_64)
	link_directories("C:\\Program Files (x86)\\Microsoft DirectX SDK (August 2007)\\Lib\\x86")
endif(CMAKE_CL_64)

add_library(${PROJECT_NAME} SHARED
	../../../../kernel/src/sys/win/counter.cpp
	parsewavefile.cpp
	s_dx8.cpp
	StdAfx.cpp)

include_directories(../..
	../../../../../sdk/inc 
	../../../../kernel/src
	../../../../shared/src/sys/win)

set_target_properties(${PROJECT_NAME}
	PROPERTIES OUTPUT_NAME SndDrv)

target_link_libraries(${PROJECT_NAME}
	dxguid
	winmm
	msacm32
	LIB_LTMem)

if(NOT CMAKE_CL_64)
	target_link_libraries(${PROJECT_NAME} eaxguid)
endif(NOT CMAKE_CL_64)
