#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <stdexcept>

#include <SDL3/SDL.h>

namespace Renderer
{
    struct Color
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };

	class Renderer
	{
	public:
		Renderer();
		~Renderer();

        void setDrawColor(const Color& color);
        void clear() const;
        void present() const;
    private:
		SDL_Window* m_window = nullptr;
        SDL_Renderer* m_renderer = nullptr;
	};
}

#endif // RENDERER_HPP