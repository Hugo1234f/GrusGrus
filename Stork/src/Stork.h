#pragma once

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
	STORK_API void Print();
	STORK_API void TestPy();

	struct AD_Data {
		std::string ICAO;
		std::string data;
	};

	STORK_API AD_Data getData();
	
}