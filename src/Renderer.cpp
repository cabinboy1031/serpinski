#include<engine/Renderer/Renderer2D.hpp>
using namespace Violet;

Renderer2D::Renderer2D(flecs::world &world){
    world.module<Renderer2D>("Renderer2D");

    m_preRender = world.component<PreRender>()
        .add(flecs::Phase)
        .depends_on(flecs::OnStore);
    m_Render = world.component<Render>()
        .add(flecs::Phase)
        .depends_on<PreRender>();
    m_postRender = world.component<PostRender>()
        .add(flecs::Phase)
        .depends_on<Render>();
    
    
    m_renderStart = world.system()
        .kind<PreRender>()
        .iter([](flecs::iter &it){
            BeginDrawing();
            ClearBackground(BLACK);
        });


    m_renderEnd = world.system()
        .kind<PostRender>()
        .iter([](flecs::iter &it){
            EndDrawing();
        });
}