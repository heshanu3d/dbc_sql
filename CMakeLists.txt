cmake_minimum_required(VERSION 3.16)
project(my_dbc_sql)

set(CMAKE_C_FLAGS "-m32")
set(CMAKE_CXX_FLAGS "-m32")

add_executable(generate generate.cpp)
add_custom_target(generate_header
    COMMAND ./generate
    DEPENDS generate
)
file(GLOB generatefiles "header/*.cpp")
message(STATUS ${generatefiles})

add_executable(main main.cpp dbc.cpp ${generatefiles} progressbar.cpp)
target_include_directories(main PRIVATE header ${CMAKE_CURRENT_LIST_DIR})
add_dependencies(main generate_header)

add_custom_target(build_and_run_main
    COMMAND ./main
    DEPENDS main
)

# move generated files to header/