#include <Windows.h>
#include <string>
#include <iostream>

namespace Stork::Grabber {

	bool GetLFVMetar() {
		std::string command = "python ..\\..\\..\\Getters\\LFVMetar.py";

		STARTUPINFOA si = { sizeof(si) };
		PROCESS_INFORMATION pi;

		BOOL result = CreateProcessA(
			nullptr,
			command.data(),
			nullptr,
			nullptr,
			FALSE,
			0,
			nullptr,
			nullptr,
			&si,
			&pi
		);

		if (!result) {
			std::cerr << "Failed to start Python script LFVMetar.py. Error: " << GetLastError() << std::endl;
			return false;
		}

		WaitForSingleObject(pi.hProcess, INFINITE);

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		return true;
	}
	
}
