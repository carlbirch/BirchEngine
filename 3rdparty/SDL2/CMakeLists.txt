set(library_name SDL2)
set(library_version 2.0.7)
set(library_fullname ${library_name}-${library_version})
set(library_path ${CMAKE_CURRENT_BINARY_DIR}/${library_fullname})

get_archive(
    https://www.libsdl.org/release/${library_fullname}.tar.gz
    ${library_fullname}
)

option(SDL_SHARED "Build a shared version of the library" OFF)

add_subdirectory(${library_path} ${library_path})

target_include_directories(SDL2-static PUBLIC
    $<BUILD_INTERFACE:${library_path}/include>
)
