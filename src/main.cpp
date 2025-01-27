#include <SDL3/SDL_main.h>
#include "main.hpp"

int main(int argc, char* argv[])
{
	std::cout << "Argument Count: " << argc << std::endl;

	for(int i = 0; i < argc; i++)
	{
		std::cout << argv[i] << std::endl;
	}

	#if _WIN32
		std::unique_ptr<Renderer::IRenderer> renderer = std::make_unique<Renderer::WindowsRenderer>();
	#elif __linux__
		std::unique_ptr<Renderer::IRenderer> renderer = std::make_unique<Renderer::LinuxRenderer>();
	#endif

	run(renderer);

	std::cout << "Goodbye World!" << std::endl;

	return 0;
}

void run(std::unique_ptr<Renderer::IRenderer>& renderer)
{
	bool done = false;

	SDL_Event event;

	uint64_t start = 0;
	uint64_t last = 0;

	while(!done)
	{
		start = SDL_GetTicks();

		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_EVENT_QUIT)
			{
				done = true;
			}
		}

        Renderer::Color color{0xB0, 0xB0, 0xB0, 0xFF};
        renderer->setColor(color);

        renderer->clear();

        renderer->present();

		last = SDL_GetTicks();

        double fps = 1000.0 / static_cast<double>(last - start);
		std::cout << "FPS: " << fps << std::endl;
	}
}