#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <stdexcept>

#include <SDL3/SDL.h>

namespace Renderer
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();
	private:
		SDL_Window* m_window = nullptr;
	};
}

#endif // RENDERER_HPP