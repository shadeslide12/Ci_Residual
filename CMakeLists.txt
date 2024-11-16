cmake_minimum_required(VERSION 3.20)
project(CI_Res)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/resource)

find_package(Qt5 5.15 COMPONENTS Charts Core Gui Widgets REQUIRED)

if(Qt5_FOUND)
    message(STATUS "Qt is located at : ${Qt5_Dir}")
endif ()

set(UI_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/resource/MainWindow.ui
)
set(RCC_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/resource/resource.qrc
)
set(SRC_FILES
        main.cpp
        mainwindow.cpp
        ResidualPlot.cpp
        ResultPlot.cpp
        CipherRunner.cpp
        setting.cpp
)

message(STATUS "UI_FILES: ${UI_FILES}")
message(STATUS "SRC_FILES: ${SRC_FILES}")

add_executable(QtTest
        ${SRC_FILES}
        ${UI_FILES}
        ${RCC_FILES}
)

target_include_directories(QtTest PRIVATE
        ${CMAKE_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(QtTest PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Charts
)

add_subdirectory(ui_show)