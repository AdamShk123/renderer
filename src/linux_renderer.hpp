#ifndef LINUX_RENDERER_HPP
#define LINUX_RENDERER_HPP

#include <stdexcept>
#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

#include <SDL3/SDL.h>

#include<glad/glad.h>

#include "interface_renderer.hpp"

namespace Renderer
{
    constexpr std::string_view WINDOW_TITLE = "Renderer";
    constexpr unsigned int WINDOW_WIDTH = 800;
    constexpr unsigned int WINDOW_HEIGHT = 600;

    class LinuxRenderer : public IRenderer
    {
    public:
        LinuxRenderer();
        ~LinuxRenderer() override;

        void drawTriangle() override;
        void clear() override;
        void present() override;
    private:
        SDL_Window* m_window = nullptr;
        SDL_GLContext m_context = nullptr;
    };
}

#endif // LINUX_RENDERER_HPP