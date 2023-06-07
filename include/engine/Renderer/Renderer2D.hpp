#pragma once
#include<iostream>
#include<raylib.h>
#include<raymath.h>
#include<flecs.h>

namespace Violet {

    // Renderer Phases
    struct PreRender {};
    struct Render {};
    struct PostRender {};

    // Render Module Class
    class Renderer2D {
        public:
            Renderer2D(flecs::world &world);
            
            ~Renderer2D() = default;

            
            flecs::entity m_preRender;
            flecs::entity m_Render;
            flecs::entity m_postRender;
            flecs::entity m_renderStart;
            flecs::entity m_renderEnd;
    };
};