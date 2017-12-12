project(Test_CShell)
cmake_minimum_required(VERSION 3.1)

include(FindPkgConfig)

pkg_check_modules(SDL2 REQUIRED sdl2)

set(exec_src
    src/shell.cpp)

set(libs
	${SDL2_LIBRARIES}
	LIB_Lith)

include_directories(../../sdk/inc
	${SDL2_INCLUDE_DIRS}
	../../libs/MFCStub
	../../libs/stdlith
	../../libs/ButeMgr
	../../libs/CryptMgr
	../../libs/lith
	../../libs/RegMgr
	../../libs/LTGUIMgr
	../../libs/ServerDir
)

add_library(${PROJECT_NAME} SHARED ${exec_src})

set_target_properties(${PROJECT_NAME}
        PROPERTIES OUTPUT_NAME CShell)

target_link_libraries(${PROJECT_NAME} ${libs})

