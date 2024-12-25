#include "renderer.hpp"

namespace Renderer 
{
	Renderer::Renderer() 
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


		constexpr auto windowFlags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE);

		m_window = SDL_CreateWindow(
			"Renderer",
			800,
			600,
			windowFlags
		);

		if (m_window == nullptr)
		{
			throw std::runtime_error(SDL_GetError());
		}
	}

	Renderer::~Renderer()
	{
		SDL_DestroyWindow(m_window);
		m_window = nullptr;

		SDL_Quit();
	}
}