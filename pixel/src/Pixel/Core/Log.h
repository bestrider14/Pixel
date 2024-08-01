#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Pixel 
{
	class  Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}// namespace Pixel

// Core Log macros
#define PX_CORE_TRACE(...)	::Pixel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PX_CORE_INFO(...)	::Pixel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PX_CORE_WARN(...)	::Pixel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PX_CORE_ERROR(...)	::Pixel::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PX_CORE_FATAL(...)	::Pixel::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client Log macros
#define PX_TRACE(...)	::Pixel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PX_INFO(...)	::Pixel::Log::GetClientLogger()->info(__VA_ARGS__)
#define PX_WARN(...)	::Pixel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PX_ERROR(...)	::Pixel::Log::GetClientLogger()->error(__VA_ARGS__)
#define PX_FATAL(...)	::Pixel::Log::GetClientLogger()->fatal(__VA_ARGS__)