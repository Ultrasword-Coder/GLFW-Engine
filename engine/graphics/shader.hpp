#pragma once

#include <string>

typedef unsigned int uint;

namespace Sora
{
    const std::string VERT_SECTION = "#vertex", FRAG_SECTION = "#fragment";
    const uint FRAGTYPE = 0, VERTTYPE = 1;

    class Shader
    {
    private:
        const char *filepath;
        std::string vert_shader, frag_shader;
        uint program;

    public:
        Shader(const char *);
        ~Shader();

        void set_shader_code(std::string, std::string);
        void create();
        void clean();
        void bind();
        void unbind();

        uint compile_shader(uint, const char *);

        // uniform setters
        void uploadBool(const char *, bool) const;
        void uploadInt(const char *, int) const;
        void uploadFloat(const char *, float) const;

        // implement matrix uploading and others

        // ---- static methods --- //
    };

    static Sora::Shader load_shader_from_file(const char *filepath);
}