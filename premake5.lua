-- premake5.lua

-- Constructed from repository "ProjectTemplate" by Yan "TheCherno" Chernikov
-- https://github.com/TheCherno/ProjectTemplate

workspace "GrusGrus"
    architecture "x64"
    configurations {"Debug", "Release"}
    startproject "App"

    filter "system:windows"
        buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

    OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"
    SDLDir = "Dependencies/SDL3/SDL3-3.2.12"

project "App"
    location "App"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    targetdir "bin/%{cfg.buildcfg}"
    staticruntime "off"

    files { "App/src/**.h", "App/src/**.cpp" }

    includedirs {
        "App/src", 
        "Stork/src", 
        "Dependencies",
        SDLDir .. "/include", 
    }

    libdirs {
        SDLDir .. "/lib/x64"
    }

    links { 
        "Stork",
        "SDL3.lib" 
    }

    targetdir ("bin/" .. OutputDir)
    objdir ("bin-ints/" .. OutputDir)

    debugdir ("bin/" .. OutputDir)

    filter "system:windows"
        systemversion "latest"
        defines { "WINDOWS" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        runtime "Release"
        optimize "On"
        symbols "Off"

project "Stork"
    location "Stork"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"
    targetdir "bin/%{cfg.buildcfg}"
    staticruntime "off"

    files {"Stork/src/**.h", "Stork/src/**.cpp", "Dependencies/**.h" }

    includedirs { 
        "Stork/src", 
        "App/src", 
        "Dependencies" 
    }

    defines { "STORK" }

    targetdir ("bin/" .. OutputDir)
    objdir ("bin-ints/" .. OutputDir)

    debugdir ("bin/" .. OutputDir)

    filter "system:windows"
        systemversion "latest"
        defines { "WINDOWS" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        runtime "Release"
        optimize "On"
        symbols "Off"