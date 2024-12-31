#ifndef INTERFACE_RENDERER_HPP
#define INTERFACE_RENDERER_HPP

namespace Renderer 
{
	class IRenderer 
	{
	public:
		IRenderer() = default;
		virtual ~IRenderer() = default;
		
		virtual void drawTriangle() = 0;
	private:
	};
}

#endif