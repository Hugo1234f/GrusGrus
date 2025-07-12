#include <iostream>

#include "Stork.h"
#include "App.h"
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include "Widgets.h"

#include "SDL3/SDL.h"

#include "Renderer.h"

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

	
	
	//------------------------------
	//Set up window
	//------------------------------

	SDL_Window*		window;
	SDL_Renderer*	renderer;
	Renderer::SDL_INIT(&window, &renderer);

	SDL_Texture* my_texture;
	int my_image_width, my_image_height;
	bool ret = Renderer::SDL3_LoadTextureFromFile("..\\..\\..\\Dependencies\\Sweden.png", renderer, &my_texture, &my_image_width, &my_image_height);
	IM_ASSERT(ret);

	//------------------------------
	// Set up ImGui
	//------------------------------

	ImGuiIO	io;
	Renderer::ImGui_SDL3_Init(&io, &window, &renderer);

	//------------------------------
	// Rendering preferences
	//------------------------------

	ImVec4		clear_color			= ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	SDL_Event	e;
	bool		quit				= false;
	bool		show_demo_window;

	//------------------------------
	// Class Init
	//------------------------------
	Stork::Print();
	widgets::Widgets widgets;
	widgets.setMetarData(Stork::getData());
	widgets.setMapSize(my_image_width, my_image_height);

	//------------------------------
	// Rendering loop
	//------------------------------

	while (!quit) {
		//Poll for events
		Renderer::ImGui_SDL3_PollEvent(&e, &quit);

		Renderer::ImGui_SDL3_NewFrame();

		ImGui::ShowDemoWindow(&show_demo_window);						//ImGui demo window
		widgets.drawSidePanel();										//Side panel
		widgets.drawMap(my_texture);	//Map panel
		
		//Issue Draw call
		ImGui::Render();
		Renderer::SDL_Render(&renderer, &io, &clear_color);

		

		//Check if refresh button is pressed
		if (widgets.getRefresh()) {
			widgets.setMetarData(Stork::getData());
			widgets.setRefresh(false);
		}
	}

	//------------------------------
	// Shutdown
	//------------------------------
	Renderer::ImGui_SDL3_ShutDown(&window, &renderer);

	return 0;
}