project(NOLF2_ServerRes)

add_library(${PROJECT_NAME} SHARED
	MAIN.CPP
	ServerRes.rc)

set_target_properties(${PROJECT_NAME}
	PROPERTIES OUTPUT_NAME SRes)
