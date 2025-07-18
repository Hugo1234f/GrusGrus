#include "Widgets.h"
#include "Stork.h"
#include "StorkGrabber.h"
#include <iostream>

namespace widgets {

		Stork::Grabber::MetarDataStruct metarData;
		int aerodrome_highlited_idx = -1;
		int aerodrome_item_selected_idx = 0;
		int mapWidth = -1;
		int mapHeight = -1;
		std::string lastUpdated = "N/A";
		std::string weatherText = "N/A";
		std::string requestedWeather = "";
		std::string currentWeather = "a";
		static bool updateClicked = false;
		static bool refresh = false;

		Widgets::Widgets() {

		}

		void Widgets::setMetarData(Stork::Grabber::MetarDataStruct data) {
			metarData = data;
		}

		void Widgets::drawLastUpdated() {
			if (ImGui::CollapsingHeader("Last Updated", ImGuiTreeNodeFlags_None)) {
				ImGui::Text(metarData.LastUpdated.c_str());
	
				if (ImGui::Button("Refresh")) {
					updateClicked = true;
				}
				if (updateClicked) {
					ImGui::SameLine();
					ImGui::Text("Updating");
					refresh = true;
				}
			}
		}

		void Widgets::drawStationsHeader() {
			if (ImGui::CollapsingHeader("Stations", ImGuiBackendFlags_None)) {
				int aerodrome_nums = ICAOtoDromeNameCount;

				ImGui::SeparatorText("Aerodromes");
				ImGui::BeginListBox("##Listbox 2", ImVec2(-FLT_MIN, (aerodrome_nums < 10 ? aerodrome_nums : 10) * ImGui::GetTextLineHeightWithSpacing()));
				for (int i = 0; i < aerodrome_nums; i++) {
					const bool is_selected = (aerodrome_item_selected_idx == i);
					std::string ItemName = ICAOtoDromeName[i].ICAOCode + " - " + ICAOtoDromeName[i].DroneName;
					ImGuiSelectableFlags flags = (aerodrome_highlited_idx == i) ? ImGuiSelectableFlags_Highlight : 0;

					if (ImGui::Selectable(ItemName.c_str(), is_selected, flags)) {
						aerodrome_item_selected_idx = i;

						

						if (currentWeather != ICAOtoDromeName[i].ICAOCode) {
							requestedWeather = ICAOtoDromeName[i].ICAOCode;
						}
						
					}
				}
				ImGui::EndListBox();

				ImGui::SeparatorText("VViS");
				ImGui::SeparatorText("Custom Points");
			}
		}

		void Widgets::drawSidePanel() {
			ImGui::Begin("AD Data");

			drawLastUpdated();
			drawStationsHeader();

			ImGui::End();
		}

		void Widgets::drawMap(void* my_texture, int my_image_width, int my_image_height) {
			ImGui::Begin("Map");
			ImGui::Image((ImTextureID)(intptr_t)my_texture, ImVec2((float)my_image_width, (float)my_image_height));
			ImGui::End();
		}
		void Widgets::drawMap(void* my_texture) {
			if (mapWidth <= 0 || mapHeight <= 0) { return; }

			ImGui::Begin("Map");
			ImGui::Image((ImTextureID)(intptr_t)my_texture, ImVec2((float)mapWidth, (float)mapHeight));
			
			if (currentWeather.size() >= 4) {
				ImDrawList* draw_list = ImGui::GetWindowDrawList();
				ImVec2 map_origin = ImGui::GetItemRectMin();
				draw_list->AddCircleFilled(map_origin, 10.0f, IM_COL32(255, 0, 0, 255));
			}
			
			ImGui::End();
		
			
		}


		void Widgets::drawWeather() {
			ImGui::Begin("Weather");
			ImGui::Text(weatherText.c_str());
			ImGui::End();

			
		}

	
		bool Widgets::getRefresh() {
			return refresh;
		}
		void Widgets::setRefresh(bool state) {
			refresh = state;
			updateClicked = refresh;
		}
		void Widgets::setMapSize(int width, int height) {
			mapWidth = width;
			mapHeight = height;
		}
		std::string Widgets::getRequestedWeather() {
			return requestedWeather;
		}
		void Widgets::setWeatherText(std::string text) {
			weatherText = text;
			currentWeather = requestedWeather;
			requestedWeather = "";
			
		}

}