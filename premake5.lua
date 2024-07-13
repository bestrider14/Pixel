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

include "Pixel/vendor/GLFW"

project "Pixel"
    location "Pixel"
    kind "SharedLib"
    language "C++"

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
        "%{IncludeDir.GLFW}"
    }

    links
    {
        "GLFW",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "PX_PLATFORM_WINDOWS",
            "PX_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/SandBox")
        }

    filter "configurations:Debug"
        defines "PX_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "PX_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "PX_DIST"
        optimize "On"

project "SandBox"
    location "SandBox"
    kind "ConsoleApp"
    language "C++"

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
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "PX_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "PX_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "PX_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "PX_DIST"
        optimize "On"
