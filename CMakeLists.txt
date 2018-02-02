cmake_minimum_required(VERSION 3.6)
project(embedded_mysql)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
add_executable(embedded_mysql ${SOURCE_FILES})

find_package( ZLIB REQUIRED )
if ( ZLIB_FOUND )
    include_directories( ${ZLIB_INCLUDE_DIRS} )
    target_link_libraries( embedded_mysql ${ZLIB_LIBRARIES} )
endif( ZLIB_FOUND )

execute_process(COMMAND mysql_config --include
        OUTPUT_VARIABLE MYSQL_INCLUDE)
execute_process(COMMAND mysql_config --libmysqld-libs
        OUTPUT_VARIABLE MYSQL_LIBS)

string(STRIP ${MYSQL_LIBS} MYSQL_LIBS)

target_compile_options(embedded_mysql PUBLIC ${MYSQL_INCLUDE})
target_link_libraries(embedded_mysql ${MYSQL_LIBS})

