#pragma once

#include "imgui.h"
#include "App.h"
#include "StorkGrabber.h"

namespace widgets {
	
	class Widgets 
	{

	public:
		Widgets();
		
		void setMetarData(Stork::Grabber::MetarDataStruct data);
	
		void drawLastUpdated();
		void drawStationsHeader();

		//Draws the side panel
		void drawSidePanel();

		void drawMap();

		bool getRefresh();
		void setRefresh(bool state);
	};
}