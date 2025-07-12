#include <iostream>
#include "Stork.h"
#include "StorkGrabber.h"

namespace Stork {

	Grabber::MetarDataStruct data;

	void Print() {
		std::cout << "Hello Stork!" << std::endl;
	}

	class StorkHandle {
		StorkHandle() {
			std::cout << "Starting Stork..." << std::endl;

			std::cout << "Started Stork" << std::endl;
		}

		~StorkHandle() {
			std::cout << "Stopping Stork..." << std::endl;

			std::cout << "Stopped Stork..." << std::endl;
		}
	};

	void TestPy() {
		Grabber::GetLFVMetar(data);
		std::cout << data.LastUpdated << std::endl;
	}

	void Stork::grabMetar() {
		Grabber::GetLFVMetar(data);
	}

	Grabber::MetarDataStruct getData() {
		Grabber::MetarDataStruct data1;
		Grabber::GetLFVMetar(data1);
		return data1;
	}

	std::string getLastUpdated() {
		return data.LastUpdated;
	}

	Grabber::MetarDataStruct Stork::getData() {
		return data;
	}

	Stork::Stork() {
		Print();
		grabMetar();
	}
	
}