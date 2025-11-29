// ################################################################################
// Common Framework for Computer Graphics Courses at FI MUNI.
// 
// Copyright (c) 2021-2022 Visitlab (https://visitlab.fi.muni.cz)
// All rights reserved.
// ################################################################################

#include "application.hpp"
#include "glad/glad.h"
#include "lodepng.h"
#include <filesystem>
#include <iostream>


namespace my_engine
{
    // Constants //
    MyEngine MyEngine::my_engine;

    // Private Constructors //
    MyEngine::MyEngine() : IApplication(1024, 768, {""}) {}

    // Initializator //
    void MyEngine::initialize_engine(int initial_width, int initial_height, std::vector<std::string> arguments)
    {
        my_engine.width = initial_width;
        my_engine.height = initial_height;
        my_engine.arguments = arguments;
        my_engine.configuration = Configuration(arguments[0]);

        my_engine.framework_folder_path = my_engine.configuration.get_path("framework_dir", "/framework");
        my_engine.lecture_folder_path = my_engine.configuration.get_path("lecture_dir", "/");

        my_engine.init_framebuffers();
        my_engine.init_shaders();
        my_engine.init_textures();
        my_engine.init_skybox();

        my_engine.init_game();
        my_engine.init_gui();
        my_engine.init_cameras();
        my_engine.init_models();
        my_engine.init_lights();
    }

    void MyEngine::init_framebuffers()
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &_shadow_texture);
        glTextureStorage2D(_shadow_texture, 1, GL_DEPTH_COMPONENT24, _shadow_texture_size, _shadow_texture_size);

        glTextureParameteri(_shadow_texture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTextureParameteri(_shadow_texture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTextureParameteri(_shadow_texture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTextureParameteri(_shadow_texture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glCreateFramebuffers(1, &_shadow_framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, _shadow_framebuffer);
        glNamedFramebufferTexture(_shadow_framebuffer, GL_DEPTH_ATTACHMENT, _shadow_texture, 0);
    }

    void MyEngine::init_cameras()
    {
        my_engine._camera_buffer = std::make_unique<CameraBuffer>();

        my_engine._preview_cam = std::make_unique<ScenePreviewCameraObject>
        (
            Vector3(0.0f), Vector3(1.0f), Quaternion(),
            PreviewCamera
            (
                PI / 4.0f, PI / 4.0f, 6.0f, PI / 4.f,
                static_cast<float>(width), static_cast<float>(height), 0.01f, 1000.0f,
                Camera::CameraType::Perspective
            )
        );

        my_engine._preview_cam->set_buffer(my_engine._camera_buffer.get());

        my_engine::Vector2 boundaries = my_engine::Camera::orthographic_boundaries
        (
            my_engine::PI / 3.f, std::sqrt(18.0f),
            static_cast<float>(my_engine.width) / static_cast<float>(my_engine.height)
        );

        my_engine.instantiate_camera(Vector3(0.0f, 3.0f, 3.0f), -Vector3(0.0f, 3.0f, 3.0f), PI / 3.0f, my_engine.width, my_engine.height, 0.1f, 1000.0f, Camera::CameraType::Perspective);
        my_engine.instantiate_camera(Vector3(0.0f, std::sqrt(18.0f), 0.0f), Vector3::DOWN, PI / 3.0f, 2.0f * boundaries.x(), 2.0f * boundaries.y(), 0.1f, 1000.0f, Camera::CameraType::Orthographic);
        my_engine._camera_objects[0]->set_active();

        // Shadow Camera //
        my_engine.instantiate_camera(light_position, -light_position, PI / 2.0f, _shadow_texture_size, _shadow_texture_size, 0.1f, 20.0f, Camera::CameraType::Perspective);
    }

    void MyEngine::init_models()
    {
        my_engine.instantiate_model(0.125f * Vector3::DOWN, Vector3(3.8f), Quaternion(), Mesh::plane(64));
        my_engine._model_objects.back()->set_diffuse_texture(my_engine._textures.at("sand_diffuse"));
        my_engine._model_objects.back()->set_normal_texture(my_engine._textures.at("sand_normal"));

        float random_angle = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * 2.0f * PI;
        float cos = std::cos(random_angle), sin = std::sin(random_angle);
        Ball::instantiate(Vector3(cos, 0.0f, sin) * 1.5f, Vector3(0.25f));
        Ball::game_ball = my_engine._ball_physics_objects.back();

        Quaternion rot(2.0f * PI / 3.0f, Vector3::UP);
        Vector3 pos = Vector3::RIGHT;

        for (size_t i = 0; i < 3; i++)
        {
            Paddle::instantiate(pos, Vector3(4.0f));
            pos = rot.rotate(pos);
        }

        rot = Quaternion(PI / 6.0f, Vector3::UP);
        pos = Vector3::RIGHT;
        Brick::bricks_count = 0;

        for (size_t i = 0; i < 12; i++)
        {
            Brick::instantiate(pos, Vector3(1.5f), Quaternion(), 1, 3 + i % 2);
            pos = rot.rotate(pos);
        }
    }

    void MyEngine::init_lights()
    {
        my_engine._light_buffer = std::make_unique<LightBuffer>();
        my_engine.instantiate_point_light(light_position);
    }

    void MyEngine::init_textures()
    {
        my_engine._textures.insert({ "sand_diffuse", load_texture(my_engine.lecture_folder_path / "data" / "textures" / "sand_diffuse.png") });
        my_engine._textures.insert({ "sand_normal", load_texture(my_engine.lecture_folder_path / "data" / "textures" / "sand_normal.png") });

        my_engine._textures.insert({ "rock_diffuse", load_texture(my_engine.lecture_folder_path / "data" / "textures" / "rock_diffuse.png") });
        my_engine._textures.insert({ "rock_normal", load_texture(my_engine.lecture_folder_path / "data" / "textures" / "rock_normal.png") });

        my_engine._textures.insert({ "rock_cracked_diffuse", load_texture(my_engine.lecture_folder_path / "data" / "textures" / "rock_cracked_diffuse.png") });
        my_engine._textures.insert({ "rock_cracked_normal", load_texture(my_engine.lecture_folder_path / "data" / "textures" / "rock_cracked_normal.png") });

        my_engine._textures.insert({ "rock_broken_diffuse", load_texture(my_engine.lecture_folder_path / "data" / "textures" / "rock_broken_diffuse.png") });
        my_engine._textures.insert({ "rock_broken_normal", load_texture(my_engine.lecture_folder_path / "data" / "textures" / "rock_broken_normal.png") });

        my_engine._textures.insert({ "fabric_diffuse", load_texture(my_engine.lecture_folder_path / "data" / "textures" / "fabric_diffuse.png") });
        my_engine._textures.insert({ "fabric_normal", load_texture(my_engine.lecture_folder_path / "data" / "textures" / "fabric_normal.png") });

        my_engine._textures.insert({ "gui_win", load_texture(my_engine.lecture_folder_path / "data" / "textures" / "you_win.png") });
        my_engine._textures.insert({ "gui_defeat", load_texture(my_engine.lecture_folder_path / "data" / "textures" / "game_over.png") });
        my_engine._textures.insert({ "gui_pause", load_texture(my_engine.lecture_folder_path / "data" / "textures" / "pause.png") });
        my_engine._textures.insert({ "gui_lives", load_texture(my_engine.lecture_folder_path / "data" / "textures" / "lives.png") });
        my_engine._textures.insert({ "gui_score", load_texture(my_engine.lecture_folder_path / "data" / "textures" / "score.png") });
        my_engine._textures.insert({ "gui_digits", load_texture(my_engine.lecture_folder_path / "data" / "textures" / "digits.png") });
        my_engine._textures.insert({ "gui_heart", load_texture(my_engine.lecture_folder_path / "data" / "textures" / "heart.png") });
    }

    void MyEngine::init_gui()
    {
        my_engine.instantiate_gui_object(Vector2(-1.0f, -0.125f), Vector2(1.0f, 0.125f), Vector2(0.0f), Vector2(1.0f), Vector2(0.0f), my_engine._textures.at("gui_win"));
        my_engine.instantiate_gui_object(Vector2(-1.0f, -0.125f), Vector2(1.0f, 0.125f), Vector2(0.0f), Vector2(1.0f), Vector2(0.0f), my_engine._textures.at("gui_defeat"));
        my_engine.instantiate_gui_object(Vector2(-0.5f, -0.125f), Vector2(0.5f, 0.125f), Vector2(0.0f), Vector2(1.0f), Vector2(0.0f), my_engine._textures.at("gui_pause"));

        my_engine.instantiate_gui_object(Vector2(0.1f, 0.1f), Vector2(0.5f, 0.2f), Vector2(0.0f), Vector2(1.0f), Vector2(-1.0f), my_engine._textures.at("gui_score"));
        //my_engine.instantiate_gui_object(Vector2(-0.5727272f, 0.1f), Vector2(-0.1727272f, 0.2f), Vector2(0.0f), Vector2(1.0f), Vector2(1.0f, -1.0f), my_engine._textures.at("gui_lives"));

        GUIScore::instantiate(Vector2(0.5f, 0.1f), Vector2(0.5727272f, 0.2f), -Vector2(1.0f), 0);
        GUILives::instantiate(Vector2(-0.2f, 0.1f), Vector2(-0.1f, 0.2f), Vector2(1.0f, -1.0f), 3);
    }

    void MyEngine::init_game()
    {
        my_engine.space_pressed = false;
        state = GameState::Running;
        time_factor = 1.0f;
    }

    void MyEngine::init_shaders()
    {
        my_engine._phong_vertex_shader = load_shader(my_engine.lecture_folder_path / "data" / "shaders" / "phong_shader.vert", GL_VERTEX_SHADER);
        my_engine._phong_fragment_shader = load_shader(my_engine.lecture_folder_path / "data" / "shaders" / "phong_shader.frag", GL_FRAGMENT_SHADER);
        my_engine._phong_shader_program = create_program(my_engine._phong_vertex_shader, my_engine._phong_fragment_shader);

        my_engine._gui_vertex_shader = load_shader(my_engine.lecture_folder_path / "data" / "shaders" / "gui_shader.vert", GL_VERTEX_SHADER);
        my_engine._gui_fragment_shader = load_shader(my_engine.lecture_folder_path / "data" / "shaders" / "gui_shader.frag", GL_FRAGMENT_SHADER);
        my_engine._gui_shader_program = create_program(my_engine._gui_vertex_shader, my_engine._gui_fragment_shader);

        my_engine._shadow_vertex_shader = load_shader(my_engine.lecture_folder_path / "data" / "shaders" / "shadow_shader.vert", GL_VERTEX_SHADER);
        my_engine._shadow_fragment_shader = load_shader(my_engine.lecture_folder_path / "data" / "shaders" / "shadow_shader.frag", GL_FRAGMENT_SHADER);
        my_engine._shadow_shader_program = create_program(my_engine._shadow_vertex_shader, my_engine._shadow_fragment_shader);

        my_engine._skybox_vertex_shader = load_shader(my_engine.lecture_folder_path / "data" / "shaders" / "skybox_shader.vert", GL_VERTEX_SHADER);
        my_engine._skybox_fragment_shader = load_shader(my_engine.lecture_folder_path / "data" / "shaders" / "skybox_shader.frag", GL_FRAGMENT_SHADER);
        my_engine._skybox_shader_program = create_program(my_engine._skybox_vertex_shader, my_engine._skybox_fragment_shader);
    }

    void MyEngine::init_skybox()
    {
        std::vector<std::string> faces = { "right.png", "left.png", "top.png", "bottom.png", "front.png", "back.png" };
        glGenTextures(1, &_skybox);
        glBindTexture(GL_TEXTURE_CUBE_MAP, _skybox);

        glTextureStorage2D(_skybox, static_cast<GLsizei>(std::log2(2048)), GL_RGBA8, 2048, 2048);

        int width, height, nrChannels;
        for (unsigned int i = 0; i < faces.size(); i++)
        {
            std::vector<unsigned char> texels;
            unsigned int width, height;
            unsigned int error_code = lodepng::decode(texels, width, height, (my_engine.lecture_folder_path / "data" / "textures" / "skybox" / faces[i]).string(), LCT_RGBA);
            assert(error_code == 0);

            glTextureSubImage3D(_skybox, 0, 0, 0, i, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, texels.data());
        }

        glGenerateTextureMipmap(_skybox);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }


    // Destructors //
    MyEngine::~MyEngine()
    {
        clear();
    }

    void MyEngine::reset()
    {
        if (state == GameState::Victory)
        {
            size_t i = 0;

            while (i < _scene_objects.size())
            {
                if (_scene_objects[i]->scene_object->destroy_on_victory())
                {
                    _scene_objects.erase(_scene_objects.begin() + i);
                }
                else
                {
                    i++;
                }
            }
        }
        else
        {
            _scene_objects.clear();
            _gui_objects.clear();
            _gui_buffers.clear();

            init_gui();
        }

        _camera_objects.clear();
        _model_objects.clear();
        _ball_physics_objects.clear();
        _paddle_physics_objects.clear();
        _light_objects.clear();

        _model_buffers.clear();
        _camera_buffer.reset();
        _light_buffer.reset();

        init_game();
        init_cameras();
        init_models();
        init_lights();
    }

    void MyEngine::respawn()
    {
        state = GameState::Running;
        time_factor = 1.0f;
        space_pressed = false;

        float random_angle = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * 2.0f * PI;
        float cos = std::cos(random_angle), sin = std::sin(random_angle);
        Vector3 new_position = Vector3(cos, 0.0f, sin) * 1.5f;

        float direction_randomness = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) - 0.5f;
        Vector3 new_direction = Quaternion(0.25f * direction_randomness * PI, Vector3::UP).rotate(-new_position.normalized());

        Ball::game_ball->set_position(new_position);
        Ball::game_ball->set_direction(new_direction);
    }

    void MyEngine::clear()
    {
        _scene_objects.clear();
        _camera_objects.clear();
        _model_objects.clear();
        _ball_physics_objects.clear();
        _paddle_physics_objects.clear();
        _gui_objects.clear();
        _light_objects.clear();

        _model_buffers.clear();
        _gui_buffers.clear();
        _camera_buffer.reset();
        _light_buffer.reset();

        for (auto tex : _textures)
        {
            glDeleteTextures(1, &tex.second);
        }

        _textures.clear();

        glDeleteFramebuffers(1, &_shadow_framebuffer);
        glDeleteTextures(1, &_shadow_texture);
        glDeleteTextures(1, &_skybox);

        glDeleteShader(_phong_vertex_shader);
        glDeleteShader(_phong_fragment_shader);
        glDeleteProgram(_phong_shader_program);

        glDeleteShader(_gui_vertex_shader);
        glDeleteShader(_gui_fragment_shader);
        glDeleteProgram(_gui_shader_program);

        glDeleteShader(_shadow_vertex_shader);
        glDeleteShader(_shadow_fragment_shader);
        glDeleteProgram(_shadow_shader_program);

        glDeleteShader(_skybox_vertex_shader);
        glDeleteShader(_skybox_fragment_shader);
        glDeleteProgram(_skybox_shader_program);
    }


    // Number of Scene Objects //
    size_t MyEngine::scene_object_count()
    {
        return my_engine._scene_objects.size();
    }


    // Get Camera Matrices //
    Camera::CameraType MyEngine::get_camera_type()
    {
        return my_engine._camera_objects[my_engine._current_camera]->get_type();
    }

    GLuint MyEngine::get_texture(const std::string& texture)
    {
        return my_engine._textures.at(texture);
    }


    // Update Methods //
    void MyEngine::update(float delta)
    {
        _delta_counter += time_factor * delta;

        while (fixed_delta <= _delta_counter)
        {
            for (SceneBallPhysicsObject* ball_object : _ball_physics_objects)
            {
                ball_object->physics_update(fixed_delta / 1000.0f);
            }

            for (ScenePaddlePhysicsObject* paddle_object : _paddle_physics_objects)
            {
                paddle_object->physics_update(fixed_delta / 1000.0f);
            }

            for (SceneBallPhysicsObject* ball_object : _ball_physics_objects)
            {
                for (ScenePaddlePhysicsObject* paddle_object : _paddle_physics_objects)
                {
                    ball_object->collide(*paddle_object);
                }
            }
            
            _delta_counter -= fixed_delta;
        }

        for (std::unique_ptr<SceneObjectElement>& soe : _scene_objects)
        {
            soe->scene_object->update(time_factor * delta / 1000.0f);
        }

        for (std::unique_ptr<SceneObjectElement>& soe : _scene_objects)
        {
            soe->scene_object->late_update(time_factor * delta / 1000.0f);
        }

        size_t i = 0, size = _scene_objects.size();

        while (i < size)
        {
            if (_scene_objects[i]->scene_object->destroy())
            {
                destroy_scene_object(i);
                size--;
            }
            else
            {
                i++;
            }
        }

        for (auto pair : _to_be_instantiated)
        {
            instantiate(pair.first, pair.second);
        }

        _to_be_instantiated.clear();
    }


    // Render Methods //
    void MyEngine::render()
    {
        // Render the Shadow Texture //
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glDrawBuffer(GL_NONE);
        glDepthMask(GL_TRUE);

        glBindFramebuffer(GL_FRAMEBUFFER, _shadow_framebuffer);
        glViewport(0, 0, _shadow_texture_size, _shadow_texture_size);

        glClearDepth(1.0f);
        glClear(GL_DEPTH_BUFFER_BIT);

        glUseProgram(_shadow_shader_program);
        _camera_objects[2]->set_active();
        _camera_buffer->bind_buffer();
        _light_buffer->bind_buffer();

        for (const std::unique_ptr<ModelBuffer>& mb : _model_buffers)
        {
            mb->draw();
        }

        // Render the Scene //
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, width, height);

        glDrawBuffer(GL_FRONT);

        // Sets the clear color.
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClearDepth(1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDepthMask(GL_FALSE);

        glUseProgram(_skybox_shader_program);

        if (_current_camera < 2)
        {
            _camera_objects[_current_camera]->set_active();
        }
        else
        {
            _preview_cam->set_active();
        }

        _camera_buffer->bind_buffer();

        glBindTexture(GL_TEXTURE_CUBE_MAP, _skybox);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Clears the window using the above color.
        glDrawBuffer(GL_FRONT);
        glDepthMask(GL_TRUE);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_MULTISAMPLE);

        glUseProgram(_phong_shader_program);

        if (_current_camera < 2)
        {
            _camera_objects[_current_camera]->set_active();
        }
        else
        {
            _preview_cam->set_active();
        }

        _camera_buffer->bind_buffer();
        _light_buffer->bind_buffer();

        Vector3 ball_position = Ball::game_ball->get_position();
        MatrixData light_view = (_camera_objects[2]->get_view());
        MatrixData light_projection = (_camera_objects[2]->get_projection());

        glUniform3f(6, ball_position.x(), ball_position.y(), ball_position.z());
        glUniformMatrix4fv(7, 1, GL_FALSE, &light_view.xx);
        glUniformMatrix4fv(8, 1, GL_FALSE, &light_projection.xx);
        glBindTextureUnit(2, _shadow_texture);
        
        for (const std::unique_ptr<ModelBuffer>& mb : _model_buffers)
        {
            glUniform1i(5, mb->get_model()->use_alpha());
            mb->draw();
        }

        glDisable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);
        glDisable(GL_MULTISAMPLE);
    }

    void MyEngine::render_ui()
    {
        glDisable(GL_DEPTH_TEST);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glUseProgram(_gui_shader_program);
        glUniform2f(0, static_cast<float>(width), static_cast<float>(height));

        switch (state)
        {
        case(GameState::Victory):
            _gui_buffers[0]->draw();
            break;
        case(GameState::Defeat):
            _gui_buffers[1]->draw();
            break;
        case(GameState::Paused):
            _gui_buffers[2]->draw();
            break;
        case(GameState::Running):
            break;
        }

        for (int i = 3; i < _gui_buffers.size(); i++)
        {
            _gui_buffers[i]->draw();
        }

        glDisable(GL_BLEND);

        glFinish();
    }


    // Screen Event Methods //
    void MyEngine::on_resize(int width, int height) {
        // Calls the default implementation to set the class variables.
        IApplication::on_resize(width, height);
        // Changes the viewport.
        glViewport(0, 0, width, height);

        for (SceneCameraObject* c : _camera_objects)
        {
            if (c->get_type() == Camera::CameraType::Orthographic)
            {
                my_engine::Vector2 boundaries = my_engine::Camera::orthographic_boundaries
                (
                    c->get_fov(), c->get_eye_position().magnitude(),
                    static_cast<float>(width) / static_cast<float>(height)
                );

                c->set_orthographic(-boundaries.x(), boundaries.x(), -boundaries.y(), boundaries.y(), c->get_near(), c->get_far());
            }
            else
            {
                c->set_perspective(c->get_fov(), static_cast<float>(width), static_cast<float>(height), c->get_near(), c->get_far());
            }
        }

        if (_preview_cam->get_type() == Camera::CameraType::Orthographic)
        {
            my_engine::Vector2 boundaries = my_engine::Camera::orthographic_boundaries
            (
                _preview_cam->get_fov(), _preview_cam->get_distance(),
                static_cast<float>(width) / static_cast<float>(height)
            );

            _preview_cam->set_orthographic(-boundaries.x(), boundaries.x(), -boundaries.y(), boundaries.y(), _preview_cam->get_near(), _preview_cam->get_far());
        }
        else
        {
            _preview_cam->set_perspective(_preview_cam->get_fov(), static_cast<float>(width), static_cast<float>(height), _preview_cam->get_near(), _preview_cam->get_far());
        }
    }

    void MyEngine::on_mouse_move(double x, double y)
    {
        if (_first_move)
        {
            _first_move = false;
            _last_x = x;
            _last_y = y;

            return;
        }

        double x_offset = x - _last_x;
        double y_offset = y - _last_y;

        _last_x = x;
        _last_y = y;

        if (_moving)
        {
            my_engine::Vector3 right = _preview_cam->get_right();
            my_engine::Vector3 up = _preview_cam->get_up();

            float f = my_engine::Camera::move_sensitivity * _preview_cam->get_distance() / 8.f;
            my_engine::Vector3 offset = (right * x_offset + up * y_offset) * f;

            _preview_cam->set_center(_preview_cam->get_center() + offset);
        }

        if (_rotating)
        {
            _preview_cam->set_yaw(_preview_cam->get_yaw() + x_offset * my_engine::Camera::angle_sensitivity);
            _preview_cam->set_pitch(_preview_cam->get_pitch() + y_offset * my_engine::Camera::angle_sensitivity);
        }
    }

    void MyEngine::on_mouse_scroll(double x, double y)
    {
        float offset = y;
        float f = _preview_cam->get_distance() / 8.f;

        _preview_cam->set_distance(std::max(_preview_cam->get_distance() - offset * f, 0.1f));

        if (_preview_cam->get_type() == Camera::CameraType::Orthographic)
        {
            my_engine::Vector2 boundaries = my_engine::Camera::orthographic_boundaries
            (
                my_engine::PI / 3.f, _preview_cam->get_distance(),
                static_cast<float>(width) / static_cast<float>(height)
            );

            _preview_cam->set_orthographic(-boundaries.x(), boundaries.x(), -boundaries.y(), boundaries.y(), 0.01f, 1000.f);
        }
    }

    void MyEngine::on_mouse_button(int button, int action, int mods)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        {
            _rotating = true;
        }
        else
        {
            _rotating = false;
        }

        if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        {
            _moving = true;
        }
        else
        {
            _moving = false;
        }
    }

    void MyEngine::on_key_pressed(int key, int scancode, int action, int mods) {
        if (action == GLFW_PRESS)
        {
            switch (key)
            {
            case GLFW_KEY_KP_1:
                _current_camera = 0;
                break;
            case GLFW_KEY_KP_2:
                _current_camera = 1;
                break;
            case GLFW_KEY_KP_3:
                _current_camera = 2;
                break;
            case GLFW_KEY_RIGHT:
                right_pressed = true;
                break;
            case GLFW_KEY_LEFT:
                left_pressed = true;
                break;
            case GLFW_KEY_UP:
                up_pressed = true;
                break;
            case GLFW_KEY_DOWN:
                down_pressed = true;
                break;
            case GLFW_KEY_SPACE:
                space_pressed = true;
                break;
            case GLFW_KEY_R:
                reset();
                break;
            case GLFW_KEY_P:
                if (state == GameState::Running)
                {
                    time_factor = 0.0f;
                    state = GameState::Paused;
                }
                else if (state == GameState::Paused)
                {
                    time_factor = 1.0f;
                    state = GameState::Running;
                }

                break;
            }
        }

        if (action == GLFW_RELEASE)
        {
            switch (key)
            {
            case GLFW_KEY_RIGHT:
                right_pressed = false;
                break;
            case GLFW_KEY_LEFT:
                left_pressed = false;
                break;
            case GLFW_KEY_UP:
                up_pressed = false;
                break;
            case GLFW_KEY_DOWN:
                down_pressed = false;
                break;
            }
        }
    }


    // Instantiation methods //
    void MyEngine::instantiate(SceneObject* scene_object, SceneObjectElement::SceneObjectType type)
    {
        my_engine._scene_objects.push_back(std::make_unique<SceneObjectElement>());
        my_engine._scene_objects.back()->type = type;
        my_engine._scene_objects.back()->scene_object = std::unique_ptr<SceneObject>(scene_object);

        switch (type)
        {
        case SceneObjectElement::SceneObjectType::CameraObject:
        {
            my_engine._scene_objects.back()->index = my_engine._camera_objects.size();

            SceneCameraObject* camera = static_cast<SceneCameraObject*>(my_engine._scene_objects.back()->scene_object.get());
            camera->set_buffer(my_engine._camera_buffer.get());
            camera->set_active();

            my_engine._camera_objects.push_back(static_cast<SceneCameraObject*>(my_engine._scene_objects.back()->scene_object.get()));

            break;
        }
        case SceneObjectElement::SceneObjectType::ModelObject:
        {
            my_engine._scene_objects.back()->index = my_engine._model_objects.size();

            my_engine._model_buffers.push_back(std::make_unique<ModelBuffer>());
            SceneModelObject* model = static_cast<SceneModelObject*>(my_engine._scene_objects.back()->scene_object.get());
            model->set_buffer(my_engine._model_buffers.back().get());

            my_engine._model_objects.push_back(model);

            break;
        }
        case SceneObjectElement::SceneObjectType::BallPhysicsObject:
        {
            my_engine._scene_objects.back()->index = my_engine._ball_physics_objects.size();

            my_engine._model_buffers.push_back(std::make_unique<ModelBuffer>());
            SceneBallPhysicsObject* ball = static_cast<SceneBallPhysicsObject*>(my_engine._scene_objects.back()->scene_object.get());
            ball->set_buffer(my_engine._model_buffers.back().get());

            my_engine._ball_physics_objects.push_back(ball);

            break;
        }
        case SceneObjectElement::SceneObjectType::PaddlePhysicsObject:
        {
            my_engine._scene_objects.back()->index = my_engine._paddle_physics_objects.size();

            my_engine._model_buffers.push_back(std::make_unique<ModelBuffer>());
            ScenePaddlePhysicsObject* paddle = static_cast<ScenePaddlePhysicsObject*>(my_engine._scene_objects.back()->scene_object.get());
            paddle->set_buffer(my_engine._model_buffers.back().get());

            my_engine._paddle_physics_objects.push_back(paddle);

            break;
        }
        case SceneObjectElement::SceneObjectType::GUIObject:
        {
            my_engine._scene_objects.back()->index = my_engine._gui_objects.size();

            my_engine._gui_buffers.push_back(std::make_unique<ModelBuffer>());
            SceneGUIObject* gui = static_cast<SceneGUIObject*>(my_engine._scene_objects.back()->scene_object.get());
            gui->set_buffer(my_engine._gui_buffers.back().get());

            my_engine._gui_objects.push_back(gui);

            break;
        }
        case SceneObjectElement::SceneObjectType::LightObject:
        {
            my_engine._scene_objects.back()->index = my_engine._light_objects.size();

            SceneLightObject* light = static_cast<SceneLightObject*>(my_engine._scene_objects.back()->scene_object.get());
            light->set_buffer(my_engine._light_buffer.get());
            my_engine._light_buffer->add_light(light);

            my_engine._light_objects.push_back(light);

            break;
        }
        }
    }


    // Instantioation at the End of the Update //
    void MyEngine::to_instantiate(SceneObject* scene_object, SceneObjectElement::SceneObjectType type)
    {
        my_engine._to_be_instantiated.push_back({ scene_object, type });
    }

    void MyEngine::instantiate_camera(const Vector3& position, const Vector3& direction, float fov, float width, float height, float near, float far, Camera::CameraType type)
    {
        _scene_objects.push_back(std::make_unique<SceneObjectElement>());
        _scene_objects.back()->index = _camera_objects.size();
        _scene_objects.back()->type = SceneObjectElement::SceneObjectType::CameraObject;
        _scene_objects.back()->scene_object = std::make_unique<SceneCameraObject>
        (
            position, Vector3(1.0f), Quaternion(),
            Camera(position, direction, fov, width, height, near, far, type)
        );

        SceneCameraObject* camera = static_cast<SceneCameraObject*>(_scene_objects.back()->scene_object.get());
        camera->set_buffer(_camera_buffer.get());
        camera->set_active();

        _camera_objects.push_back(static_cast<SceneCameraObject*>(_scene_objects.back()->scene_object.get()));
    }

    void MyEngine::instantiate_ball(const Vector3& position, float scale, const Vector3& direction, float velocity, float bounce_factor, size_t level)
    {
        _scene_objects.push_back(std::make_unique<SceneObjectElement>());
        _scene_objects.back()->index = _ball_physics_objects.size();
        _scene_objects.back()->type = SceneObjectElement::SceneObjectType::BallPhysicsObject;
        _scene_objects.back()->scene_object = std::make_unique<SceneBallPhysicsObject>
        (
            position, Vector3(scale), Quaternion(), Mesh::ball(level), Material::DEFAULT_MATERIAL, 0, direction, velocity, bounce_factor, scale * 0.5f
        );

        _model_buffers.push_back(std::make_unique<ModelBuffer>());
        SceneBallPhysicsObject* ball = static_cast<SceneBallPhysicsObject*>(_scene_objects.back()->scene_object.get());
        ball->set_buffer(_model_buffers.back().get());

        _ball_physics_objects.push_back(ball);
    }

    void MyEngine::instantiate_paddle(const Vector3& position, float scale, size_t level, float angle, float width, float height)
    {
        _scene_objects.push_back(std::make_unique<SceneObjectElement>());
        _scene_objects.back()->index = _paddle_physics_objects.size();
        _scene_objects.back()->type = SceneObjectElement::SceneObjectType::PaddlePhysicsObject;
        _scene_objects.back()->scene_object = std::make_unique<ScenePaddlePhysicsObject>
        (
            position, scale, Mesh::paddle(level, angle, width, height), Material::DEFAULT_MATERIAL, 0, Vector3::FORWARD, 0.0f, 0.0f, angle, width
        );

        _model_buffers.push_back(std::make_unique<ModelBuffer>());
        ScenePaddlePhysicsObject* paddle = static_cast<ScenePaddlePhysicsObject*>(_scene_objects.back()->scene_object.get());
        paddle->set_buffer(_model_buffers.back().get());

        _paddle_physics_objects.push_back(paddle);
    }

    void MyEngine::instantiate_model(const Vector3& position, const Vector3& scale, const Quaternion& rotation, Mesh mesh)
    {
        _scene_objects.push_back(std::make_unique<SceneObjectElement>());
        _scene_objects.back()->index = _model_objects.size();
        _scene_objects.back()->type = SceneObjectElement::SceneObjectType::ModelObject;
        _scene_objects.back()->scene_object = std::make_unique<SceneModelObject>
        (
            position, scale, rotation, mesh, Material::DEFAULT_MATERIAL, 0
        );

        _model_buffers.push_back(std::make_unique<ModelBuffer>());
        SceneModelObject* model = static_cast<SceneModelObject*>(_scene_objects.back()->scene_object.get());
        model->set_buffer(_model_buffers.back().get());

        _model_objects.push_back(model);
    }

    void MyEngine::instantiate_directional_light(const Vector3& direction, const Vector3& attenuation, const Vector3& ambient, const Vector3& diffuse, const Vector3& specular)
    {
        _scene_objects.push_back(std::make_unique<SceneObjectElement>());
        _scene_objects.back()->index = _light_objects.size();
        _scene_objects.back()->type = SceneObjectElement::SceneObjectType::LightObject;
        _scene_objects.back()->scene_object = std::make_unique<SceneLightObject>
        (
            -direction, Vector3(1.0f), Quaternion(),
            Light(Vector4(-direction, 0.0f), Vector4(attenuation, 0.0f), Vector4(ambient, 1.0f), Vector4(diffuse, 1.0f), Vector4(specular, 1.0f))
        );

        SceneLightObject* light = static_cast<SceneLightObject*>(_scene_objects.back()->scene_object.get());
        light->set_buffer(_light_buffer.get());
        _light_buffer->add_light(light);

        _light_objects.push_back(light);
    }

    void MyEngine::instantiate_point_light(const Vector3& position, const Vector3& attenuation, const Vector3& ambient, const Vector3& diffuse, const Vector3& specular, float radius)
    {
        _scene_objects.push_back(std::make_unique<SceneObjectElement>());
        _scene_objects.back()->index = _light_objects.size();
        _scene_objects.back()->type = SceneObjectElement::SceneObjectType::LightObject;
        _scene_objects.back()->scene_object = std::make_unique<SceneLightObject>
        (
            position, Vector3(1.0f), Quaternion(),
            Light(Vector4(position, 1.0f), Vector4(attenuation, radius), Vector4(ambient, 1.0f), Vector4(diffuse, 1.0f), Vector4(specular, 1.0f))
        );

        SceneLightObject* light = static_cast<SceneLightObject*>(_scene_objects.back()->scene_object.get());
        light->set_buffer(_light_buffer.get());
        _light_buffer->add_light(light);

        _light_objects.push_back(light);
    }

    void MyEngine::instantiate_gui_object(const Vector2& min, const Vector2& max, const Vector2& uv_min, const Vector2& uv_max, const Vector2& anchor, GLuint texture)
    {
        _scene_objects.push_back(std::make_unique<SceneObjectElement>());
        _scene_objects.back()->index = _gui_objects.size();
        _scene_objects.back()->type = SceneObjectElement::SceneObjectType::GUIObject;
        _scene_objects.back()->scene_object = std::make_unique<SceneGUIObject>
        (
            min, max, uv_min, uv_max, anchor, texture
        );

        _gui_buffers.push_back(std::make_unique<ModelBuffer>());
        SceneGUIObject* gui = static_cast<SceneGUIObject*>(_scene_objects.back()->scene_object.get());
        gui->set_buffer(_gui_buffers.back().get());

        _gui_objects.push_back(gui);
    }


    // Destroy Scene Object at a Given Index //
    void MyEngine::destroy_scene_object(size_t index)
    {
        switch (my_engine._scene_objects[index]->type)
        {
        case SceneObjectElement::SceneObjectType::CameraObject:
            my_engine._camera_objects.erase(my_engine._camera_objects.begin() + my_engine._scene_objects[index]->index);
            my_engine._scene_objects[index]->scene_object.reset();
            my_engine._scene_objects.erase(my_engine._scene_objects.begin() + index);

            for (size_t i = index; i < my_engine._scene_objects.size(); i++)
            {
                if (my_engine._scene_objects[i]->type == SceneObjectElement::SceneObjectType::CameraObject)
                {
                    my_engine._scene_objects[i]->index--;
                }
            }

            break;
        case SceneObjectElement::SceneObjectType::ModelObject:
            my_engine.destroy_model_buffer(my_engine._model_buffers, &my_engine._model_objects[my_engine._scene_objects[index]->index]->get_buffer());
            my_engine._model_objects.erase(my_engine._model_objects.begin() + my_engine._scene_objects[index]->index);
            my_engine._scene_objects[index]->scene_object.reset();
            my_engine._scene_objects.erase(my_engine._scene_objects.begin() + index);

            for (size_t i = index; i < my_engine._scene_objects.size(); i++)
            {
                if (my_engine._scene_objects[i]->type == SceneObjectElement::SceneObjectType::ModelObject)
                {
                    my_engine._scene_objects[i]->index--;
                }
            }

            break;
        case SceneObjectElement::SceneObjectType::BallPhysicsObject:
            my_engine.destroy_model_buffer(my_engine._model_buffers, &my_engine._ball_physics_objects[my_engine._scene_objects[index]->index]->get_buffer());
            my_engine._ball_physics_objects.erase(my_engine._ball_physics_objects.begin() + my_engine._scene_objects[index]->index);
            my_engine._scene_objects[index]->scene_object.reset();
            my_engine._scene_objects.erase(my_engine._scene_objects.begin() + index);

            for (size_t i = index; i < my_engine._scene_objects.size(); i++)
            {
                if (my_engine._scene_objects[i]->type == SceneObjectElement::SceneObjectType::BallPhysicsObject)
                {
                    my_engine._scene_objects[i]->index--;
                }
            }

            break;
        case SceneObjectElement::SceneObjectType::PaddlePhysicsObject:
            my_engine.destroy_model_buffer(my_engine._model_buffers, &my_engine._paddle_physics_objects[my_engine._scene_objects[index]->index]->get_buffer());
            my_engine._paddle_physics_objects.erase(my_engine._paddle_physics_objects.begin() + my_engine._scene_objects[index]->index);
            my_engine._scene_objects[index]->scene_object.reset();
            my_engine._scene_objects.erase(my_engine._scene_objects.begin() + index);

            for (size_t i = index; i < my_engine._scene_objects.size(); i++)
            {
                if (my_engine._scene_objects[i]->type == SceneObjectElement::SceneObjectType::PaddlePhysicsObject)
                {
                    my_engine._scene_objects[i]->index--;
                }
            }

            break;
        case SceneObjectElement::SceneObjectType::GUIObject:
            my_engine.destroy_model_buffer(my_engine._gui_buffers, &my_engine._gui_objects[my_engine._scene_objects[index]->index]->get_buffer());
            my_engine._gui_objects.erase(my_engine._gui_objects.begin() + my_engine._scene_objects[index]->index);
            my_engine._scene_objects[index]->scene_object.reset();
            my_engine._scene_objects.erase(my_engine._scene_objects.begin() + index);

            for (size_t i = index; i < my_engine._scene_objects.size(); i++)
            {
                if (my_engine._scene_objects[i]->type == SceneObjectElement::SceneObjectType::GUIObject)
                {
                    my_engine._scene_objects[i]->index--;
                }
            }

            break;
        case SceneObjectElement::SceneObjectType::LightObject:
            my_engine._light_objects.erase(my_engine._light_objects.begin() + my_engine._scene_objects[index]->index);
            my_engine._light_buffer->remove_light(my_engine._scene_objects[index]->index);
            my_engine._scene_objects[index]->scene_object.reset();
            my_engine._scene_objects.erase(my_engine._scene_objects.begin() + index);

            for (size_t i = index; i < my_engine._scene_objects.size(); i++)
            {
                if (my_engine._scene_objects[i]->type == SceneObjectElement::SceneObjectType::LightObject)
                {
                    my_engine._scene_objects[i]->index--;
                }
            }

            break;
        }
    }

    void MyEngine::destroy_model_buffer(std::vector<std::unique_ptr<ModelBuffer>>& buffers, ModelBuffer* buffer)
    {
        size_t index = 0;

        while (index < buffers.size() && buffers[index].get() != buffer)
        {
            index++;
        }

        if (index < buffers.size())
        {
            buffers.erase(buffers.begin() + index);
        }
    }


    // Static Methods //
    GLuint MyEngine::load_shader(std::filesystem::path const& path, GLenum const shader_type)
    {
        std::filesystem::path const current = std::filesystem::current_path();
        GLuint const shader = glCreateShader(shader_type);
        std::ifstream ifs(path);
        assert(ifs.is_open());
        std::string const str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        char const* code = str.c_str();

        glShaderSource(shader, 1, &code, nullptr);
        glCompileShader(shader);
        return shader;
    }

    GLuint MyEngine::create_program(GLuint const  vertex_shader, GLuint const  fragment_shader)
    {
        GLuint const  shader_program = glCreateProgram();

        glAttachShader(shader_program, vertex_shader);
        glAttachShader(shader_program, fragment_shader);
        glLinkProgram(shader_program);
        glDetachShader(shader_program, vertex_shader);
        glDetachShader(shader_program, fragment_shader);

        return shader_program;
    }

    GLuint MyEngine::load_texture(std::filesystem::path const& path)
    {
        std::vector<unsigned char> texels;
        unsigned int width, height;
        unsigned int error_code = lodepng::decode(texels, width, height, path.string(), LCT_RGBA);
        assert(error_code == 0);

        //flip the image vertically
        for (unsigned int lo = 0, hi = height - 1; lo < hi; ++lo, --hi)
            for (unsigned int* lo_ptr = (unsigned int*)texels.data() + lo * width,
                *lo_end = lo_ptr + width,
                *hi_ptr = (unsigned int*)texels.data() + hi * width;
                lo_ptr != lo_end; ++lo_ptr, ++hi_ptr)
                std::swap(*lo_ptr, *hi_ptr);

        GLuint texture;

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)texels.data());
        glGenerateMipmap(GL_TEXTURE_2D);

        glTextureParameteri(texture, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(texture, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        return texture;
    }
}