add_library(fort STATIC libfort/lib/fort.c)
target_include_directories(fort PUBLIC libfort/lib)

if(TARGET_GROUP STREQUAL test)
    add_library(unity STATIC unity/src/unity.c)
    target_include_directories(unity PUBLIC unity/src)
endif()