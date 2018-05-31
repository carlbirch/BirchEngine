set(library_name SDL2_ttf)
set(library_version 2.0.14)
set(library_fullname ${library_name}-${library_version})
set(library_path ${CMAKE_CURRENT_BINARY_DIR}/${library_fullname})

get_archive(
    https://www.libsdl.org/projects/SDL_ttf/release/${library_fullname}.tar.gz
    ${library_fullname}
)

set(cmakelists_sourcepath ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists-${library_name}.txt)
set(cmakelists_destpath ${library_path}/CMakeLists.txt)
copy_file(${cmakelists_sourcepath} ${cmakelists_destpath})

add_subdirectory(${library_path} ${library_path})
