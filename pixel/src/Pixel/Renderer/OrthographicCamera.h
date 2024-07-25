#pragma once

#include <glm/glm.hpp>

namespace Pixel
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float p_Left, float p_Right, float p_Bottom, float p_Top);

		const inline glm::vec3 GetPosition() const { return m_Position; }
		inline void SetPosition(const glm::vec3& p_Postion) { m_Position = p_Postion; RecalculateViewMatrix(); }

		const inline float GetRotation() const { return m_Rotation; }
		inline void SetRotation(float p_Rotation) { m_Rotation = p_Rotation; RecalculateViewMatrix(); }

		const glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4 GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
	};
}// namespace Pixel