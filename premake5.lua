workspace "Pixel"
    architecture "x64"
    startproject "SandBox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Pixel/vendor/GLFW/include"
IncludeDir["Glad"] = "Pixel/vendor/GLAD/include"
IncludeDir["ImGui"] = "Pixel/vendor/imgui"
IncludeDir["glm"] = "Pixel/vendor/glm"
IncludeDir["stb_image"] = "Pixel/vendor/stb_image"

group "Dependencies"
	include "Pixel/vendor/GLFW"
	include "Pixel/vendor/Glad"
	include "Pixel/vendor/imgui"

group ""

project "Pixel"
    location "Pixel"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
	staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
    pchheader "pxpch.h"
    pchsource "Pixel/src/pxpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/stb_image/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"
    }

    links
    {
        "GLFW",
		"Glad",
		"ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "PX_PLATFORM_WINDOWS",
            "PX_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "PX_DEBUG"
		runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "PX_RELEASE"
		runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "PX_DIST"
		runtime "Release"
        optimize "on"

project "SandBox"
    location "SandBox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
	staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Pixel/vendor/spdlog/include",
        "Pixel/src",
        "Pixel/vendor",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Pixel"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "PX_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "PX_DEBUG"
		runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "PX_RELEASE"
		runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "PX_DIST"
		runtime "Release"
        optimize "on"