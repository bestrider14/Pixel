#pragma once

#include "Pixel/Renderer/OrthographicCamera.h"
#include "Pixel/Core/Timestep.h"

#include "Pixel/Events/ApplicationEvent.h"
#include "Pixel/Events/MouseEvent.h"

namespace Pixel
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float p_AspectRatio, bool p_Rotation = false);

		inline OrthographicCamera& GetCamera() { return m_Camera; }
		inline const OrthographicCamera& GetCamera() const { return m_Camera; }

		inline float GetZoomLevel() { return m_ZoomLevel; }
		inline void SetZoomLevel(float p_ZoomLevel) { m_ZoomLevel = p_ZoomLevel; }

		void OnUpdate(Timestep p_Timestep);
		void OnEvent(Event& p_Event);

	private:
		bool OnMouseScrolled(MouseScrolledEvent& p_Event);
		bool OnWindowResized(WindowResizeEvent& p_Event);

		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 8.0f, m_CameraRotationSpeed = 180.0f;
		bool m_Rotation;
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		OrthographicCamera m_Camera;
	};
}// namespace Pixel