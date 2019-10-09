# cmake needs this line 要求的最低版本  
    cmake_minimum_required(VERSION 2.8)  
      
    # Define project name 定义工程名  
    project(example_project)  
      
    # Find OpenCV, you may need to set OpenCV_DIR variable  
    # to the absolute path to the directory containing OpenCVConfig.cmake file  
    # via the command line or GUI 自动查找库  
    find_package(OpenCV REQUIRED)  
      
    # Declare the executable target built from your sources 声明可执行目标文件及源文件  
    add_executable(cv cv.cpp) # 目标文件，源文件0,源文件1,...  
      
    # Link your application with OpenCV libraries 将目标文件与库链接  
    target_link_libraries(cv ${OpenCV_LIBS})   # 目标文件，库路径 

