#pragma once

#include "StorkGrabber.h"

#ifdef WINDOWS
	#ifdef STORK
		#define STORK_API __declspec(dllexport)
	#else
		#define STORK_API __declspec(dllimport)
	#endif
#else
	#error "GrusGrus only supports Windows"
#endif


namespace Stork {

	class STORK_API StorkHandle {
		Grabber::MetarDataStruct data;
					  
	public:
		StorkHandle();

		void grabMetar();
		void Print();

		std::string getLastUpdated();
		Grabber::MetarDataStruct getData();
		
	};
	
}