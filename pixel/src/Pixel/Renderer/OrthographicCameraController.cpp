#include "pxpch.h"
#include "OrthographicCameraController.h"

#include "Pixel/Core/Input.h"
#include "Pixel/Core/KeyCode.h"

namespace Pixel
{
	OrthographicCameraController::OrthographicCameraController(float p_AspectRatio, bool p_Rotation)
		:m_AspectRatio(p_AspectRatio), m_Rotation(p_Rotation), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
	{

	}

	void OrthographicCameraController::OnUpdate(Timestep p_Timestep)
	{
		PX_PROFILE_FUNCTION();
		
		if (Input::IsKeyPressed(PX_KEY_A))
			m_CameraPosition.x -= m_CameraTranslationSpeed * p_Timestep;

		if (Input::IsKeyPressed(PX_KEY_D))
			m_CameraPosition.x += m_CameraTranslationSpeed * p_Timestep;

		if (Pixel::Input::IsKeyPressed(PX_KEY_W))
			m_CameraPosition.y += m_CameraTranslationSpeed * p_Timestep;

		if (Input::IsKeyPressed(PX_KEY_S))
			m_CameraPosition.y -= m_CameraTranslationSpeed * p_Timestep;

		m_Camera.SetPosition(m_CameraPosition);

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(PX_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * p_Timestep;

			if (Input::IsKeyPressed(PX_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * p_Timestep;

			m_Camera.SetRotation(m_CameraRotation);
		}	

		m_CameraTranslationSpeed = m_ZoomLevel * 2.0f;
	}

	void OrthographicCameraController::OnEvent(Event& p_Event)
	{
		PX_PROFILE_FUNCTION();

		EventDispatcher dispatcher(p_Event);
		dispatcher.Dispatch<MouseScrolledEvent>(PX_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(PX_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& p_Event)
	{
		PX_PROFILE_FUNCTION();

		m_ZoomLevel -= p_Event.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& p_Event)
	{
		PX_PROFILE_FUNCTION();

		m_AspectRatio = (float)p_Event.GetWidth() / (float)p_Event.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
}// namespace Pixel