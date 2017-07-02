project(LIB_LTMem)

add_library(${PROJECT_NAME} STATIC
	ltmem.cpp
	ltmemdebug.cpp
	ltmemheap.cpp
	ltmemstats.cpp
	ltmemtrack.cpp
	stdafx.cpp)

include_directories(../../sdk/inc
	../../runtime/shared/src
	../../runtime/kernel/src
	../stdlith
	../../runtime/kernel/mem/src
	/usr/inlcude/SDL2)

if(CMAKE_COMPILER_IS_GNUCXX)
	set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-fpermissive -fPIC -std=c++11")
endif(CMAKE_COMPILER_IS_GNUCXX)
