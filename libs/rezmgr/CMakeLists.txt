project(LIB_RezMgr)

add_library(${PROJECT_NAME} STATIC
	rezfile.cpp
	rezhash.cpp
	rezmgr.cpp
	rezutils.cpp)

include_directories(../../sdk/inc
	../lith)

if(CMAKE_COMPILER_IS_GNUCXX)
	set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-fpermissive -fPIC")
endif(CMAKE_COMPILER_IS_GNUCXX)
