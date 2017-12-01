project(ServerDir)

add_library(${PROJECT_NAME} SHARED
	CServerDir_Titan.cpp
	stdafx.cpp)

include_directories(../../sdk/inc
	../WONAPI
	../../NOLF2/ClientRes/Shared)
set(libs LIB_WONAPI)

if(LINUX)
    set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-fpermissive -fPIC")
	set(libs pthread ${libs})
endif(LINUX)

target_link_libraries(${PROJECT_NAME}
	${libs})

