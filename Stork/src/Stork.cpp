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

	AD_Data getData() {
		AD_Data dataObj;
		dataObj.ICAO = data.stationDatas[0].IcaoCode;
		dataObj.ICAO = data.stationDatas[0].rawData;

		return dataObj;
	}
	
}