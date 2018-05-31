set(library_name freetype)
set(library_version 2.9.1)
set(library_fullname ${library_name}-${library_version})
set(library_path ${CMAKE_CURRENT_BINARY_DIR}/${library_fullname})

get_archive(
    http://download.savannah.gnu.org/releases/freetype/${library_fullname}.tar.gz
    ${library_fullname}
)

# Copy over an edited version of the freetype CMakeLists.txt file with the following changes:
# https://savannah.nongnu.org/bugs/index.php?53816
# https://savannah.nongnu.org/bugs/index.php?53815
set(cmakelists_sourcepath ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists-${library_name}.txt)
set(cmakelists_destpath ${library_path}/CMakeLists.txt)
copy_file(${cmakelists_sourcepath} ${cmakelists_destpath})

add_subdirectory(${library_path} ${library_path})
