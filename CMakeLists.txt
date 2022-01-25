cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)

set(CMAKE_C_COMPILER /home/luiscarlos/buildroot/buildroot-2021.02.5/output/host/bin/arm-buildroot-linux-gnueabihf-gcc ${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_CXX_COMPILER /home/luiscarlos/buildroot/buildroot-2021.02.5/output/host/bin/arm-buildroot-linux-gnueabihf-g++ ${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)



project(smartFitness LANGUAGES C CXX)

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
set (OpenCV_DIR home/luiscarlos/buildroot/buildroot-2021.02.5/output/host/arm-buildroot-linux-gnueabihf/sysroot/usr/share/OpenCV)
set(Qt5_DIR /home/luiscarlos/buildroot/buildroot-2021.02.5/output/host/arm-buildroot-linux-gnueabihf/sysroot/usr/lib/cmake/Qt5)


find_package(OpenCV REQUIRED PATHS /home/luiscarlos/buildroot/buildroot-2021.02.5/output/host/arm-buildroot-linux-gnueabihf/sysroot/usr/share/OpenCV NO_DEFAULT_PATH)
find_package(SQLite3)
find_package(Qt5 COMPONENTS Widgets REQUIRED PATHS /home/luiscarlos/buildroot/buildroot-2021.02.5/output/host/arm-buildroot-linux-gnueabihf/sysroot/usr/lib/cmake/Qt5 NO_DEFAULT_PATH)

find_package(Threads REQUIRED)

include_directories(include ${OpenCV_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/includes ${SQLite3_INCLUDE_DIRS})

file(GLOB srcs
 	#"${PROJECT_SOURCE_DIR}/src/camera.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.cpp" "${PROJECT_SOURCE_DIR}/src/*.ui"    
)


add_executable(${PROJECT_NAME} ${srcs} includes/mainwindow.h includes/secondwindow.h)


target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${SQLite3_LIBRARIES} Qt5::Widgets -lrt)
#target_link_libraries(${PROJECT_NAME} )
