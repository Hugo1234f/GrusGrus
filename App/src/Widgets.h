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
		
		void drawMap();

		//---------------------------------------
		// Update indicator controls
		//---------------------------------------

		bool getRefresh();
		void setRefresh(bool state);
	};
}