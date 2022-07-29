#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <STB/stb_image.h>
#include <glm/glm.hpp>

#include "engine/engine.hpp"

#include "engine/time.cpp"
#include "engine/utils.cpp"
#include "engine/window.cpp"
#include "engine/input.cpp"

#include "engine/graphics/shader.cpp"
#include "engine/graphics/texture.cpp"
#include "engine/graphics/framebuffer.cpp"

#include "engine/mesh/buffer_object.cpp"
#include "engine/mesh/vao.cpp"

#include "engine/handler/filehandler.cpp"
#include "engine/handler/texuploadhandler.cpp"
#include "engine/handler/vaohandler.cpp"

#include "engine/components/component.cpp"
#include "engine/components/transform.cpp"

#include "engine/objects/camera.cpp"

typedef unsigned int uint;

Sora::Window window;
SoraEngine::Camera3D camera(1280.0f, 720.0f);
glm::vec3 pos = glm::vec3(0.0f, 0.0f, -10.0f);

void init()
{
    // ----- just floating point stuff ------
    set_io_floating_precision(3);
    // --------------------------------------
    Sora::init_engine(Sora::VERY_VERBOSE);
    window.create();
    Sora::init_glew(Sora::VERY_VERBOSE);
    Sora::collect_engine_data(Sora::VERY_VERBOSE);

    // window event callbacks
    glfwSetWindowSizeCallback(Sora::w_instance->window, Sora::Window::window_size_callback);
    glfwSetErrorCallback(glErrorCallback);
    glfwSetKeyCallback(Sora::w_instance->window, Sora::Input::key_callback);
    glfwSetCursorPosCallback(Sora::w_instance->window, Sora::Input::mouse_position_callback);
    glfwSetMouseButtonCallback(Sora::w_instance->window, Sora::Input::mouse_callback);
    glfwSetScrollCallback(Sora::w_instance->window, Sora::Input::mouse_scroll_callback);
}

void update()
{
    if (Sora::Input::is_key_pressed(GLFW_KEY_W))
    {
        // move forward
        pos += camera.get_rdirection() * 5.0f * Sora::Time::delta_time;
        // pos.z -= 5.0f * Sora::Time::delta_time;
    }
    if (Sora::Input::is_key_pressed(GLFW_KEY_S))
    {
        pos += camera.get_rdirection() * -5.0f * Sora::Time::delta_time;
        // pos.z += 5.0f * Sora::Time::delta_time;
    }
    if (Sora::Input::is_key_pressed(GLFW_KEY_A))
    {
        pos += camera.get_left() * 5.0f * Sora::Time::delta_time;
        // pos.x -= 5.0f * Sora::Time::delta_time;
    }
    if (Sora::Input::is_key_pressed(GLFW_KEY_D))
    {
        pos += camera.get_left() * -5.0f * Sora::Time::delta_time;
        // pos.x += 5.0f * Sora::Time::delta_time;
    }
    if (Sora::Input::is_key_pressed(GLFW_KEY_LEFT_SHIFT))
    {
        pos += camera.get_up() * 5.0f * Sora::Time::delta_time;
    }
    if (Sora::Input::is_key_pressed(GLFW_KEY_SPACE))
    {
        pos += camera.get_up() * -5.0f * Sora::Time::delta_time;
    }
}

int main()
{
    init();
    // ----- glm testing ---- //
    camera.set_position(pos);
    camera.set_target(0.0f, 0.0f, 0.0f);
    camera.update_projection();
    camera.calculate_vectors();
    // --- end glm ---- //

    // vertices
    float vertices[] = {
        // positions          // colors           // texture coords
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,   // top right
        0.5f, -0.5f, -0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, -0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f  // top left
    };
    // index stuff
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3};
    // create gigachad
    Sora::Shader *gigachad_shader = Sora::Filehandler::get_shader("assets/shaders/default.glsl");
    gigachad_shader->bind();
    gigachad_shader->uploadMat4("proj", camera.get_proj());
    gigachad_shader->uploadMat4("view", camera.get_view());
    gigachad_shader->unbind();
    Sora::VAO gigachad_vao;
    gigachad_vao.create();
    gigachad_vao.bind();
    gigachad_vao.add_attribute(Sora::create_attribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, 0));
    gigachad_vao.add_attribute(Sora::create_attribute(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 9, sizeof(float) * 3));
    gigachad_vao.add_attribute(Sora::create_attribute(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 9, sizeof(float) * 7));
    Sora::BufferObject<float> gigachad_verts(4 * 9, GL_FLOAT);
    gigachad_verts.create();
    gigachad_verts.bind();
    gigachad_verts.set_data(vertices, 4 * 9);
    gigachad_verts.upload_data();
    Sora::BufferObject<uint> gigachad_inds(4 * 9, GL_UNSIGNED_INT);
    gigachad_inds.create();
    gigachad_inds.bind();
    gigachad_inds.set_data(indices, 6);
    Sora::VAOHandler<float, uint> gigachad = Sora::create_vao_handler(gigachad_vao, gigachad_verts, gigachad_inds);
    gigachad.unbind();
    Sora::TexUploadHandler::TexUpload<Sora::Texture2D> gigachad_texs;
    gigachad_texs.add_texture(Sora::Filehandler::get_texture("assets/images/img1.png"));
    gigachad_texs.add_texture(Sora::Filehandler::get_texture("assets/images/img2.png"));
    // ---- end setup --- //

    // game loop
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    Sora::set_clear_bits(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Sora::set_clear_color(0.6f, 0.0f, 0.2f, 1.0f);
    Sora::Time::start();
    while (!glfwWindowShouldClose(Sora::w_instance->window))
    {
        // clear errors /  flush em out
        glCheckError();
        Sora::set_clear_color(0.6f, 0.0f, 0.2f, 1.0f);
        glClear(Sora::CLEAR_BITS);

        // update call
        update();
        camera.set_position(pos);
        camera.update();

        // ------------- render call ------------- //

        // render gigachad
        gigachad_texs.bind_textures();
        gigachad_shader->bind();
        gigachad_shader->uploadMat4("view", camera.get_view());
        gigachad_shader->uploadFloat("utime", Sora::Time::get_time());
        gigachad_vao.bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
        gigachad_vao.unbind();
        gigachad_shader->unbind();
        gigachad_texs.unbind_textures();
        glCheckError();

        // gigachad render
        // tex_handler.bind_textures();
        // shader->bind();
        // shader->uploadMat4("view", camera.get_view());
        // shader->uploadFloat("utime", Sora::Time::get_time());
        // main_vao.bind();
        // glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
        // main_vao.unbind();
        // shader->unbind();
        // tex_handler.unbind_textures();
        // glCheckError();

        // // render ground
        // glActiveTexture(GL_TEXTURE0);
        // f_tex->bind();
        // f_shader->bind();
        // f_shader->uploadMat4("view", camera.get_view());
        // floor_vao.bind();
        // glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
        // floor_vao.unbind();
        // f_shader->unbind();
        // f_tex->unbind();
        // glCheckError();

        // update window
        window.update();
        Sora::Input::update();
        Sora::Time::update();
    }

    gigachad.clean();
    // main_vao.clean();
    // floor_vao.clean();
    Sora::Filehandler::clean(Sora::VERY_VERBOSE);

    window.clean();
    Sora::clean_engine(Sora::VERY_VERBOSE);
    return 0;
}
