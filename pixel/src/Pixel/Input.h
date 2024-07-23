#pragma once

#include "Pixel/Core.h"

namespace Pixel
{
	class  Input
	{
	public:
		inline static bool IsKeyPressed(int p_Keycode) { return s_Instance->IsKeyPressedImpl(p_Keycode); }

		inline static bool IsMouseButtonPressed(int p_Button) { return s_Instance->IsMouseButtonPressedImpl(p_Button); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int p_Keycode) = 0;

		virtual bool IsMouseButtonPressedImpl(int p_Button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		static Input* s_Instance;
	};
}// namespace Pixel