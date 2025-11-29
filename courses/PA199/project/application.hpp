// ################################################################################
// Common Framework for Computer Graphics Courses at FI MUNI.
//
// Copyright (c) 2021-2022 Visitlab (https://visitlab.fi.muni.cz)
// All rights reserved.
// ################################################################################

#pragma once
#include "iapplication.h"
#include "glad/glad.h"
#include "./my_engine/my_engine.hpp"
#include "./my_game/my_game.hpp"

#include <map>
#include <algorithm>
#include <iostream>

namespace my_engine
{
    struct SceneObjectElement
    {
        enum struct SceneObjectType
        {
            BaseObject,
            CameraObject,
            ModelObject,
            BallPhysicsObject,
            PaddlePhysicsObject,
            GUIObject,
            LightObject
        };


        std::shared_ptr<SceneObject> scene_object = nullptr;
        SceneObjectType type = SceneObjectType::BaseObject;
        size_t index = 0;
    };

    enum struct GameState
    {
        Running,
        Paused,
        Victory,
        Defeat
    };




    class MyEngine : public IApplication
    {
    public:
        static MyEngine my_engine;

    protected:
        // Shadows //
        GLuint _shadow_framebuffer = 0;
        GLuint _shadow_texture = 0;
        GLuint _shadow_texture_size = 2048;
        Vector3 light_position = Vector3(2.0f, 3.0f, 3.0f);

        // Scene Objects //
        std::vector<std::unique_ptr<SceneObjectElement>> _scene_objects;
        std::vector<std::pair<SceneObject*, SceneObjectElement::SceneObjectType>> _to_be_instantiated;

        // Cameras //
        std::unique_ptr<ScenePreviewCameraObject> _preview_cam = nullptr;
        std::vector<SceneCameraObject*> _camera_objects;
        size_t _current_camera = 0;

        // Objects //
        std::vector<SceneModelObject*> _model_objects;
        std::vector<SceneBallPhysicsObject*> _ball_physics_objects;
        std::vector<ScenePaddlePhysicsObject*> _paddle_physics_objects;
        std::vector<SceneGUIObject*> _gui_objects;

        // Textures //
        std::map<std::string, GLuint> _textures;
        GLuint _skybox;

        // Lights //
        std::vector<SceneLightObject*> _light_objects;

        // Buffers //
        std::unique_ptr <CameraBuffer> _camera_buffer = nullptr;
        std::vector<std::unique_ptr<ModelBuffer>> _model_buffers;
        std::vector<std::unique_ptr<ModelBuffer>> _gui_buffers;
        std::unique_ptr <LightBuffer> _light_buffer = nullptr;

        // Phong Shader //
        GLuint _phong_vertex_shader = 0;
        GLuint _phong_fragment_shader = 0;
        GLuint _phong_shader_program = 0;

        // GUI Shader //
        GLuint _gui_vertex_shader = 0;
        GLuint _gui_fragment_shader = 0;
        GLuint _gui_shader_program = 0;

        // Shadow Shader //
        GLuint _shadow_vertex_shader = 0;
        GLuint _shadow_fragment_shader = 0;
        GLuint _shadow_shader_program = 0;

        // Skybox Shader //
        GLuint _skybox_vertex_shader = 0;
        GLuint _skybox_fragment_shader = 0;
        GLuint _skybox_shader_program = 0;

        // Cursor Information //
        double _last_x = 0.f, _last_y = 0.f;
        bool _first_move = true, _rotating = false, _moving = false;

        // Time //
        float _delta_counter = 0.0f;

    public:
        const float fixed_delta = 5.0f;
        float time_factor = 1.0f;

        // Game State //
        GameState state = GameState::Running;

        // Input //
        bool right_pressed = false;
        bool left_pressed = false;
        bool up_pressed = false;
        bool down_pressed = false;
        bool space_pressed = false;

        // Private Constructor //
    protected:
        MyEngine();

    public:
        // Initializator //
        static void initialize_engine(int initial_width, int initial_height, std::vector<std::string> arguments = {});

        void init_framebuffers();
        void init_cameras();
        void init_models();
        void init_lights();
        void init_textures();
        void init_gui();
        void init_game();
        void init_shaders();
        void init_skybox();

        // Destructor //
        virtual ~MyEngine();
        void reset();
        void respawn();
        void clear();

        // Number of Scene Objects //
        static size_t scene_object_count();

        // Get Camera Matrix //
        static Camera::CameraType get_camera_type();
        static GLuint get_texture(const std::string& texture);

        // Update Methods //
        void update(float delta) override;

        // Render Methods //
        void render() override;
        void render_ui() override;

        // Screen Event Methods //
        void on_resize(int width, int height) override;
        void on_mouse_move(double x, double y) override;
        void on_mouse_scroll(double x, double y) override;
        void on_mouse_button(int button, int action, int mods) override;
        void on_key_pressed(int key, int scancode, int action, int mods) override;

        // Instantiation methods //
        static void instantiate(SceneObject* scene_object, SceneObjectElement::SceneObjectType type);

        // Instantioation at the End of the Update //
        static void to_instantiate(SceneObject* scene_object, SceneObjectElement::SceneObjectType type);
        
        void instantiate_camera
        (
            const Vector3& position = Vector3(0.0f), const Vector3& direction = Vector3::FORWARD, float fov = PI / 4.0f,
            float width = 1.0f, float height = 1.0f, float near = 0.01f, float far = 1000.0f,
            Camera::CameraType type = Camera::CameraType::Perspective
        );

        void instantiate_ball
        (
            const Vector3& position = Vector3(0.0f), float scale = 1.0f, const Vector3& direction = Vector3::FORWARD,
            float velocity = 1.0f, float bounce_factor = 1.0f, size_t level = 32
        );

        void instantiate_paddle
        (
            const Vector3& position = Vector3(0.0f), float scale = 1.0f, size_t level = 32,
            float angle = PI / 2.0f, float width = 0.25f, float height = 0.5f
        );

        void instantiate_model
        (
            const Vector3& position = Vector3(0.0f), const Vector3& scale = Vector3(1.0f), const Quaternion& rotation = Quaternion(), Mesh mesh = Mesh()
        );

        void instantiate_directional_light
        (
            const Vector3& direction = Vector3(0.0f), const Vector3& attenuation = Vector3(1.0f, 0.0f, 0.0f),
            const Vector3& ambient = Vector3(0.8f), const Vector3& diffuse = Vector3(0.2f), const Vector3& specular = Vector3(1.0f)
        );

        void instantiate_point_light
        (
            const Vector3& position = Vector3(0.0f), const Vector3& attenuation = Vector3(1.0f, 0.0f, 0.0f),
            const Vector3& ambient = Vector3(0.8f), const Vector3& diffuse = Vector3(0.2f), const Vector3& specular = Vector3(1.0f), float radius = 0.0f
        );

        void instantiate_gui_object(const Vector2& min = Vector2(-1.0f), const Vector2& max = Vector2(1.0f), const Vector2& uv_min = Vector2(0.0f), const Vector2& uv_max = Vector2(1.0f), const Vector2& anchor = Vector2(0.0f), GLuint texture = 0);

        // Destroy Scene Object at a Given Index //
        static void destroy_scene_object(size_t index);
        void destroy_model_buffer(std::vector<std::unique_ptr<ModelBuffer>>& buffers, ModelBuffer* buffer);

        // Static Methods //
        static GLuint load_shader(std::filesystem::path const& path, GLenum const shader_type);
        static GLuint create_program(GLuint const  vertex_shader, GLuint const  fragment_shader);
        static GLuint load_texture(std::filesystem::path const& path);
    };
};