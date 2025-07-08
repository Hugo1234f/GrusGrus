#pragma once

#include "imgui.h"
#include "App.h"
#include "StorkGrabber.h"

namespace widgets {
	
	class Widgets 
	{
	public:
		Widgets();
		
		//---------------------------------------
		// Data handling
		//---------------------------------------

		void setMetarData(Stork::Grabber::MetarDataStruct data);

		//---------------------------------------
		// Side Panel
		//---------------------------------------

		void drawSidePanel();
		
		void drawLastUpdated();
		void drawStationsHeader();

		//---------------------------------------
		// Map
		//---------------------------------------
		
		void drawMap(void* my_texture, int my_image_width, int my_image_height);
		void drawMap(void* my_texture);

		//---------------------------------------
		// Update indicator controls
		//---------------------------------------

		bool getRefresh();
		void setRefresh(bool state);
		void setMapSize(int width, int height);
	};
}