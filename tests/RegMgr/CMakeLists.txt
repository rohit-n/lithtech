project(Test_RegMgr)

set(exec_src
    testReg.cpp)

set(libs
	LIB_RegMgr)

include_directories(../../libs/RegMgr
    ../../libs/lith)

add_executable(${PROJECT_NAME} ${exec_src})
set_target_properties(${PROJECT_NAME}
	PROPERTIES OUTPUT_NAME testRegMgr)
target_link_libraries(${PROJECT_NAME} ${libs})


if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS -std=c++11 ${CMAKE_CXX_FLAGS})
endif(CMAKE_COMPILER_IS_GNUCXX)
