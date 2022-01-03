cmake_minimum_required(VERSION 3.0.0)
project(smartFitness VERSION 0.1.0)



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})   
include(CPack)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


#set the OpenCV variable to the given path
set (OpenCV_DIR /home/bento/buildroot/buildroot-2021.02.5/output/host/arm-buildroot-linux-gnueabihf/sysroot/usr/share/OpenCV)

list(APPEND CMAKE_MODULE_PATH "OpenCV_DIR/OpenCV")

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

file(GLOB srcs
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_executable(${PROJECT_NAME} ${srcs})




target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

