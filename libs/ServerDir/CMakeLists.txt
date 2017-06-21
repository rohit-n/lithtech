project(ServerDir)

add_library(${PROJECT_NAME} SHARED
	CServerDir_Titan.cpp
	stdafx.cpp)

include_directories(../../sdk/inc
	../WONAPI
	../../NOLF2/ClientRes/Shared)

target_link_libraries(${PROJECT_NAME}
	LIB_WONAPI)

if(CMAKE_COMPILER_IS_GNUCXX)
        set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-fpermissive -std=c++11")
endif(CMAKE_COMPILER_IS_GNUCXX)


