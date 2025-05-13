#pragma once

#include <vector>

namespace Stork::Grabber {
	bool GetLFVMetar();

	struct MetarStationDataStruct {

	} typedef MetarStationDataStruct;

	struct MetarDataStruct {
		std::string LastUpdated;
		std::vector<MetarStationDataStruct> stationDatas;

	} typedef MetarDataStruct;
}
