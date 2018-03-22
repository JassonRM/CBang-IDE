cmake_minimum_required(VERSION 3.5)

project(CFactorial-IDE)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_PREFIX_PATH "/Applications/Qt/5.10.1/clang_64")

# Find the QtWidgets library
find_package(Qt5Widgets)

# Add the include directories for the Qt 5 Widgets module to
# the compile lines.
include_directories(${Qt5Widgets_INCLUDE_DIRS})

# Use the compile definitions defined in the Qt 5 Widgets module
add_definitions(${Qt5Widgets_DEFINITIONS})

# Add compiler flags for building executables (-fPIE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

qt5_generate_moc(main.cpp main.moc)
set(CMAKE_AUTOMOC on)

# Tell CMake to create the helloworld executable
add_executable(helloworld main.cpp main.moc)

#Link the helloworld executable to the Qt 5 widgets library.
target_link_libraries(helloworld Qt5::Widgets)
