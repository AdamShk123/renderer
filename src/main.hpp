#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <cstdint>

#if _WIN32
	#include "windows_renderer.hpp"
#elif __linux__
	#include "linux_renderer.hpp"
#endif

void run(std::unique_ptr<Renderer::IRenderer>& renderer);

#endif // MAIN_HPP