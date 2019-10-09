cmake_minimum_required(VERSION 2.8)
project( l6 )

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( l6 main.cpp )

target_link_libraries( l6 ${OpenCV_LIBS} )
