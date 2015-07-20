project(NOLF2_ClientRes)

add_library(${PROJECT_NAME} SHARED
	main.cpp
	Lang/EN/ClientRes.rc)

include_directories(../Shared
	../Shared/Lang/EN
	../../Shared/Lang/EN)

set_target_properties(${PROJECT_NAME}
	PROPERTIES OUTPUT_NAME CRes)
