project(TOOLS_LithRez)

add_definitions(-D_CONSOLE -DREZMGRFULL)

add_executable(${PROJECT_NAME} WIN32
	lithrez.cpp)

set_target_properties(${PROJECT_NAME}
	PROPERTIES OUTPUT_NAME LithRez)

include_directories(../../libs/lith
	../../libs/rezmgr)

target_link_libraries(${PROJECT_NAME}
	LIB_Lith
	LIB_RezMgr)

if(MSVC)
	set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")	# Need Console subsystem for console apps
endif(MSVC)
