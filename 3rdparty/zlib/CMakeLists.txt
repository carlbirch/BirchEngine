set(library_name zlib)
set(library_version ${zlib_version})
set(library_fullname ${library_name}-${library_version})
set(library_path ${zlib_path})

get_archive(
    https://zlib.net/${library_fullname}.tar.gz
    ${library_fullname}
)

add_subdirectory(${library_path} ${library_path})
