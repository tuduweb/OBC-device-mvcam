cmake_minimum_required(VERSION 3.14)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "
    FATAL: In-source builds are not allowed.
           You should create a separate directory for build files.
           ")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # doesnt work
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # works

IF (APPLE)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/usr/local/opt/qt5/lib/cmake")
ENDIF()

project(OBCDeviceMvcam VERSION 0.1 LANGUAGES CXX)


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Widgets WebSockets Network LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets WebSockets Network LinguistTools REQUIRED)

# include(./src/plugin/ObPluginInterface.cmake)

include(./mvcamsdk/mvcamsdk.cmake)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/)

file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*)
file(GLOB SRC_WIDGETS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/*)

set(PROJECT_SOURCES
        #resources.qrc
        src/main.cpp
        ${HEADERS}
        ${SRC_FILES}
        ${SRC_WIDGETS_FILES}
)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
)

add_library(obc_baselib STATIC
)

if(APPLE)
    add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_INSTALL_NAME_TOOL} -add_rpath "@executable_path/../Frameworks/" $<TARGET_FILE:${PROJECT_NAME}>)
    
    # change dependency
    add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_INSTALL_NAME_TOOL} -change @executable_path/../Frameworks/libmvsdk.dylib ${mvcamsdk_libs_DIR}/libmvsdk.dylib $<TARGET_FILE:${PROJECT_NAME}>)
endif()

message(${CMAKE_INSTALL_NAME_TOOL})

target_link_libraries(obc_baselib
    PUBLIC Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC obc_baselib
    libmvsdk
)


# add_library()
# add_executable()

option(IS_BUILD_PLUGIN_EXAMPLES "build examples" ON)

if(IS_BUILD_PLUGIN_EXAMPLES)
    #修改目录位置 还要防止套娃现象发生
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/examples/)
endif()
