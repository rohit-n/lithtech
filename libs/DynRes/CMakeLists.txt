project(LIB_DynRes)

add_library(${PROJECT_NAME} STATIC
    dynres.cpp)

if(LINUX)
    set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-fPIC")
endif(LINUX)
