#include <stdio.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/DefaultLogger.hpp>

#include "engine/components/component.cpp"

int main()
{

    SoraComponent::ComponentHandler chandler;
    SoraComponent::Component obj;
    chandler.add_component(&obj);
    SoraComponent::Component anota;
    chandler.add_component(&anota);

    for (int i = 0; i < 2; i++)
    {
        printf("Comp: %s | %llu\n", chandler.get_at(i)->get_name().c_str(), chandler.get_at(i)->get_id());
    }
    printf("End\n");

    return 0;
}