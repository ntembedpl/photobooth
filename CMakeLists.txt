cmake_minimum_required (VERSION 3.5)
project (photobooth)

find_package (OpenCV 4 REQUIRED)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_Release "-O3")

add_executable (photobooth inc/GUI.h inc/Screen.h inc/Element.h inc/Button.h inc/Video.h inc/TrackBar.h inc/Image.h inc/Touch.h inc/Utils.h inc/ConfigReader.h inc/Control.h inc/Programs.h
        src/GUI.cpp src/Screen.cpp src/Element.cpp src/Button.cpp src/Video.cpp src/TrackBar.cpp src/Image.cpp src/Touch.cpp src/Utils.cpp src/ConfigReader.cpp src/Control.cpp main.cpp src/Programs.cpp)

target_link_libraries (photobooth ${OpenCV_LIBS} pthread)
