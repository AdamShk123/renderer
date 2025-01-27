#ifndef INTERFACE_RENDERER_HPP
#define INTERFACE_RENDERER_HPP

namespace Renderer 
{
    struct Color
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };

	class IRenderer 
	{
	public:
		IRenderer() = default;
		virtual ~IRenderer() = default;
		
		virtual void drawTriangle() = 0;
        virtual void clear() = 0;
        virtual void present() = 0;

        void setColor(const Color& color)
        {
            m_color = color;
        }
    protected:
        Color m_color{};
	private:
	};
}

#endif