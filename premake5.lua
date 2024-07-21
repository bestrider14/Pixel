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

group "Dependencies"
	include "Pixel/vendor/GLFW"
	include "Pixel/vendor/Glad"
	include "Pixel/vendor/imgui"

group ""

project "Pixel"
    location "Pixel"
    kind "SharedLib"
    language "C++"
	staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
    pchheader "pxpch.h"
    pchsource "Pixel/src/pxpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
    }

    links
    {
        "GLFW",
		"Glad",
		"ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++20"
        systemversion "latest"

        defines
        {
            "PX_PLATFORM_WINDOWS",
            "PX_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/SandBox/\"")
        }

    filter "configurations:Debug"
        defines "PX_DEBUG"
		runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "PX_RELEASE"
		runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "PX_DIST"
		runtime "Release"
        optimize "On"

project "SandBox"
    location "SandBox"
    kind "ConsoleApp"
    language "C++"
	staticruntime "off"

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
        "Pixel/src"
    }

    links
    {
        "Pixel"
    }

    filter "system:windows"
        cppdialect "C++20"
        systemversion "latest"

        defines
        {
            "PX_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "PX_DEBUG"
		runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "PX_RELEASE"
		runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "PX_DIST"
		runtime "Release"
        optimize "On"
