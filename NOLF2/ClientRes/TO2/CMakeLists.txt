project(NOLF2_ClientRes)

set(exec_src main.cpp)

include_directories(../Shared
	../Shared/Lang/EN
	../../Shared/Lang/EN)

if(LINUX)
include_directories(../../../libs/DynRes)
list(APPEND exec_src ClientRes.rc.cpp)

add_custom_command(OUTPUT ClientRes.rc.cpp
    COMMAND  ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/DynRes/rc.parser.py ../../../Shared/Lang/EN ${CMAKE_CURRENT_SOURCE_DIR}/Lang/EN/ClientRes.rc)

endif(LINUX)

list(APPEND exec_src Lang/EN/ClientRes.rc)

add_library(${PROJECT_NAME} SHARED 
  ${exec_src})

set_target_properties(${PROJECT_NAME}
	PROPERTIES OUTPUT_NAME CRes)
if(LINUX)
target_link_libraries(${PROJECT_NAME} LIB_DynRes)
endif(LINUX)
