cmake_minimum_required(VERSION 3.10)
project(breadboard)

set(CMAKE_CXX_STANDARD 11)

set (CMAKE_PREFIX_PATH "D://EDIT//Qt//5.10.1//mingw53_32")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCE_FILES
        environment.cpp
        environment.h
        general_window.cpp
        general_window.h
        objects_named_states.cpp
        objects_named_states.h
        rw_view_obj.cpp
        rw_view_obj.h
        script_canvas.cpp
        script_canvas.h
        startup_config.cpp
        startup_config.h
        test_dcpp_viewer.h
        control_window.cpp
        control_window.h
        views_obj.h
        rw_stantion.h
        rw_stantion.cpp
        at_script_canvas.h
        at_script_canvas.cpp
        cyclocom.h
        cyclocom.cpp
        play_breadboard.h
        play_breadboard.cpp
        before_started.h
        before_started.cpp
        first_pix.h
        camera.cpp
        camera.h
        attcontroller.h)

set(SOURCE_FILES_BB_TEST
        bb_test.cpp
        bb_test_window.h
        bb_test_window.cpp attcontroller.h)

add_executable(breadboard WIN32 main.cpp ${SOURCE_FILES})
SET_TARGET_PROPERTIES(breadboard PROPERTIES COMPILE_FLAGS "-D_FIRST")

add_executable(bb_test WIN32 ${SOURCE_FILES_BB_TEST} ${SOURCE_FILES})
SET_TARGET_PROPERTIES(bb_test PROPERTIES COMPILE_FLAGS "-D_SECOND")

find_package(Qt5Widgets)
find_package (Qt5Core)

target_link_libraries(breadboard Qt5::Widgets Qt5::UiTools Qt5::SerialPort Qt5::Multimedia Qt5::MultimediaWidgets ${QT_QTMAIN_LIBRARY})
qt5_use_modules(breadboard Core Widgets Gui Script Uitools Network Serialport XmlPatterns Multimedia MultimediaWidgets)

target_link_libraries(bb_test Qt5::Widgets Qt5::UiTools Qt5::SerialPort ${QT_QTMAIN_LIBRARY})
qt5_use_modules(bb_test Core Widgets Gui Script Uitools Network Serialport XmlPatterns)

add_custom_command(
        TARGET breadboard POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_BINARY_DIR}//breadboard.exe
        ${CMAKE_SOURCE_DIR}//bin//${CMAKE_BUILD_TYPE}//breadboard.exe)

add_custom_command(
        TARGET breadboard POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_BINARY_DIR}//bb_test.exe
        ${CMAKE_SOURCE_DIR}//bin//${CMAKE_BUILD_TYPE}//bb_test.exe)
