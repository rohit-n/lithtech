project(LIB_Lith)

add_library(${PROJECT_NAME} STATIC
	basehash.cpp
	baselist.cpp
	baselistcounter.cpp
	dprintf.cpp
	lith.cpp
	lithbaselist.cpp
	lithchunkallocator.cpp
	lithsimpary.cpp
	lithsimparystat.cpp
	virtlist.cpp)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS -std=c++11 ${CMAKE_CXX_FLAGS})
	set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-fpermissive -fPIC")
endif(CMAKE_COMPILER_IS_GNUCXX)
