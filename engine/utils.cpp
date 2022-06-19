#include "utils.hpp"

// error handling
static void glClearError()
{
    while (glGetError() != GL_NO_ERROR)
        ;
}

static void glCheckError()
{
    while (GLenum error = glGetError())
    {
        std::cout << "OPENGL ERROR: (" << error << ")" << std::endl;
    }
}

SoraIO::File::File(const char *path) : path(path)
{
    // get file size
    this->s_file.open(path, std::ios::binary | std::ios::ate);
    this->char_count = s_file.tellg();
    this->s_file.close();

    this->r_file.open(path);
    if (!this->r_file || !r_file.is_open())
    {
        std::cout << "[SoraIO][utils.cpp] Could not open up the file at `" << path << "`!" << std::endl;
        assert(!"[SoraIO][utils.cpp] Could not open file!");
    }
    // just have the file open to read from!
}

SoraIO::File::~File()
{
    this->clean();
}

bool SoraIO::File::has_next_line()
{
    return (bool)getline(this->r_file, this->line);
}

std::string SoraIO::File::next_line()
{
    /*Returned strings do not include '\n' character at end!*/
    return this->line;
}

void SoraIO::File::clean()
{
    this->s_file.close();
    this->r_file.close();
}
