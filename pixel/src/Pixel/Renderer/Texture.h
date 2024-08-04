#pragma once

#include <string>

#include "Pixel/Core/Core.h"

namespace Pixel
{
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t getWidth() const = 0;
		virtual uint32_t getHeight() const = 0;

		virtual void SetData(void* p_Data, uint32_t p_Size) = 0;

		virtual void Bind(uint32_t p_Slot = 0) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(uint32_t p_Width, uint32_t p_Height);
		static Ref<Texture2D> Create(const std::string& p_Path);
	};
}// namespace Pixel