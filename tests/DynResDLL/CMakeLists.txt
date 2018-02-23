project(Test_DynResDLL)

set(exec_src
    src/main.cpp)


add_library(${PROJECT_NAME} SHARED ${exec_src})

set_target_properties(${PROJECT_NAME}
        PROPERTIES OUTPUT_NAME testCRes)

target_link_libraries(${PROJECT_NAME} ${libs})

