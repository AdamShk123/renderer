#ifndef LINUX_RENDERER_HPP
#define LINUX_RENDERER_HPP

#include <stdexcept>
#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

#include <SDL3/SDL.h>

#include "interface_renderer.hpp"

namespace Renderer
{

    class LinuxRenderer : public IRenderer
    {
    public:
        LinuxRenderer();
        ~LinuxRenderer() override;

        void drawTriangle() override;
    private:
    };
}

#endif // LINUX_RENDERER_HPP