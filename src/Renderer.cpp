#include <engine/Renderer/Renderer2D.hpp>

using namespace Violet;

Renderer2D::Renderer2D(flecs::world &world){
    this->PreRender  = world.entity().add(flecs::Phase).depends_on(flecs::OnStore);
    this->Render     = world.entity().add(flecs::Phase).depends_on(this->PreRender);
    this->PostRender = world.entity().add(flecs::Phase).depends_on(this->Render);
    
    
    flecs::system RenderStart = world.system()
        .kind(PreRender)
        .iter([](flecs::iter &it){
            BeginDrawing();
            ClearBackground(BLACK);
        });


    flecs::system RenderEnd = world.system()
        .kind(PostRender)
        .iter([](flecs::iter &it){
            EndDrawing();
        });
}