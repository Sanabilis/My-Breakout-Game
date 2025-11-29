################################################################################
# Common Framework for Computer Graphics Courses at FI MUNI.
#
# Copyright (c) 2021-2022 Visitlab (https://visitlab.fi.muni.cz)
# All rights reserved.
#
# Course: PA199 (Project Template)
################################################################################

# Generates the lecture. DO NOT MODIFY THIS COMMAND:
visitlab_generate_lecture(PA199 project)

# Finds the external libraries and load their settings.
find_package(lodepng CONFIG REQUIRED)

target_sources(PA199_project
    # Here you can add more source files to the excutable of the game.
    PUBLIC "./my_game.cpp" # This includes the tutorial file. Can be removed.
    PUBLIC "./my_engine/camera/camera.cpp"
    PUBLIC "./my_engine/camera/preview_camera.cpp"
    PUBLIC "./my_engine/mesh/mesh.cpp"
    PUBLIC "./my_engine/light/light.cpp"
    PUBLIC "./my_engine/buffers/buffer_data.cpp"
    PUBLIC "./my_engine/buffers/camera_buffer.cpp"
    PUBLIC "./my_engine/buffers/model_buffer.cpp"
    PUBLIC "./my_engine/buffers/light_buffer.cpp"
    PUBLIC "./my_engine/physics/physics_object.cpp"
    PUBLIC "./my_engine/collision/base_collider.cpp"
    PUBLIC "./my_engine/collision/circle_collider.cpp"
    PUBLIC "./my_engine/collision/paddle_collider.cpp"
    PUBLIC "./my_engine/scene/scene_base_object.cpp"
    PUBLIC "./my_engine/scene/scene_model_object.cpp"
    PUBLIC "./my_engine/scene/scene_physics_object.cpp"
    PUBLIC "./my_engine/scene/scene_ball_physics_object.cpp"
    PUBLIC "./my_engine/scene/scene_paddle_physics_object.cpp"
    PUBLIC "./my_engine/scene/scene_camera_object.cpp"
    PUBLIC "./my_engine/scene/scene_preview_camera_object.cpp"
    PUBLIC "./my_engine/scene/scene_light_object.cpp"
    PUBLIC "./my_engine/scene/scene_gui_object.cpp"
    PUBLIC "./my_game/ball.cpp"
    PUBLIC "./my_game/powerup.cpp"
    PUBLIC "./my_game/brick.cpp"
    PUBLIC "./my_game/paddle.cpp"
    PUBLIC "./my_game/gui_score.cpp"
    PUBLIC "./my_game/gui_lives.cpp"
)

# Add sub-directories of your libraries
add_subdirectory("libraries")  # This includes the tutorial library. Can be removed.

# Include your liblaries to linking of the project.
target_link_libraries(PA199_project
    PUBLIC 
        lodepng # This links the lodepng library. Do not remove.
        "my_engine_math" # This links the tutorial library. Can be removed.
)

# Includes 'unit_tests' project to the build. DO NOT MODIFY THIS COMMAND:
add_subdirectory("test")  # Do not rename the directory name.

# Installing the application. Do not modify!
install(TARGETS PA199_project DESTINATION .)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/glfw3.dll OPTIONAL DESTINATION .)
install(CODE [[file(WRITE ${CMAKE_INSTALL_PREFIX}/configuration.toml "framework_dir = \".\"\nlecture_dir = \".\"")]])
install(DIRECTORY ./data DESTINATION .)
