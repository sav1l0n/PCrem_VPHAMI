cmake_minimum_required(VERSION 3.16)

project(PCrem_VPHAMI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Находим Qt Widgets и Sql
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

# Указываем исходники проекта
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

# Создаем исполняемый файл
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(PCrem_VPHAMI
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        AddOrderDialog.ui
        AddOrderDialog.h AddOrderDialog.cpp
    )
else()
    if(ANDROID)
        add_library(PCrem_VPHAMI SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(PCrem_VPHAMI
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Подключаем библиотеки Qt Widgets и Sql
target_link_libraries(PCrem_VPHAMI PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)

# Свойства для iOS/macOS/Windows
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.PCrem_VPHAMI)
endif()
set_target_properties(PCrem_VPHAMI PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Установка исполняемого файла
include(GNUInstallDirs)
install(TARGETS PCrem_VPHAMI
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Финализация для Qt6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(PCrem_VPHAMI)
endif()
