#pragma once
#include<iostream>
#include<raylib.h>
#include<raymath.h>
#include<flecs.h>

namespace Violet {
    class Renderer2D {
        public:
            Renderer2D(flecs::world &world);
            
            ~Renderer2D() = default;

            // Renderer Phases
            flecs::entity PreRender;
            flecs::entity Render;
            flecs::entity PostRender;
    };
};