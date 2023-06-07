#include <engine/Renderer/Interface.hpp>

using namespace Violet;

Interface::Interface(flecs::world &world){
    world.module<Interface>();
    world.import<Renderer2D>();

    m_update = world.component<UIUpdate>()
        .add(flecs::Phase)
        .depends_on(flecs::OnUpdate);
    m_draw = world.component<UIDraw>()
        .add(flecs::Phase)
        .depends_on<Render>();
}