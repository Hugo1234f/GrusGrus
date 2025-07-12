-- premake5.lua

-- Constructed from repository "ProjectTemplate" by Yan "TheCherno" Chernikov
-- https://github.com/TheCherno/ProjectTemplate

workspace "GrusGrus"
    architecture "x64"
    configurations {"Debug", "Release"}
    startproject "App"

    filter "system:windows"
        buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus", "/utf-8" }

    OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"
    SDLDir = "Dependencies/SDL3/SDL3-3.2.12"

project "App"
    location "App"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    targetdir "bin/%{cfg.buildcfg}"
    staticruntime "off"

    

    files { 
        "App/src/**.h", "App/src/**.cpp", 
        "Dependencies/imgui/imgui.cpp",
        "Dependencies/imgui/imgui_draw.cpp",
        "Dependencies/imgui/imgui_tables.cpp",
        "Dependencies/imgui/imgui_widgets.cpp",
        "Dependencies/imgui/imgui_demo.cpp",

        "Dependencies/imgui/backends/imgui_impl_sdl3.cpp",
        "Dependencies/imgui/backends/imgui_impl_sdlrenderer3.cpp" 
    }

    includedirs {
        "App/src", 
        "Stork/src", 
        "Dependencies",
        SDLDir .. "/include",
        "Dependencies/imgui",
        "Dependencies/imgui/backends" 
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

    local SDL3_DLL_SRC = path.join(SDLDir, "lib", "SDL3.dll")
    local SDL3_DLL_DST = path.join("bin", OutputDir, "SDL3.dll")
    postbuildcommands {
        '{COPYFILE} "' .. SDL3_DLL_SRC .. '" "' .. SDL3_DLL_DST '"' 
    }

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