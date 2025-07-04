#pragma once

#include <string>

struct ICAOtoDromeNameStruct {
	std::string ICAOCode;
	std::string DroneName;
} typedef ICAOtoDromeNameStruct;

ICAOtoDromeNameStruct ICAOtoDromeName[] = {
	{"ESCF", "Linköping/Malmen"},
	{"ESCM", "Uppsala-Ärna"},
	{"ESDF", "Ronneby Airport"},
	{"ESGG", "Göteborg/Landvetter"},
	{"ESGJ", "Jönköping Airport"},
	{"ESGT", "Trollhättan/Vänersborg"},
	{"ESGP", "Göteborg/Säve"},
	{"ESIA", "Karlsborg"},
	{"ESIB", "Såtenäs"},
	{"ESKM", "Mora/Siljan"},
	{"ESKN", "Stockholm/Skavsta"},
	{"ESKS", "Sälen/Scandinavian Mountains"},
	{"ESMK", "Kristianstad"},
	{"ESMQ", "Kalmar"},
	{"ESMS", "Malmö"},
	{"ESMT", "Halmstad"},
	{"ESMX", "Växjö/Kronoberg"},
	{"ESND", "Sveg"},
	{"ESNG", "Gällivare"},
	{"ESNK", "Kramfors-Sollefteå"},
	{"ESNL", "Lycksele"},
	{"ESNN", "Sundsvall-Timrå"},
	{"ESNO", "Örnsköldsvik"},
	{"ESNQ", "Kiruna"},
	{"ESNS", "Skellefteå"},
	{"ESNU", "Umeå"},
	{"ESNV", "Vilhelmina"},
	{"ESNX", "Arvidsjaur"},
	{"ESNZ", "Åre Östersund"},
	{"ESOE", "Örebro"},
	{"ESOK", "Karlstad"},
	{"ESOH", "Hagfors"},
	{"ESOW", "Stockholm/Västerås"},
	{"ESPA", "Luleå/Kallax"},
	{"ESPE", "Vidsel"},
	{"ESSA", "Stockholm/Arlanda"},
	{"ESSB", "Stockholm/Bromma"},
	{"ESSD", "Borlänge"},
	{"ESSL", "Linköping/SaaB"},
	{"ESSP", "Norrköping/Kungsängen"},
	{"ESST", "Torsby"},
	{"ESSV", "Visby"},
	{"ESTA", "Ängelholm"},
	{"ESTL", "Ljungbyhed"},
	{"ESUP", "Pajala"},
	{"ESUT", "Hemavan Tärnaby"}
};



