project(DLL_LTMsg)

add_library(${PROJECT_NAME} SHARED
	Lang/EN/ltmsg.rc
	init.cpp)

set_target_properties(${PROJECT_NAME}
	PROPERTIES OUTPUT_NAME LTMsg)
