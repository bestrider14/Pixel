#pragma once

#ifdef PX_PLATFORM_WINDOWS
	#ifdef PX_BUILD_DLL
		#define PIXEL_API __declspec(dllexport)
	#else
		#define PIXEL_API __declspec(dllimport)
	#endif
#else
	#error Pixel only supports Windows !
#endif

#define BIT(x) (1 << x)