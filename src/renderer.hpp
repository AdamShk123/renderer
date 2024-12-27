#ifndef RENDERER_HPP
#define RENDERER_HPP

#if _WIN32
#elif __linux__
#endif

#include <stdexcept>
#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

#include <SDL3/SDL.h>

#include <dxgi1_6.h>
#include <wrl/client.h>
#include <d3d11_4.h>
#include <windows.h>
#include <D3DCompiler.h>

namespace Renderer
{
    //struct Color
    //{
    //    uint8_t r;
    //    uint8_t g;
    //    uint8_t b;
    //    uint8_t a;
    //};

	class Renderer
	{
	public:
		Renderer();
		~Renderer();

        //void setDrawColor(const Color& color);
        //void clear() const;
        //void present() const;
    private:
		SDL_Window* m_window = nullptr;

        HWND m_handle = nullptr;

        Microsoft::WRL::ComPtr<IDXGIFactory7> m_factory = nullptr;
        Microsoft::WRL::ComPtr<IDXGIAdapter4> m_adapter = nullptr;
        Microsoft::WRL::ComPtr<ID3D11Device5> m_device = nullptr;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext4> m_context = nullptr;

        void initSDL();
        void createFactory();
        void findAdapter();
        void createDevice();
	};
}

#endif // RENDERER_HPP