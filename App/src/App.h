#pragma once

#include <string>

struct ICAOtoDromeNameStruct {
	std::string ICAOCode;
	std::string DroneName;
} typedef ICAOtoDromeNameStruct;

extern ICAOtoDromeNameStruct ICAOtoDromeName[];
extern const int ICAOtoDromeNameCount;



