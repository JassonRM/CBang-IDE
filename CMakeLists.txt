cmake_minimum_required(VERSION 3.5)
project(CFactorial-IDE)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_PREFIX_PATH "/Applications/Qt/5.10.1/clang_64")

set(Boost_INCLUDE_DIR /usr/local/Cellar/boost/1.66.0/include)
set(Boost_LIBRARY_DIR /usr/local/Cellar/boost/1.66.0/lib)

find_package(Qt5Widgets REQUIRED)
include_directories(${Qt5Widgets_INCLUDE_DIRS})

find_package(Qt5Network REQUIRED)
include_directories(${Qt5Network_INCLUDE_DIRS})

find_package(Boost COMPONENTS system REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Network_EXECUTABLE_COMPILE_FLAGS}")

add_executable(CFactorial-IDE main.cpp MainWindow.h MainWindow.cpp ServerConnection.cpp ServerConnection.h TokenTypes.h Token.cpp Token.h Json.cpp Json.h tinyexpr.h tinyexpr.c Parser.cpp Parser.h JsonArray.cpp JsonArray.h loguru.hpp Requests.cpp Requests.h TextEditor.cpp TextEditor.h Highlighter.cpp Highlighter.h)

target_link_libraries(CFactorial-IDE Qt5::Widgets)
target_link_libraries(CFactorial-IDE Qt5::Network)
find_package(Threads)
target_link_libraries(CFactorial-IDE ${CMAKE_THREAD_LIBS_INIT}) # For pthreads
target_link_libraries(CFactorial-IDE dl) # For ldl
