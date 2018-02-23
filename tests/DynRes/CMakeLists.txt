project(Test_DynRes)

set(exec_src
    testReg.cpp)

set(libs
    Test_DynResDLL
	LIB_DynRes
    dl)

include_directories(../../libs/DynRes
    ../DynResDLL/src)

add_executable(${PROJECT_NAME} ${exec_src})
set_target_properties(${PROJECT_NAME}
	PROPERTIES OUTPUT_NAME testDynRes)
target_link_libraries(${PROJECT_NAME} ${libs})