set(target_name BirchEngine)

set(src_files
    Collision.h
    Collision.cpp
    Game.cpp
    Game.h
    main.cpp
    Map.cpp
    Map.h
    TextureManager.cpp
    TextureManager.h
    Vector2D.cpp
    Vector2D.h
)
set(ecs_files
    ECS/Animation.h
    ECS/ColliderComponent.h
    ECS/Components.h
    ECS/ECS.cpp
    ECS/ECS.h
    ECS/KeyboardController.h
    ECS/SpriteComponent.h
    ECS/TileComponent.h
    ECS/TransformComponent.h
)
add_executable(${target_name}
    ${src_files}
    ${ecs_files}
)
source_group(Src FILES ${src_files})
source_group(Src\\ECS FILES ${ecs_files})

target_include_directories(${target_name} PRIVATE
    .
)

target_link_libraries(${target_name}
    SDL2-static
    SDL2main
    SDL2_image
)

include(../../copy_files_to_binary_dir.cmake)
