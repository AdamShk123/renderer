#include <SDL3/SDL_main.h>
#include "main.hpp"

int main(int argc, char* argv[])
{
	std::cout << "Argument Count: " << argc << std::endl;

	for(int i = 0; i < argc; i++)
	{
		std::cout << argv[i] << std::endl;
	}

	auto renderer = Renderer::Renderer();

	run(renderer);

	std::cout << "Goodbye World!" << std::endl;

	return 0;
}

void run(Renderer::Renderer& renderer)
{
	std::cout << &renderer << std::endl;

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

        Renderer::Color color{0xD0, 0xD0, 0xD0, 0xFF};
        renderer.setDrawColor(color);
        renderer.clear();
        renderer.present();

		last = SDL_GetTicks();

		double fps = 1000.0 / static_cast<double>(last - start);
		std::cout << "FPS: " << fps << std::endl;
	}
}