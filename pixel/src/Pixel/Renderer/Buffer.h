#pragma once

namespace Pixel
{
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType p_Type)
	{
		switch (p_Type)
		{
			case Pixel::ShaderDataType::Float:	return 4;
			case Pixel::ShaderDataType::Float2:	return 4 * 2;
			case Pixel::ShaderDataType::Float3:	return 4 * 3;	
			case Pixel::ShaderDataType::Float4:	return 4 * 4;
			case Pixel::ShaderDataType::Mat3:	return 4 * 3 * 3;
			case Pixel::ShaderDataType::Mat4:	return 4 * 4 * 4;
			case Pixel::ShaderDataType::Int:	return 4;
			case Pixel::ShaderDataType::Int2:	return 4 * 2;
			case Pixel::ShaderDataType::Int3:	return 4 * 3;
			case Pixel::ShaderDataType::Int4:	return 4 * 4;
			case Pixel::ShaderDataType::Bool:	return 1;
		}

		PX_CORE_ASSERT(false, "Unknow ShaderDataType!");
		return 0;
	}
	
	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		BufferElement(ShaderDataType p_Type, const std::string& p_Name, bool p_Normalized = false)
			: Name(p_Name), Type(p_Type), Size(ShaderDataTypeSize(p_Type)), Offset(0), Normalized(p_Normalized)
		{

		}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
				case Pixel::ShaderDataType::Float:	return 1;
				case Pixel::ShaderDataType::Float2:	return 2;
				case Pixel::ShaderDataType::Float3: return 3;
				case Pixel::ShaderDataType::Float4:	return 4;
				case Pixel::ShaderDataType::Mat3:	return 3 * 3;
				case Pixel::ShaderDataType::Mat4:	return 4 * 4;
				case Pixel::ShaderDataType::Int:	return 1;
				case Pixel::ShaderDataType::Int2:	return 2;
				case Pixel::ShaderDataType::Int3:	return 3;
				case Pixel::ShaderDataType::Int4:	return 4;
				case Pixel::ShaderDataType::Bool:	return 1;
			}

			PX_CORE_ASSERT(false, "Unknow Element Count!");
			return 0;
		}
	};
	
	class BufferLayout
	{
	public:
		BufferLayout() {}
		
		BufferLayout(const std::initializer_list<BufferElement>& p_Element)
			: m_Elements(p_Element)
		{
			CalculateOffsetAndStride();
		}

		inline uint32_t GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		void CalculateOffsetAndStride()
		{
			uint32_t offset = 0;
			m_Stride = 0;

			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}

		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetData(const void* p_data, uint32_t p_Size) = 0;
		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& p_Layout) = 0;


		static Ref<VertexBuffer> Create(uint32_t p_Size);
		static Ref<VertexBuffer> Create(float* p_Vertices, uint32_t p_Size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static Ref<IndexBuffer> Create(uint32_t* p_Indices, uint32_t p_Count);
	};

}// Pixel