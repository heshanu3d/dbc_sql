cmake_minimum_required(VERSION 3.16)
project(my_dbc_sql)

add_executable(g generate.cpp)
add_custom_target(generate_header
    COMMAND ./g
    DEPENDS g
)
file(GLOB generatefiles "header/*.cpp")
message(STATUS ${generatefiles})

add_executable(m main.cpp dbc.cpp ${generatefiles})
target_include_directories(m PRIVATE header ${CMAKE_CURRENT_LIST_DIR})
add_dependencies(m generate_header)

add_custom_target(test_main
    COMMAND ./m
    DEPENDS m
)

# move generated files to header/