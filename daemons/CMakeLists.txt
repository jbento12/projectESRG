cmake_minimum_required(VERSION 3.0.0)

#set(CMAKE_C_COMPILER /home/luiscarlos/buildroot/buildroot-2021.02.5/output/host/bin/arm-buildroot-linux-gnueabihf-gcc ${CMAKE_EXECUTABLE_SUFFIX})
#set(CMAKE_CXX_COMPILER /home/luiscarlos/buildroot/buildroot-2021.02.5/output/host/bin/arm-buildroot-linux-gnueabihf-g++ ${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
project(AquireImage LANGUAGES C CXX)

#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})   
include(CPack)

set(CMAKE_BUILD_TYPE Debug)

#set the OpenCV variable to the given path
#set (OpenCV_DIR home/luiscarlos/buildroot/buildroot-2021.02.5/output/host/arm-buildroot-linux-gnueabihf/sysroot/usr/share/OpenCV)
# find_package(OpenCV REQUIRED PATHS /home/luiscarlos/buildroot/buildroot-2021.02.5/output/host/arm-buildroot-linux-gnueabihf/sysroot/usr/share/OpenCV NO_DEFAULT_PATH)

find_package(OpenCV REQUIRED)

file(GLOB srcs
 	#"${PROJECT_SOURCE_DIR}/src/camera.cpp"
    "${PROJECT_SOURCE_DIR}/*.cpp"   
)
set(EXECUTABLE_OUTPUT_PATH ./)

add_executable(${PROJECT_NAME} ${srcs})


target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} rt)
#target_link_libraries(${PROJECT_NAME} )
