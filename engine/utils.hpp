#pragma once

#include <GL/glew.h>
#include <GLM/glm.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
#include <iomanip>

// error handling
static void glClearError();
static void glCheckError();

static void glErrorCallback(int, const char *);

void set_io_floating_precision(int precision)
{
    std::cout << std::setprecision(precision);
}

namespace SoraIO
{
    /*
        Holds classes to read files
        - these object are only supposed to be temporary
    */

    class File
    {
    private:
        const char *path;
        int char_count;
        std::ifstream r_file, s_file;

        std::string line;

    public:
        File(const char *path);
        ~File();

        bool has_next_line();
        std::string next_line();
        void clean();
    };

}

namespace GLMUtils
{
    void output_vec2(glm::vec2);
    void output_vec3(glm::vec3);
    void output_vec4(glm::vec4);
    void output_mat2(glm::mat2);
    void output_mat3(glm::mat3);
    void output_mat4(glm::mat4);

}
