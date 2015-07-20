project(LIB_ILTSound)

include_directories(src
	../../sdk/inc)

add_library(${PROJECT_NAME} STATIC
	src/iltsound.cpp)

if(CMAKE_COMPILER_IS_GNUCXX)
	set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-fpermissive")
endif(CMAKE_COMPILER_IS_GNUCXX)
