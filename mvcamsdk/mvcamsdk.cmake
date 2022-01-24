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


ELSEIF(WIN32)

ELSE()

ENDIF()

add_library(mvcam_lib STATIC)
target_link_libraries(mvcam_lib
    PUBLIC libmvsdk
)