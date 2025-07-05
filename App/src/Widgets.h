#pragma once

#include "imgui.h"
#include "App.h"

namespace widgets {

	static int aerodrome_highlited_idx = -1;
	static int aerodrome_item_selected_idx = 0;

	static std::string lastUpdated = "N/A";

	void setLastUpdated(std::string lastUpdatedStr) {
		lastUpdated = lastUpdatedStr;
	}

	void drawLastUpdated() {
		if (ImGui::CollapsingHeader("Last Updated", ImGuiTreeNodeFlags_None)) {
			ImGui::Text(lastUpdated.c_str());
			ImGui::Button("Refresh (TODO)");
		}
	}

	void drawStationsHeader() {
		if (ImGui::CollapsingHeader("Stations", ImGuiBackendFlags_None)) {
			int aerodrome_nums = sizeof(ICAOtoDromeName) / sizeof(ICAOtoDromeNameStruct);

			ImGui::SeparatorText("Aerodromes");
			ImGui::BeginListBox("##Listbox 2", ImVec2(-FLT_MIN, (aerodrome_nums < 10 ? aerodrome_nums : 10) * ImGui::GetTextLineHeightWithSpacing()));
			for (int i = 0; i < aerodrome_nums; i++) {
				const bool is_selected = (aerodrome_item_selected_idx == i);
				std::string ItemName = ICAOtoDromeName[i].ICAOCode + " - " + ICAOtoDromeName[i].DroneName;
				ImGuiSelectableFlags flags = (aerodrome_highlited_idx == i) ? ImGuiSelectableFlags_Highlight : 0;

				if (ImGui::Selectable(ItemName.c_str(), is_selected, flags)) {
					aerodrome_item_selected_idx = i;
				}
			}
			ImGui::EndListBox();

			ImGui::SeparatorText("VViS");
		}
	}

	//Draws the side panel
	void drawSidePanel() {
		ImGui::Begin("AD Data");

		drawLastUpdated();
		drawStationsHeader();

		ImGui::End();
	}


	void drawMap() {

	}
}