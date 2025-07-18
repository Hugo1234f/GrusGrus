#include <Windows.h>
#include <string>
#include <iostream>
#include <fstream>

#include "nlohmann/json.h"
#include "StorkGrabber.h"

namespace Stork::Grabber {

	void parseJSONMetar(nlohmann::json& data) {
		std::ifstream f("..\\..\\..\\Getters\\data.json");
		data = nlohmann::json::parse(f);

		std::cout << "Last updated" << data["lastUpdated"] << std::endl;
	}

	bool GetLFVMetar(MetarDataStruct& data) {
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

		nlohmann::json Rawdata;
		parseJSONMetar(Rawdata);

		data.LastUpdated = Rawdata["lastUpdated"];

		std::vector<Stork::Grabber::MetarStationDataStruct> stationDataVec;
		for (int i = 0; i < Rawdata["stations"].size(); i++) {
			MetarStationDataStruct stationData;
			stationData.IcaoCode = Rawdata["stations"][i]["ICAO"];
			stationData.rawData = Rawdata["stations"][i]["weatherData"];
			stationDataVec.push_back(stationData);
		}
		data.stationDatas = stationDataVec;

		return true;
	}
	
	

}
