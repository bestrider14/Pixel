#include "pxpch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Pixel
{
	OrthographicCamera::OrthographicCamera(float p_Left, float p_Right, float p_Bottom, float p_Top)
		: m_ProjectionMatrix(glm::ortho(p_Left, p_Right, p_Bottom, p_Top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::SetProjection(float p_Left, float p_Right, float p_Bottom, float p_Top)
	{
		m_ProjectionMatrix = glm::ortho(p_Left, p_Right, p_Bottom, p_Top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}// namespace Pixel