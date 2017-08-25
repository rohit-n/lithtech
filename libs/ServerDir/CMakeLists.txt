project(ServerDir)

add_library(${PROJECT_NAME} SHARED
	CServerDir_Titan.cpp
	stdafx.cpp)

include_directories(../../sdk/inc
	../WONAPI
	../../NOLF2/ClientRes/Shared)
set(libs LIB_WONAPI)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS -std=c++11 ${CMAKE_CXX_FLAGS})
	set(libs pthread ${libs})
    set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-fpermissive")
endif(CMAKE_COMPILER_IS_GNUCXX)

target_link_libraries(${PROJECT_NAME}
	${libs})

