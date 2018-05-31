function(untar_archive archive_name destpath)
    if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/${destpath})
        set(archive_sourcepath ${CMAKE_CURRENT_BINARY_DIR}/${archive_name})
        set(archive_destpath ${CMAKE_CURRENT_BINARY_DIR})
        message(STATUS "Unzipping ${archive_sourcepath} to ${archive_destpath}...")
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E tar xzf ${archive_sourcepath}
            WORKING_DIRECTORY ${archive_destpath}
        )
    endif()
endfunction(untar_archive)

function(get_archive archive_url destpath)
    get_filename_component(archive_name ${archive_url} NAME)
    set(archive_destpath ${CMAKE_CURRENT_BINARY_DIR}/${archive_name})
    if(NOT EXISTS ${archive_destpath})
        message(STATUS "Downloading ${archive_url} to ${archive_destpath}...")
        file(DOWNLOAD
            ${archive_url}
            ${archive_destpath}
            STATUS download_status
        )
        list(GET download_status 0 download_error_code)
        list(GET download_status 1 download_error_msg)
        if(NOT ${download_error_code} EQUAL 0)
            message(FATAL_ERROR "Download failed, error code ${download_error_code}: ${download_error_msg}")
            file(REMOVE ${archive_destpath})
        endif()
    endif()
    untar_archive(${archive_name} ${destpath})
endfunction(get_archive)

function(copy_file sourcepath destpath)
    message(STATUS "Copying ${sourcepath} to ${destpath}")

    execute_process(
       COMMAND
           ${CMAKE_COMMAND} -E copy
           ${sourcepath}
           ${destpath}
    )
endfunction(copy_file)

set(zlib_version 1.2.11)
set(zlib_path ${CMAKE_BINARY_DIR}/3rdparty/zlib/zlib-${zlib_version})
add_subdirectory(zlib)

add_subdirectory(freetype)
add_subdirectory(libpng)
add_subdirectory(SDL2)
add_subdirectory(SDL2_image)
add_subdirectory(SDL2_ttf)
