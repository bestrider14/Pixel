#pragma once

#include "Event.h"

namespace Pixel 
{
	class PIXEL_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent(int p_KeyCode)
			: m_KeyCode(p_KeyCode){}

		int m_KeyCode;
	};

	class PIXEL_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int p_KeyCode, int p_RepeatCount)
			: KeyEvent(p_KeyCode), m_RepeatCount(p_RepeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class PIXEL_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int p_KeyCode)
			: KeyEvent(p_KeyCode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}// Namespace Pixel