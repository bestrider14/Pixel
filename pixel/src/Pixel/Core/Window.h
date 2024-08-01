#pragma once

#include "pxpch.h"

#include "Pixel/Core/Core.h"
#include "Pixel/Events/Event.h"

namespace Pixel
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& p_title = "Pixel Engine",
			unsigned int p_width = 1280,
			unsigned int p_height = 720)
		: Title(p_title), Width(p_width), Height(p_height){}

	};

	// Interface representing a desktop system base Window
	class  Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window(){}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		//Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}// namespace Pixel