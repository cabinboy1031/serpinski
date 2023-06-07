#include "engine/Renderer/Interface.hpp"

using namespace Violet;

Interface::Interface(flecs::world &world, Violet::Renderer2D &renderer){
    this->UIUpdate = world.entity().add(flecs::Phase).depends_on(flecs::OnUpdate);
    this->UIDraw = world.entity().add(flecs::Phase).depends_on(renderer.Render);

}