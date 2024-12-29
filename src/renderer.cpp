#include "renderer.hpp"

using Microsoft::WRL::ComPtr;

namespace Renderer 
{
	Renderer::Renderer() 
	{
		initSDL();
		createFactory();
		findAdapter();
		createDevice();
		createSwapChain();
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
			WINDOW_TITLE.data(),
			WINDOW_WIDTH,
			WINDOW_HEIGHT,
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

		auto result = CreateDXGIFactory2(createFactoryFlags, __uuidof(m_factory), (void**)m_factory.ReleaseAndGetAddressOf());

		CheckIfFailed(result, "Failed to create factory!");
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

		if(adapters.empty())
		{
			throw std::runtime_error("No adapters found!");
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
		adapters[index]->QueryInterface(m_adapter.GetAddressOf());

		// releases remaining adapters
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
		std::array<D3D_FEATURE_LEVEL, 7> featureLevelInputs{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1
		};

		D3D_FEATURE_LEVEL featureLevelOutputs = featureLevelInputs[0];

		unsigned int flags = D3D11_CREATE_DEVICE_SINGLETHREADED;

		#ifdef _DEBUG
			flags |= D3D11_CREATE_DEVICE_DEBUG;
		#endif // _DEBUG

		ComPtr<ID3D11Device> device = nullptr;
		ComPtr<ID3D11DeviceContext> context = nullptr;

		auto createDeviceResult = D3D11CreateDevice(
			m_adapter.Get(),
			D3D_DRIVER_TYPE_UNKNOWN,
			nullptr,
			flags,
			featureLevelInputs.data(),
			static_cast<unsigned int>(featureLevelInputs.size()),
			D3D11_SDK_VERSION,
			device.GetAddressOf(),
			&featureLevelOutputs,
			context.GetAddressOf()
		);

		CheckIfFailed(createDeviceResult, "Failed to create device!");

		CheckIfFailed(device.As(&m_device), "Failed to convert interface!");
		CheckIfFailed(context.As(&m_context), "Failed to convert interface!");

		#ifdef _DEBUG
		m_device->QueryInterface(__uuidof(ID3D11Debug), &m_debug);
		#endif
	}

	void Renderer::createSwapChain() 
	{
		DXGI_SWAP_CHAIN_DESC swapChainDesc{};
		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferDesc.Width = WINDOW_WIDTH;
		swapChainDesc.BufferDesc.Height = WINDOW_HEIGHT;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = m_handle;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.Windowed = TRUE;

		ComPtr<IDXGISwapChain> temp = nullptr;

		auto createSwapChainResult = m_factory->CreateSwapChain(
			m_device.Get(),
			&swapChainDesc,
			temp.GetAddressOf()
		);

		CheckIfFailed(createSwapChainResult, "Failed to init swap chain!");

		CheckIfFailed(temp.As(&m_swap), "Failed to convert interface!");
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