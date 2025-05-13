#pragma once

#include <vector>


namespace Stork::Grabber {
	

	struct MetarStationDataStruct {
		std::string IcaoCode;
		std::string rawData;

	} typedef MetarStationDataStruct;

	struct MetarDataStruct {
		std::string LastUpdated;
		std::vector<MetarStationDataStruct> stationDatas;

	} typedef MetarDataStruct;

	bool GetLFVMetar(MetarDataStruct& data);
}
