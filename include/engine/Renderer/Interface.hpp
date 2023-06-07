#pragma once
#include <flecs.h>
#include "Renderer2D.hpp"

namespace Violet{
    class Interface {
public: 
        Interface(flecs::world&, Violet::Renderer2D&);
        
        flecs::entity UIUpdate;
        flecs::entity UIDraw;
private:
};
}