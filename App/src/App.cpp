#include <iostream>

#include "Stork.h"
#include "App.h"
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include "Widgets.h"

#include "SDL3/SDL.h"

#define WINDOW_NAME "GrusGrus"


ICAOtoDromeNameStruct ICAOtoDromeName[] {
		{"ESCF", "Linköping/Malmen"},
	{"ESCM", "Uppsala-Ärna"},
	{"ESDF", "Ronneby Airport"},
	{"ESGG", "Göteborg/Landvetter"},
	{"ESGJ", "Jönköping Airport"},
	{"ESGT", "Trollhättan/Vänersborg"},
	{"ESGP", "Göteborg/Säve"},
	{"ESIA", "Karlsborg"},
	{"ESIB", "Såtenäs"},
	{"ESKM", "Mora/Siljan"},
	{"ESKN", "Stockholm/Skavsta"},
	{"ESKS", "Sälen/Scandinavian Mountains"},
	{"ESMK", "Kristianstad"},
	{"ESMQ", "Kalmar"},
	{"ESMS", "Malmö"},
	{"ESMT", "Halmstad"},
	{"ESMX", "Växjö/Kronoberg"},
	{"ESND", "Sveg"},
	{"ESNG", "Gällivare"},
	{"ESNK", "Kramfors-Sollefteå"},
	{"ESNL", "Lycksele"},
	{"ESNN", "Sundsvall-Timrå"},
	{"ESNO", "Örnsköldsvik"},
	{"ESNQ", "Kiruna"},
	{"ESNS", "Skellefteå"},
	{"ESNU", "Umeå"},
	{"ESNV", "Vilhelmina"},
	{"ESNX", "Arvidsjaur"},
	{"ESNZ", "Åre Östersund"},
	{"ESOE", "Örebro"},
	{"ESOK", "Karlstad"},
	{"ESOH", "Hagfors"},
	{"ESOW", "Stockholm/Västerås"},
	{"ESPA", "Luleå/Kallax"},
	{"ESPE", "Vidsel"},
	{"ESSA", "Stockholm/Arlanda"},
	{"ESSB", "Stockholm/Bromma"},
	{"ESSD", "Borlänge"},
	{"ESSL", "Linköping/SaaB"},
	{"ESSP", "Norrköping/Kungsängen"},
	{"ESST", "Torsby"},
	{"ESSV", "Visby"},
	{"ESTA", "Ängelholm"},
	{"ESTL", "Ljungbyhed"},
	{"ESUP", "Pajala"},
	{"ESUT", "Hemavan Tärnaby"}
};
const int ICAOtoDromeNameCount = sizeof(ICAOtoDromeName) / sizeof(ICAOtoDromeNameStruct);


int main() {
	std::cout << "Hello App!" << std::endl;

	Stork::Print();
	widgets::Widgets widgets;
	widgets.setMetarData(Stork::getData());
	//Stork::TestPy();
	//Stork::AD_Data adData = Stork::getData();
	

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("GrusGrus App",1920, 1080, SDL_WINDOW_RESIZABLE);
	if (window == nullptr) {
		std::cerr << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
	if (renderer == nullptr) {
		std::cerr << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	std::cout << IMGUI_VERSION << std::endl;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_DockingEnable;

	ImGui::StyleColorsDark();

	ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer3_Init(renderer);

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	bool show_demo_window;

	SDL_Event e;
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			ImGui_ImplSDL3_ProcessEvent(&e);
			if (e.type == SDL_EVENT_QUIT) {
				quit = true;
			}
		}

		ImGui_ImplSDLRenderer3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		ImGui::NewFrame();


		ImGui::ShowDemoWindow(&show_demo_window);
		widgets.drawSidePanel();

		ImGui::Render();
		SDL_SetRenderScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
		SDL_SetRenderDrawColorFloat(renderer, clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		SDL_RenderClear(renderer);
		ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
		SDL_RenderPresent(renderer);


		if (widgets.getRefresh()) {
			widgets.setMetarData(Stork::getData());
			widgets.setRefresh(false);
		}
	}

	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}