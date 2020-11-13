cmake_minimum_required(VERSION 3.0)

project(rtc-pattern-recognition)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -pedantic)

find_package(OpenCV REQUIRED)
find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-3.0)

add_subdirectory(src) 

include_directories(
    include
    ${OpenCV_INCLUDE_DIRS}
)

add_executable(init src/initializer.cpp src/pqueue.cpp src/semaphoreop.cpp)

add_executable(gene src/generator.cpp src/pqueue.cpp src/semaphoreop.cpp)
target_link_libraries(gene ${OpenCV_LIBS})

add_executable(conv src/converter.cpp src/pqueue.cpp src/semaphoreop.cpp)
target_link_libraries(conv ${OpenCV_LIBS})

add_executable(dest src/destroyer.cpp)
