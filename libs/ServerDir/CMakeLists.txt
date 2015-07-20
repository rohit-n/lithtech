project(ServerDir)

add_library(${PROJECT_NAME} SHARED
	CServerDir_Titan.cpp
	stdafx.cpp)

include_directories(../../sdk/inc
	../WONAPI
	../../NOLF2/ClientRes/Shared)

target_link_libraries(${PROJECT_NAME}
	LIB_WONAPI)
