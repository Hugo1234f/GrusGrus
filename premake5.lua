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

project "App"
    location "App"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    targetdir "bin/%{cfg.buildcfg}"
    staticruntime "off"

    files { "App/src/**.h", "App/src/**.cpp" }

    includedirs {"App/src", "Stork/src"}

    links { "Stork" }

    targetdir ("bin/" .. OutputDir)
    objdir ("bin-ints/" .. OutputDir)

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

    files {"Stork/src/**.h", "Stork/src/**.cpp"}

    includedirs { "Stork/src", "App/src" }

    defines { "STORK" }

    targetdir ("bin/" .. OutputDir)
    objdir ("bin-ints/" .. OutputDir)

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