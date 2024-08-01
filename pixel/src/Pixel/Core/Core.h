#pragma once

#include <memory>

#ifdef PX_DEBUG
	#define PX_ENABLE_ASSERTS
#endif // PX_DEBUG


#ifdef PX_ENABLE_ASSERTS
	#define PX_ASSERT(x, ...) { if(!(x)) { PX_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define PX_CORE_ASSERT(x, ...) { if(!(x)) { PX_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define PX_ASSERT(x, ...)
	#define PX_CORE_ASSERT(x, ...)
#endif // PX_ENABLE_ASSERTS


#define BIT(x) (1 << x)

#define PX_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Pixel
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}// namespace Pixel