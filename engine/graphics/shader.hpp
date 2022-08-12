#pragma once

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include <string>

#include "texture.hpp"

#define INT_ID typeid(int)
#define UINT_ID typeid(uint)
#define FLOAT_ID typeid(float)

typedef unsigned int uint;

namespace Sora
{
    // constant values for shader
    const std::string VERT_SECTION = "#vertex", FRAG_SECTION = "#fragment";
    const uint FRAGTYPE = 0, VERTTYPE = 1;

    class Shader
    {
        /*
            Shader abstraction code :)
            - very pog
         */
    private:
        const char *filepath;
        std::string vert_shader, frag_shader;
        uint program;
        bool created = false;

    public:
        Shader();
        Shader(const char *);
        ~Shader();

        void set_shader_code(std::string, std::string);
        void create();
        void clean();
        void bind();
        void unbind();
        const char *get_file();

        uint compile_shader(uint, const char *);

        // uniform setters
        int uniform_location(const char *) const;
        void uploadBool(const char *, bool) const;
        void uploadInt(const char *, int) const;
        void uploadFloat(const char *, float) const;
        void uploadTexture2D(const char *, Sora::Texture2D *tex) const;

        // implement matrix uploading and others
        void uploadVec2(const char *, glm::vec2);
        void uploadVec3(const char *, glm::vec3);
        void uploadVec4(const char *, glm::vec4);

        void uploadMat2(const char *, glm::mat2);
        void uploadMat3(const char *, glm::mat3);
        void uploadMat4(const char *, glm::mat4);

        void uploadIntArray(const char *, int count, int *values);
        void uploadUIntArray(const char *, int count, uint *values);

        // upload given position
        template <typename T>
        void uploadValue(int pos, T value) const;
    };

    static Sora::Shader load_shader_from_file(const char *filepath);
}