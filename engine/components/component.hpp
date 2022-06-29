

namespace Sora
{

    long long component_counter = 0;

    struct Component
    {
        Component();
        ~Component();

        long long id;
        virtual void on_ready();
        virtual void update();
    };

}
