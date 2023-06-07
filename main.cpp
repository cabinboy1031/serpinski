#include<iostream>
#include<vector>

#include<raylib.h>
#include<raymath.h>
#include<flecs.h>

#include<engine/Renderer/Renderer2D.hpp>
#include<engine/Renderer/Interface.hpp>
#include<Triangle.hpp>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

Vector2 center_point(Vector2 a, Vector2 b){
    return Vector2Scale(Vector2Add(a, b), .5);
}

std::vector<Triangle2D> triangle_split(Triangle2D& t){
    Vector2 np1 = center_point(t.p1, t.p2);
    Vector2 np2 = center_point(t.p1, t.p3);
    Vector2 np3 = center_point(t.p2, t.p3);
    
    std::vector<Triangle2D> nt = {
        {t.p1, np1, np2},
        {np1, t.p2, np3},
        {np2, np3, t.p3}
    };
    
    return nt;
}

int main(int argc, char *argv[]){
    int width = 800;
    int height = 800;
    InitWindow(width, height, "Test window");
    flecs::world world(argc,argv);
    world.import<Violet::Renderer2D>();
    world.import<Violet::Interface>();

    flecs::entity e = world.entity("TestEntity");
    e.set<Triangle2D>({
        {(float)width/2, 100}, 
        {(float)100,(float)height - 100}, 
        {(float)width - 100,(float)height - 100}});

    std::cout << "Entity name: " << e.name() << std::endl;
  
    TriangleSystemSetup(world);
    
    world.system<Triangle2D>("TriangleSplitTest")
        .kind<Violet::Render>()
        .interval(1)
        .iter([](flecs::iter &it,Triangle2D *t){
            for(auto i: it){
                std::vector<Triangle2D> new_triangles = triangle_split(t[i]);
                it.entity(i).destruct();
                it.world().entity().set<Triangle2D>(new_triangles[0]);
                it.world().entity().set<Triangle2D>(new_triangles[1]);
                it.world().entity().set<Triangle2D>(new_triangles[2]);
            }
        });
    
    world.system()
        .kind<Violet::PostRender>()
        .interval(1)
        .iter([](flecs::iter &it){
            std::cout << it.world().count<Triangle2D>() << std::endl;
        });
    
    
    world.system("DrawUITest")
        .kind<Violet::UIDraw>()
        .iter([](flecs::iter &it){
            GuiWindowBox({500, 400, 100,100}, "Test Box!");
        });
    
    while(!WindowShouldClose() && world.progress()){}

    CloseWindow();
}