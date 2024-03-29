#pragma once
#include <raylib.h>
#include <raymath.h>
#include <flecs.h>
#include <vector>
#include <engine/Renderer/Renderer2D.hpp>

class Triangle2D {
public:
    Vector2 p1, p2, p3;
};


void TriangleSystemSetup(flecs::world &world){
    world.import<Violet::Renderer2D>();
    world.system<Triangle2D>("TriangleDrawTest")
        .kind<Violet::Render>()
        .each([](Triangle2D &t){
            DrawTriangle(t.p1, t.p2, t.p3,MAROON);
        });
}