project(Test_RegMgr)

set(exec_src
    testReg.cpp)

set(libs
	LIB_RegMgr)

include_directories(${CMAKE_SOURCE_DIR}/libs/RegMgr
    ${CMAKE_SOURCE_DIR}/libs/lith
    ${CMAKE_SOURCE_DIR}/rapidjson/include)

add_executable(${PROJECT_NAME} ${exec_src})
set_target_properties(${PROJECT_NAME}
	PROPERTIES OUTPUT_NAME testRegMgr)
target_link_libraries(${PROJECT_NAME} ${libs})

# add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ../../OUT/testRegMgr)
