-- premake5.lua

-- Constructed from repository "ProjectTemplate" by Yan "TheCherno" Chernikov
-- https://github.com/TheCherno/ProjectTemplate

workspace "GrusGrus"
    architecture "x64"
    configurations {"Debug", "Release"}
    startproject "App"

    filter "system:windows"
        buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

    OutputDir = "%{cfg.system}-%{vfg.architecture}/%{cfg.buildcfg}"

project "App"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    targetdir "bin/%{cfg.buildcfg}"
    staticruntime "off"

    files { "src/**.h", "src/**.cpp" }

    includedirs {"src"}

    targetdir ("bin/" .. OutputDir)
    objdir ("bin/ints/" .. OutputDir)

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