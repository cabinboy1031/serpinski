#pragma once
#include <flecs.h>
#include <engine/Renderer/Renderer2D.hpp>

namespace Violet{

    // UI Phases
    struct UIUpdate {};
    struct UIDraw {};

    class Interface {
public: 
        Interface(flecs::world& world);
        
        flecs::entity m_update;
        flecs::entity m_preDraw;
        flecs::entity m_draw;
        flecs::entity m_postDraw;
private:
};
}