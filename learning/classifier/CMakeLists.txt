cmake_minimum_required(VERSION 2.8)
project( Opencv_test )

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -march=native")
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -march=native -O3 -pthread" )

add_executable( Opencv_test  main.cpp)
#add_executable(Opencv_test test.cpp)
#add_executable(Opencv_test RGBvalue.cpp)
#add_executable(Opencv_test v02_Find_center.cpp)
#add_executable(Opencv_test v03_Cameracalib.cpp)

find_package( OpenCV REQUIRED )

if(OpenCV_FOUND)
    message(STATUS "OpenCV library status:")
    message(STATUS "    version: ${OpenCV_VERSION}")
    message(STATUS "    libraries: ${OpenCV_LIBS}")
    message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
    include_directories(${OPENCV_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
endif()




