#include "Renderer.h"
#include <iostream>

namespace Renderer {

	//------------------------------
	// SDL_INIT
	//------------------------------
	int SDL_INIT(SDL_Window** window, SDL_Renderer** renderer) {
		SDL_Init(SDL_INIT_VIDEO);
		*window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
		if (window == nullptr) {
			std::cerr << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
			SDL_Quit();
			return 1;
		}

		*renderer = SDL_CreateRenderer(*window, NULL);
		if (*renderer == nullptr) {
			std::cerr << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
			SDL_DestroyWindow(*window);
			SDL_Quit();
			return 2;
		}
		return 0;

		std::cout << IMGUI_VERSION << std::endl;
		IMGUI_CHECKVERSION();
	}

	//------------------------------
	// ImGui_SDL_3_Init
	//------------------------------
	int ImGui_SDL3_Init(ImGuiIO* io, SDL_Window** window, SDL_Renderer** renderer) {
		ImGui::CreateContext();
		*io = ImGui::GetIO();

		ImGui::StyleColorsDark();

		ImGui_ImplSDL3_InitForSDLRenderer(*window, *renderer);
		ImGui_ImplSDLRenderer3_Init(*renderer);

		return 0;
	}

	//------------------------------
	// ImGui_SDL3_Init
	//------------------------------
	int ImGui_SDL3_Init(ImGuiIO* io, SDL_Window** window, SDL_Renderer** renderer, ImGuiColorScheme colorScheme) {
		ImGui::CreateContext();
		*io = ImGui::GetIO();

		switch (colorScheme) {
			case Classic:	ImGui::StyleColorsClassic();	break;
			case Dark:		ImGui::StyleColorsDark();		break;
			case Light:		ImGui::StyleColorsLight();		break;
		}

		ImGui_ImplSDL3_InitForSDLRenderer(*window, *renderer);
		ImGui_ImplSDLRenderer3_Init(*renderer);

		return 0;
	}

	//------------------------------
	// ImGui_SDL3_PollEvent
	//------------------------------
	int ImGui_SDL3_PollEvent(SDL_Event* e, bool* quit) {
		while (SDL_PollEvent(e)) {
			ImGui_ImplSDL3_ProcessEvent(e);
			if (e->type == SDL_EVENT_QUIT) {
				*quit = true;
			}
		}
	}

	//------------------------------
	// ImGui_SDL3_NewFrame
	//------------------------------
	int ImGui_SDL3_NewFrame() {
		ImGui_ImplSDLRenderer3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		ImGui::NewFrame();
	}

	//------------------------------
	// SDL_Render
	//------------------------------
	int SDL_Render(SDL_Renderer** renderer, ImGuiIO* io, ImVec4* clear_color) {
		SDL_SetRenderScale(*renderer, io->DisplayFramebufferScale.x, io->DisplayFramebufferScale.y);
		SDL_SetRenderDrawColorFloat(*renderer, clear_color->x, clear_color->y, clear_color->z, clear_color->w);
		SDL_RenderClear(*renderer);
		ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), *renderer);
		SDL_RenderPresent(*renderer);

		return 0;
	}

	//------------------------------
	// ImGui_SDL3_ShutDown
	//------------------------------
	int ImGui_SDL3_ShutDown(SDL_Window** window, SDL_Renderer** renderer) {
		ImGui_ImplSDLRenderer3_Shutdown();
		ImGui_ImplSDL3_Shutdown();
		ImGui::DestroyContext();

		SDL_DestroyRenderer(*renderer);
		SDL_DestroyWindow(*window);
		SDL_Quit();
	}

}