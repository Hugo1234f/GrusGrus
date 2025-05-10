#include <iostream>
#include "Stork.h"
#include "StorkGrabber.h"

namespace Stork {

	void Print() {
		printf("Hello Stork!");
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
		Grabber::GetLFVMetar();
	}
	
}