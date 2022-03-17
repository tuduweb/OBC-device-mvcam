
add_library(mvcam_lib STATIC)

IF(APPLE)
#${CMAKE_SOURCE_DIR}/mvcamsdk
set(mvcamsdk_libs_DIR ${CMAKE_SOURCE_DIR}/mvcamsdk/darwin/lib)
set(mvcamsdk_headers_DIR ${CMAKE_SOURCE_DIR}/mvcamsdk/darwin/include)

add_library(libmvsdk SHARED IMPORTED)
#指定所添加依赖库的导入路径
set_target_properties(libmvsdk PROPERTIES IMPORTED_LOCATION ${mvcamsdk_libs_DIR}/libmvsdk.dylib )

file(GLOB LIBRARIES ${mvcamsdk_libs_DIR}/*.dylib)
message("LIBRARIES = ${LIBRARIES}")

file(GLOB HEADERS ${mvcamsdk_headers_DIR}/*)
message("HEADERS = ${HEADERS}")


include_directories( ${mvcamsdk_headers_DIR} )
link_directories(${mvcamsdk_libs_DIR} )

target_link_libraries(mvcam_lib
    PUBLIC libmvsdk
)

ELSEIF(WIN32)

set(mvcamsdk_libs_DIR ${CMAKE_SOURCE_DIR}/mvcamsdk/win32/lib)
set(mvcamsdk_headers_DIR ${CMAKE_SOURCE_DIR}/mvcamsdk/win32/include)

add_library(libmvsdk STATIC IMPORTED)
#指定所添加依赖库的导入路径 #为libmvsdk 指定属性 IMPORTED_LOCATION ..
set_target_properties(libmvsdk PROPERTIES IMPORTED_LOCATION ${mvcamsdk_libs_DIR}/MVCAMSDK_X64.lib )

# file(GLOB LIBRARIES ${mvcamsdk_libs_DIR}/*_X64.lib)
# message("LIBRARIES = ${LIBRARIES}")

file(GLOB HEADERS ${mvcamsdk_headers_DIR}/*)
message("HEADERS = ${HEADERS}")

include_directories( ${mvcamsdk_headers_DIR} )
#link_directories(${mvcamsdk_libs_DIR} )


target_link_libraries(mvcam_lib
    #PUBLIC ${mvcamsdk_libs_DIR}/MVCAMSDK_X64.lib
    PUBLIC libmvsdk
)

ELSE()

ENDIF()
