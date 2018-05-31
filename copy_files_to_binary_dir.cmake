# Stage images, fonts, etc... so that builds run from the binary dir will work
add_custom_command(
    TARGET ${target_name}
    POST_BUILD
    COMMAND cmake -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)

install(TARGETS ${target_name} DESTINATION ${target_name})
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../assets DESTINATION ${target_name})
