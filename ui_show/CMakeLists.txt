add_executable(ui_show main.cpp
            MainWindow.cpp
)


target_include_directories(ui_show PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ui_show PUBLIC
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Charts
)