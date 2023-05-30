#include<iostream>
#include<raylib.h>
#include<raymath.h>
#include<flecs.h>

#include<engine/Renderer/Renderer2D.hpp>

class Position2D {
public:
    Vector2 vec;
};

class Velocity2D {
public:
    Vector2 vec;
};

int main(int argc, char *argv[]){
    InitWindow(800, 800, "Test window");
    flecs::world world(argc,argv);
    Violet::Renderer2D renderer(world);

    flecs::entity e = world.entity("TestEntity");
    e.set<Position2D>({(float)800/2, (float)800/2});
    e.set<Velocity2D>({.01,.01});

    std::cout << "Entity name: " << e.name() << std::endl;
  
    flecs::system sys = world.system<Position2D, const Velocity2D>("Move")
        .kind(flecs::OnUpdate)
        .each([](Position2D &p, const Velocity2D &v) {
            p.vec = Vector2Add(p.vec, v.vec);
        });

    flecs::system DrawCircle = world.system<Position2D, Velocity2D>()
        .kind(Violet::Renderer2D::Render)
        .each([](Position2D &p, Velocity2D &v){
            DrawCircleV(p.vec, 50, MAROON);
        });
    
    while(!WindowShouldClose() && world.progress()){}

    CloseWindow();
}