#ifndef WINDOWS_RENDERER_HPP
#define WINDOWS_RENDERER_HPP

#if _WIN32
#elif __linux__
#endif

#include <stdexcept>
#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <array>

#include <SDL3/SDL.h>

#include <dxgi1_6.h>
#include <wrl/client.h>
#include <d3d11_4.h>
#include <windows.h>
#include <D3DCompiler.h>

#include "interface_renderer.hpp"

namespace Renderer
{
    //struct Color
    //{
    //    uint8_t r;
    //    uint8_t g;
    //    uint8_t b;
    //    uint8_t a;
    //};

    struct Vertex
    {
        std::array<float,3> position;
        std::array<float,3> color;
    };

    constexpr std::array<Vertex,3> vertexBufferData{ {
        {{1.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{-1.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
        {{0.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}}
    } };

    constexpr std::string_view WINDOW_TITLE = "Renderer";
    constexpr unsigned int WINDOW_WIDTH = 800;
    constexpr unsigned int WINDOW_HEIGHT = 600;

    inline void CheckIfFailed(HRESULT result, const std::string& message)
    {
        if (result != S_OK)
        {
            throw std::runtime_error(message);
        }
    }

    class WindowsRenderer : public IRenderer
	{
	public:
		WindowsRenderer();
		~WindowsRenderer() override;

        void drawTriangle() override;

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
        Microsoft::WRL::ComPtr<ID3D11Debug> m_debug = nullptr;
        Microsoft::WRL::ComPtr<IDXGISwapChain4> m_swap = nullptr;
        Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView = nullptr;
        Microsoft::WRL::ComPtr<ID3D11Texture2D> m_backbufferTex = nullptr;
        Microsoft::WRL::ComPtr<ID3D11Texture2D> m_depthStencilBuffer = nullptr;
        Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView = nullptr;
        Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthStencilState = nullptr;
        Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer = nullptr;
        Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer = nullptr;

        void initSDL();
        void createFactory();
        void findAdapter();
        void createDevice();
        void createSwapChain();
        void createRenderViewTarget();
        void createVertexBuffer();
        void createIndexBuffer();
	};
}

#endif // WINDOWS_RENDERER_HPP