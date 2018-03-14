project(Test_DynResDLL)

set(exec_src
    myres.rc.cpp)

set(libs LIB_DynRes)

add_custom_command(OUTPUT myres.rc.cpp
    COMMAND  ../../../libs/DynRes/rc.parser.py ../../../tests/DynResDLL/src/myres.rc)

include_directories(./
    ../../libs/DynRes)

add_library(${PROJECT_NAME} SHARED ${exec_src})

set_target_properties(${PROJECT_NAME}
        PROPERTIES OUTPUT_NAME testCRes)

target_link_libraries(${PROJECT_NAME} ${libs})

