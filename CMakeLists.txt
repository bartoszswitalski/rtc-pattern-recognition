cmake_minimum_required(VERSION 3.0)

project(rtc-pattern-recognition)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -pedantic)

find_package(OpenCV REQUIRED)
find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-3.0)

include_directories(
    include
    ${OpenCV_INCLUDE_DIRS}
    ${GTKMM_INCLUDE_DIRS}
)

add_executable(configure src/configure.cpp)
target_link_libraries(configure ${OpenCV_LIBS})

add_executable(init src/initializer.cpp src/semaphoreop.cpp)

add_executable(gene src/generator.cpp src/semaphoreop.cpp)
target_link_libraries(gene ${OpenCV_LIBS})

add_executable(conv src/converter.cpp src/semaphoreop.cpp)
target_link_libraries(conv ${OpenCV_LIBS})

add_executable(disp src/displayer.cpp src/displaywindow.cpp src/semaphoreop.cpp)
target_link_libraries(disp ${GTKMM_LIBRARIES})

add_executable(dest src/destroyer.cpp)
