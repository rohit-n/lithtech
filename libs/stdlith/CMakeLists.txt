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

target_link_libraries(${PROJECT_NAME}
	LIB_ZLib)
