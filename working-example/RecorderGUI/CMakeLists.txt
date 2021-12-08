cmake_minimum_required(VERSION 3.5)

project(ScreenRecorder VERSION 0.1 LANGUAGES CXX)


if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MACOSX TRUE)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(LINUX TRUE)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(WINDOWS TRUE)
endif()

if(WINDOWS)
    set(CMAKE_CXX_COMPILER_WORKS 1)
    set(CMAKE_CXX_COMPILER "g++" )
    set(CMAKE_MAKE_PROGRAM "make")
endif()


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(UI_DIR ./ui)

if(WINDOWS)
    include_directories(${UI_DIR} ffmpeg/ include/)
else()
    include_directories(${UI_DIR} ffmpeg/)
endif()

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

if (WINDOWS)
    set(CMAKE_PREFIX_PATH "F:/Programmi/QT/5.12.11/winrt_x64_msvc2017")
    find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
    find_package(QT NAMES Qt5 COMPONENTS Core REQUIRED)
    find_package(QT NAMES Qt5 COMPONENTS Gui REQUIRED)
endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
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
        ffmpeg/ListAVDevices.cpp
        ffmpeg/ListAVDevices.h
        )
if(MACOSX)
    qt_wrap_ui(PROJECT_SOURCES ui/Recorder.ui )
else()
    qt5_wrap_ui(PROJECT_SOURCES ui/Recorder.ui)
endif()

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

if(WINDOWS)
    option(CMAKE_USE_WIN32_THREADS_INIT "using WIN32 threads" ON)
    set(CMAKE_PREFIX_PATH lib/)
else()
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
    target_link_libraries(ScreenRecorder PRIVATE Threads::Threads)
endif()


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
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ScreenRecorder)
    if(!MACOSX)
        qt5_wrap_ui()
    endif()
endif()
