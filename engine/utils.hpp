#pragma once

#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cassert>

// error handling
static void glClearError();
static void glCheckError();

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
