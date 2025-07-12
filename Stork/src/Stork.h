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

	struct AD_Data {
		std::string ICAO;
		std::string data;
	};

	//---------------------------------------
	// Diagnostics & Logging
	//---------------------------------------

	STORK_API void Print();
	STORK_API void TestPy();

	//---------------------------------------

	//STORK_API Grabber::MetarDataStruct getData();
	STORK_API std::string getLastUpdated();

	class STORK_API Stork {
		Grabber::MetarDataStruct data;
					  
	public:
		void grabMetar();
		Grabber::MetarDataStruct getData();
		Stork();
	};
	
}