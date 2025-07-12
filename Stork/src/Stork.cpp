#include <iostream>
#include "Stork.h"
#include "StorkGrabber.h"

namespace Stork {

	Grabber::MetarDataStruct data;

	void StorkHandle::Print() {
		std::cout << "Hello Stork!" << std::endl;
	}

	StorkHandle::StorkHandle() {
		Print();
		grabMetar();
	}

	void StorkHandle::grabMetar() {
		Grabber::GetLFVMetar(data);
	}

	std::string StorkHandle::getLastUpdated() {
		return data.LastUpdated;
	}

	Grabber::MetarDataStruct StorkHandle::getData() {
		return data;
	}
}