cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_COMPILER_WORKS 1)

set(CMAKE_CXX_COMPILER "g++" )
set(CMAKE_MAKE_PROGRAM "make")

project(ScreenRecorder VERSION 0.1 LANGUAGES CXX)
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MACOSX TRUE)
endif()
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(UI_DIR ./ui)
include_directories(${UI_DIR} ffmpeg/ include/)


set(CMAKE_AUTOUIC_SEARCH_PATHS ${UI_DIR}/)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
if(MACOSX)
    set(CMAKE_PREFIX_PATH "/Users/alessandrobacci/Qt/6.2.0/macos/lib/cmake")
    include_directories(/usr/local/include)
endif()
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "F:/Programmi/QT/5.12.11/winrt_x64_msvc2017")
find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(QT NAMES Qt5 COMPONENTS Core REQUIRED)
find_package(QT NAMES Qt5 COMPONENTS Gui REQUIRED)

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        resources.qrc
        recorder.cpp
        recorder.h
        ui/Recorder.ui
        resizableframe.cpp
        resizableframe.h
        ffmpeg/ScreenRecorder.h
        ffmpeg/ScreenRecorder.cpp
        )

qt5_wrap_ui(PROJECT_SOURCES ui/Recorder.ui)
#qt_wrap_ui(PROJECT_SOURCES ui/Recorder.ui )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ScreenRecorder
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
            )
else()
    if(ANDROID)
        add_library(ScreenRecorder SHARED
                ${PROJECT_SOURCES}
                )
    else()
        add_executable(ScreenRecorder
                ${PROJECT_SOURCES}
                )
    endif()
endif()

target_link_libraries(ScreenRecorder PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

#option(CMAKE_USE_WIN32_THREADS_INIT "using WIN32 threads" ON)
#set(THREADS_PREFER_PTHREAD_FLAG ON)
#find_package(Threads REQUIRED)
#target_link_libraries(ScreenRecorder PRIVATE Threads::Threads)

set(CMAKE_PREFIX_PATH lib/)


find_library(AVCODEC_LIBRARY avcodec)
find_library(AVFORMAT_LIBRARY avformat)
find_library(SWSCALE_LIBRARY swscale)
find_library(AVDEVICE_LIBRARY avdevice)
find_library(AVUTIL_LIBRARY avutil)
find_library(SWRESAMPLE_LIBRARY swresample)
find_library(SWSCALE_LIBRARY swscale)

target_link_libraries(ScreenRecorder PRIVATE ${AVCODEC_LIBRARY})
target_link_libraries(ScreenRecorder PRIVATE ${AVFORMAT_LIBRARY})
target_link_libraries(ScreenRecorder PRIVATE ${SWSCALE_LIBRARY})
target_link_libraries(ScreenRecorder PRIVATE ${AVDEVICE_LIBRARY})
target_link_libraries(ScreenRecorder PRIVATE ${AVUTIL_LIBRARY})
target_link_libraries(ScreenRecorder PRIVATE ${SWRESAMPLE_LIBRARY})
target_link_libraries(ScreenRecorder PRIVATE ${SWSCALE_LIBRARY})

set_target_properties(ScreenRecorder PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        )
#qt_finalize_executable(ScreenRecorder)
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ScreenRecorder)
#    qt5_wrap_ui()
endif()
