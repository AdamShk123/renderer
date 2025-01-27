#include "linux_renderer.hpp"

namespace Renderer 
{
	LinuxRenderer::LinuxRenderer()
	{
        const auto metadataResult = SDL_SetAppMetadata("Renderer", "1.0.0", "com.example.renderer");

        if (!metadataResult)
        {
            throw std::runtime_error(SDL_GetError());
        }

        const auto initResult = SDL_Init(SDL_INIT_VIDEO);

        if (!initResult)
        {
            throw std::runtime_error(SDL_GetError());
        }

        constexpr auto windowFlags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

        m_window = SDL_CreateWindow(
                WINDOW_TITLE.data(),
                WINDOW_WIDTH,
                WINDOW_HEIGHT,
                windowFlags
        );

        if (m_window == nullptr)
        {
            throw std::runtime_error(SDL_GetError());
        }

        m_context = SDL_GL_CreateContext(m_window);

        if (m_context == nullptr)
        {
            throw std::runtime_error(SDL_GetError());
        }

        if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        {
            throw std::runtime_error("Failed to initialize GLAD");
        }
	}

	LinuxRenderer::~LinuxRenderer()
	{
        SDL_GL_DestroyContext(m_context);
        m_context = nullptr;

        SDL_DestroyWindow(m_window);
        m_window = nullptr;
	}

	void LinuxRenderer::drawTriangle()
	{

	}

    void LinuxRenderer::clear()
    {
        glClearColor(m_color.r, m_color.g, m_color.b, m_color.a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void LinuxRenderer::present()
    {
        SDL_GL_SwapWindow(m_window);
    }
}