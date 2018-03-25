cmake_minimum_required(VERSION 3.5)
project(CFactorial-IDE)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_PREFIX_PATH "/home/marco/Qt5.7.0/5.7/gcc_64")


find_package(Qt5Widgets REQUIRED)
include_directories(${Qt5Widgets_INCLUDE_DIRS})

find_package(Qt5Network REQUIRED)
include_directories(${Qt5Network_INCLUDE_DIRS})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Network_EXECUTABLE_COMPILE_FLAGS}")

add_executable(CFactorial-IDE main.cpp MainWindow.h MainWindow.cpp ServerConnection.cpp ServerConnection.h NetworkAdapter.cpp NetworkAdapter.h "Parse Structure/IDE_Expression.h" "Parse Structure/ScopeExpression.cpp" "Parse Structure/ScopeExpression.h" "Parse Structure/IDE_Expression.cpp" "Parse Structure/AssignmentExpression.cpp" "Parse Structure/AssignmentExpression.h" "Parse Structure/DeclarationExpression.cpp" "Parse Structure/DeclarationExpression.h" "Parse Structure/ArithmeticExpression.cpp" "Parse Structure/ArithmeticExpression.h")

target_link_libraries(CFactorial-IDE Qt5::Widgets)
target_link_libraries(CFactorial-IDE Qt5::Network)
