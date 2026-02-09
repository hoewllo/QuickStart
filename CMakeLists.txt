cmake_minimum_required(VERSION 3.16)

project(QtAppLauncher VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# 设置UI文件目录
set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui")

# 设置构建输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 源文件
set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/appitem.cpp
    src/funcitem.cpp
    src/appconfigdialog.cpp
    src/funcconfigdialog.cpp
    src/icongenerator.cpp  # 添加图标生成器
)

# 头文件
set(HEADERS
    include/mainwindow.h
    include/appitem.h
    include/funcitem.h
    include/appconfigdialog.h
    include/funcconfigdialog.h
    include/icongenerator.h  # 添加图标生成器头文件
)

# UI文件
set(UI_FILES
    ui/mainwindow.ui
    ui/appconfigdialog.ui
    ui/funcconfigdialog.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QtAppLauncher
        MANUAL_FINALIZATION
        ${SOURCES}
        ${HEADERS}
        ${UI_FILES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET QtAppLauncher APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
        add_executable(QtAppLauncher
            ${SOURCES}
            ${HEADERS}
            ${UI_FILES}
        )
    endif()

target_include_directories(QtAppLauncher PRIVATE include)
target_include_directories(QtAppLauncher PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
target_link_libraries(QtAppLauncher PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# 设置可执行文件属性
set_target_properties(QtAppLauncher PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE FALSE
)

# 安装目标
install(TARGETS QtAppLauncher
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QtAppLauncher)
endif()

