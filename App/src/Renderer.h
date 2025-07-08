#pragma once

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include "SDL3/SDL.h"

// Defines
#define WINDOW_WIDTH	1920
#define WINDOW_HEIGHT	1080
#define WINDOW_TITLE	"GrusGrus App"


namespace Renderer {

	//------------------------------
	// ImGui Color Schemes
	//------------------------------

	enum ImGuiColorScheme {
		Classic,
		Dark,
		Light
	};

	//------------------------------
	// SDL
	//------------------------------

	int SDL_INIT(SDL_Window** window, SDL_Renderer** renderer);
	
	int ImGui_SDL3_Init(ImGuiIO* io, SDL_Window** window, SDL_Renderer** renderer);
	int ImGui_SDL3_Init(ImGuiIO* io, SDL_Window** window, SDL_Renderer** renderer, ImGuiColorScheme	colorScheme);
	
	int ImGui_SDL3_PollEvent(SDL_Event*	e, bool* quit);
	
	int ImGui_SDL3_NewFrame();
	
	int SDL_Render(SDL_Renderer** renderer,	ImGuiIO* io, ImVec4* clear_color);
	
	int ImGui_SDL3_ShutDown(SDL_Window** window, SDL_Renderer**	renderer);

	//------------------------------

	int SDL3_LoadTextureFromMemory(const void* data, size_t data_size, SDL_Renderer* renderer, SDL_Texture** out_texture, int* width, int* height);
	int SDL3_LoadTextureFromFile(const char* file_name, SDL_Renderer* renderer, SDL_Texture** out_texture, int* out_width, int* out_height);
}

