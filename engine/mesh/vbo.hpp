#include <GL/glew.h>

#include <vector>

#include "attribute.cpp"
#include "buffer_object.cpp"

namespace Sora
{

    class VBO
    {
    private:
        std::vector<Sora::Attribute> attribs;

    public:
        VBO();
        ~VBO();

        void create();
        void add_attribute(Sora::Attribute attrib);
        void enable_attribs();
        void disable_attribs();
    };

}