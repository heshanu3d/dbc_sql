cmake_minimum_required(VERSION 3.16)
project(my_dbc_sql)

set(CMAKE_CXX_STANDARD 17)
message(CMAKE_SYSTEM_NAME ": ${CMAKE_SYSTEM_NAME}")
message(CMAKE_CXX_COMPILER_ID ": ${CMAKE_CXX_COMPILER_ID}")
if (CMAKE_SYSTEM_NAME MATCHES "Linux" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_C_FLAGS "-m32")
    set(CMAKE_CXX_FLAGS "-m32")
    add_definitions(-D_UNIX_PACKED_)
endif()

add_executable(generate generate.cpp)
add_custom_target(generate_header
    COMMAND ./generate
    DEPENDS generate
)
# file(GLOB generatefiles "header/*.cpp")
file(GLOB generatefiles CONFIGURE_DEPENDS "header/*.cpp")
message(STATUS ${generatefiles})

add_executable(main main.cpp dbc.cpp ${generatefiles} progressbar.cpp)
target_include_directories(main PRIVATE header ${CMAKE_CURRENT_LIST_DIR})
add_dependencies(main generate_header)

add_custom_target(build_and_run_main
    COMMAND ./main
    DEPENDS main
)

# move generated files to header/