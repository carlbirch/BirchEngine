set(library_name libpng)
set(library_version 1.6.34)
set(library_fullname ${library_name}-${library_version})
set(library_path ${CMAKE_CURRENT_BINARY_DIR}/${library_fullname})

get_archive(
    http://dnqpy.com/libs/${library_fullname}.tar.gz
    ${library_fullname}
)

option(PNG_BUILD_ZLIB "Custom zlib location" ON)
option(PNG_SHARED "Build shared pnglib" OFF)
set(ZLIB_INCLUDE_DIR ${zlib_path})

add_subdirectory(${library_path} ${library_path})

target_include_directories(png_static PUBLIC
    $<BUILD_INTERFACE:${library_path}>
)
