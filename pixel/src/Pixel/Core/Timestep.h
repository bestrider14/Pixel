#pragma once

namespace Pixel
{
	class Timestep
	{
	public:
		Timestep(float p_Time = 0.0f)
			: m_Time(p_Time){}

		operator float() const { return m_Time; }

		float GetSeconds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000.0f; }
	private:
		float m_Time;
	};
}// namespace Pixel