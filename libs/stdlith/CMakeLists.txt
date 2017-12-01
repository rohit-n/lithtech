project(LIB_StdLith)

add_library(${PROJECT_NAME} STATIC
	abstractio.cpp
	dynarray.cpp
	fileio.cpp
	goodlinklist.cpp
	helpers.cpp
	l_allocator.cpp
	linklist.cpp
	lithexception.cpp
	memory.cpp
	memoryio.cpp
	stringholder.cpp
	struct_bank.cpp
	zfstream.cpp)

include_directories(../zlib)
if(LINUX)
    set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-fPIC")
endif(LINUX)

target_link_libraries(${PROJECT_NAME}
	LIB_ZLib)
