#include "Renderer.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "misc/stb_image.h"

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

		return 0;
	}

	//------------------------------
	// ImGui_SDL3_NewFrame
	//------------------------------
	int ImGui_SDL3_NewFrame() {
		ImGui_ImplSDLRenderer3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		ImGui::NewFrame();

		return 0;
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

		return 0;
	}

	//------------------------------
	// LoadTextureFromMemory
	//------------------------------
	int SDL3_LoadTextureFromMemory(const void* data, size_t data_size, SDL_Renderer* renderer, SDL_Texture** out_texture, int* out_width, int* out_height) {
		int image_width = 0;
		int image_height = 0;
		int channels = 4;
		unsigned char* image_data = stbi_load_from_memory((const unsigned char*)data, (int)data_size, &image_width, &image_height, NULL, 4);
		if (image_data == nullptr)
		{
			fprintf(stderr, "Failed to load image: %s\n", stbi_failure_reason());
			return 1;
		}

		SDL_Surface* surface = SDL_CreateSurfaceFrom(image_width, image_height, SDL_PIXELFORMAT_RGBA32, (void*)image_data, channels * image_width);
		if (surface == nullptr)
		{
			fprintf(stderr, "Failed to create SDL surface: %s\n", SDL_GetError());
			return 2;
		}

		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture == nullptr)
			fprintf(stderr, "Failed to create SDL texture: %s\n", SDL_GetError());

		*out_texture = texture;
		*out_width = image_width;
		*out_height = image_height;

		SDL_DestroySurface(surface);
		stbi_image_free(image_data);

		return 0;
	}

	// Open and read a file, then forward to LoadTextureFromMemory()
	int SDL3_LoadTextureFromFile(const char* file_name, SDL_Renderer* renderer, SDL_Texture** out_texture, int* out_width, int* out_height)
	{
		FILE* f = fopen(file_name, "rb");
		if (f == NULL)
			return false;
		fseek(f, 0, SEEK_END);
		size_t file_size = (size_t)ftell(f);
		if (file_size == -1)
			return false;
		fseek(f, 0, SEEK_SET);
		void* file_data = IM_ALLOC(file_size);
		fread(file_data, 1, file_size, f);
		fclose(f);
		bool ret = !SDL3_LoadTextureFromMemory(file_data, file_size, renderer, out_texture, out_width, out_height);
		IM_FREE(file_data);
		return ret;
	}

}