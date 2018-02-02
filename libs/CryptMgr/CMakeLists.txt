project(LIB_CryptMgr)

add_library(${PROJECT_NAME} STATIC
	blowfish.cpp
	cryptmgr.cpp)

if(LINUX)
    set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-fPIC")
endif(LINUX)
