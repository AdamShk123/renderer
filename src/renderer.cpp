#include "renderer.hpp"

namespace Renderer 
{
	Renderer::Renderer() 
	{
		initSDL();
		createFactory();
		findAdapter();
	}

	void Renderer::initSDL() 
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

		m_handle = (HWND)SDL_GetPointerProperty(SDL_GetWindowProperties(m_window), SDL_PROP_WINDOW_WIN32_HWND_POINTER, NULL);

		if (m_handle == nullptr)
		{
			throw std::runtime_error("Faile to retrieve window handle!");
		}
	}

	void Renderer::createFactory() 
	{
		#ifndef _DEBUG
				constexpr unsigned int createFactoryFlags = 0;
		#else
				constexpr unsigned int createFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;
		#endif

		auto createFactoryResult = CreateDXGIFactory2(createFactoryFlags, __uuidof(m_factory), (void**)m_factory.ReleaseAndGetAddressOf());

		if (createFactoryResult != S_OK)
		{
			throw std::runtime_error("Failed to create factory!");
		}
	}

	void Renderer::findAdapter() 
	{
		std::vector<IDXGIAdapter1*> adapters{};

		unsigned int i = 0;
		IDXGIAdapter1* adapter = nullptr;

		// finds all available adapters
		while (m_factory.Get()->EnumAdapters1(i, &adapter) != DXGI_ERROR_NOT_FOUND)
		{
			adapters.push_back(adapter);
			i += 1;
		}

		std::vector<DXGI_ADAPTER_DESC1> descriptions(adapters.size());

		auto getDescription = [](IDXGIAdapter1* adapter) -> DXGI_ADAPTER_DESC1
		{
			DXGI_ADAPTER_DESC1 description{};
			adapter->GetDesc1(&description);
			return description;
		};

		// maps new vector with adapter descriptions
		std::transform(adapters.begin(), adapters.end(), descriptions.begin(), getDescription);

		auto biggerMemory = [](const DXGI_ADAPTER_DESC1& a, const DXGI_ADAPTER_DESC1& b) -> bool
		{
			return a.DedicatedVideoMemory < b.DedicatedVideoMemory;
		};

		// finds adapter with most video memory
		auto best = std::max_element(descriptions.begin(), descriptions.end(), biggerMemory);
		auto index = std::distance(descriptions.begin(), best);
		m_adapter.Attach(adapters[index]);

		// releases remaining adapters
		adapters.erase(adapters.begin() + index);
		auto release = [](IDXGIAdapter1* adapter) { adapter->Release(); };
		std::for_each(adapters.begin(), adapters.end(), release);
	}

	Renderer::~Renderer()
	{
		SDL_DestroyWindow(m_window);
		m_window = nullptr;

		SDL_Quit();
	}

	void Renderer::createDevice() 
	{
	
	}

    //void Renderer::setDrawColor(const Color& color)
    //{
    //    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    //}

    //void Renderer::clear() const
    //{
    //    SDL_RenderClear(m_renderer);
    //}

    //void Renderer::present() const
    //{
    //    SDL_RenderPresent(m_renderer);
    //}
}