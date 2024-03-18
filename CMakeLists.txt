cmake_minimum_required(VERSION 3.5)

project(mediaSelector VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


#TODO: Eine CMakeLists.txt für die Tests schreiben, dann wäre die CMakeLists.txt hier etwas aufgeräumter

# Finden der Packages -> die müssen aber im Anschluss noch mit target_link_libraries
# mit dem target, also der executeable verbunden werden
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Charts)

set(PROJECT_SOURCES
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        credentialdialog.h
        credentialdialog.cpp
        credentialdialog.ui
)


# Erstelle eine statische Bibliothek für das Hauptprojekt
add_library(mediaSelectorLib STATIC
    ${PROJECT_SOURCES}
    dbmanager.h dbmanager.cpp
    datamanager.h datamanager.cpp
    helperfunction.h helperfunction.cpp
)

# Verknüpfen der Bibliothek mit allem was sie braucht um lauffähig zu sein
target_link_libraries(mediaSelectorLib PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Sql
        Qt${QT_VERSION_MAJOR}::Charts
)

set (TEST_SOURCES
    tests/testmain.cpp
    tests/testdatabaseconnection.cpp
    tests/testdatabaseconnection.h
    tests/teststringoperations.h
    tests/teststringoperations.cpp
    tests/testdatabasequeries.h
    tests/testdatabasequeries.cpp
)

# Fügen Sie Unittests hinzu
# Jetzt bekommt also die .exe für die Tests alle Inhalte der PROJECT_SOURCES und
# der offensichtlichen Testdateien (die hoffentlich immer test im Namen haben)
# sie heißt mediaSelectorTests
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(mediaSelectorTests
        ${PROJECT_SOURCES}
        ${TEST_SOURCES}
        dbmanager.cpp datamanager.cpp helperfunction.cpp

    )
else()
    add_executable(mediaSelectorTests
        ${PROJECT_SOURCES}
        ${TEST_SOURCES}
    )
endif()

# Pakete mit der Test-Executable verbinden
target_link_libraries(mediaSelectorTests PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Test
)


# Erstelle die Anwendung, achte auf den Suffix App
add_executable(mediaSelectorApp
    main.cpp
)


# Verknüpfen der gefundenen Pakete mit der Anwendungs-Target
# Heißt die ausführbare Datei
target_link_libraries(mediaSelectorApp PRIVATE
    mediaSelectorLib
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
)


# Setze die Ziel-Eigenschaften für die Unittests
set_target_properties(mediaSelectorTests PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    BUNDLE_ID "com.example.mediaSelector.tests"
)

# Setze die Ziel-Eigenschaften für die Anwendung
set_target_properties(mediaSelectorApp PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    BUNDLE_ID "com.example.mediaSelector.app"
)


include(GNUInstallDirs)
install(TARGETS mediaSelectorApp mediaSelectorLib
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(mediaSelectorApp)

endif()
