#pragma once

#include "Pixel/Input.h"

namespace Pixel
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int p_Keycode) override;

		virtual bool IsMouseButtonPressedImpl(int p_Button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};

}// namespace Pixel