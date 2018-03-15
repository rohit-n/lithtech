project(Test_DynResDLL)

include_directories(./
    ../../libs/DynRes)

set(exec_src
    src/resources.h
    myres.rc.cpp
    src/main.cpp)

add_custom_command(OUTPUT myres.rc.cpp
    COMMAND  ../../../libs/DynRes/rc.parser.py ../../../tests/DynResDLL/src/myres.rc)


add_library(${PROJECT_NAME} SHARED ${exec_src})

set_target_properties(${PROJECT_NAME}
        PROPERTIES OUTPUT_NAME testCRes)


