cmake_minimum_required(VERSION 3.16)

project(ActiveDesktop VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Path to FFmpeg includes and libraries
set(FFmpeg_INCLUDE_DIR "C:/Users/IMPEG/miniconda3/Library/include")
set(FFmpeg_LIB_DIR "C:/Users/IMPEG/miniconda3/Library/lib")

# Include FFmpeg headers
include_directories(${FFmpeg_INCLUDE_DIR})
# Link directories for FFmpeg libraries
link_directories(${FFmpeg_LIB_DIR})

# Find Qt packages
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets MultimediaWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets MultimediaWidgets)
find_package(Qt6 REQUIRED COMPONENTS Core5Compat)


# Define sources
set(PROJECT_SOURCES
    main.cpp
    video_player.h
    video_player.cpp
    video_item.h
    video_item.cpp

    tool_manager.h
    tool_manager.cpp
    resource.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ActiveDesktop
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        video_player_slider.h video_player_slider.cpp
        terminal.h terminal.cpp
        tool_seperator.h tool_seperator.cpp
        splitter_anchor.h splitter_anchor.cpp
    )
else()
    if(ANDROID)
        add_library(ActiveDesktop SHARED ${PROJECT_SOURCES})
    else()
        add_executable(ActiveDesktop ${PROJECT_SOURCES})
    endif()
endif()

# Link Qt libraries
target_link_libraries(ActiveDesktop PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::MultimediaWidgets)
target_link_libraries(ActiveDesktop PRIVATE Qt6::Core5Compat)
# Link FFmpeg libraries
target_link_libraries(ActiveDesktop PRIVATE
    avcodec
    avformat
    avutil
    avdevice
    avfilter
    swscale
    swresample
    postproc
)

# Set target properties for macOS and Windows
if(${QT_VERSION_MAJOR} EQUAL 6)
    qt_finalize_executable(ActiveDesktop)
endif()

set_target_properties(ActiveDesktop PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

include(GNUInstallDirs)
install(TARGETS ActiveDesktop
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
