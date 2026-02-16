cmake_minimum_required(VERSION 3.16)

project(HealthTrack VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS
    Quick
    QuickControls2
)

qt_standard_project_setup(REQUIRES 6.8)

if(ANDROID)
    set(CMAKE_SYSTEM_VERSION 34)
endif()

qt_add_executable(appHealthTrack
    main.cpp
)

qt_add_qml_module(appHealthTrack
    URI HealthTrack
    VERSION 1.0
    QML_FILES
        Main.qml
        QML_FILES LoginPage.qml
        QML_FILES HomeScreen.qml
        QML_FILES Nutrition.qml
        QML_FILES Sport.qml
        QML_FILES Sleep.qml
        QML_FILES Profile.qml
        QML_FILES Settings.qml
        QML_FILES Statistics.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appHealthTrack PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appHealthTrack
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appHealthTrack PRIVATE
    Qt6::Quick
    Qt6::QuickControls2
)

include(GNUInstallDirs)
install(TARGETS appHealthTrack
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
