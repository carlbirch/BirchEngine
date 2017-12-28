cmake_minimum_required(VERSION 3.0.2)

project(BirchEngine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(
        /MP # Multi-processor Compilation
        $<$<CONFIG:Debug>:/MTd>$<$<CONFIG:Release>:/MT>$<$<CONFIG:>:/MT> # Statically link the runtime libraries
        /permissive- # Standard C++ Conformance
    )
endif()

set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/_install)

# Organize source files into subdirectories with 'source_group'
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(3rdparty)
add_subdirectory(BirchEngine/Src)
