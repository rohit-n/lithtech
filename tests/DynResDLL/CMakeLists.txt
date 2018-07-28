project(Test_DynResDLL)

include_directories(./
    ../../libs/DynRes)

set(exec_src
    src/resources.h
    myres.rc.cpp
    src/main.cpp)

set(RC_FILES
    src/myres.rc
    src/resources.h)

add_custom_command(OUTPUT myres.rc.cpp
    COMMAND  ../../../libs/DynRes/rc.parser.py ../../../tests/DynResDLL/src/myres.rc
    DEPENDS ${RC_FILES})


add_library(${PROJECT_NAME} SHARED ${exec_src})

set_target_properties(${PROJECT_NAME}
        PROPERTIES OUTPUT_NAME testCRes)


