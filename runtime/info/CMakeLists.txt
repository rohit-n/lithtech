project(LIB_Info)

add_library(${PROJECT_NAME} STATIC
	src/outputredir.cpp
	src/sys/win32/outputredir_win32.cpp)

include_directories(src
	../../sdk/inc
	../kernel/src
	../shared/src)

set_target_properties(${PROJECT_NAME}
	PROPERTIES OUTPUT_NAME libltinfo)

if(CMAKE_COMPILER_IS_GNUCXX)
	set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-fpermissive")
endif(CMAKE_COMPILER_IS_GNUCXX)
