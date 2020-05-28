#pragma once

struct LocalBus
{
	std::string id;
	std::string driver;
	std::string mark;
	std::string model;
	float fuelPer100KM;
	float fuelPercentage;
	int totalSeats;
	int takenSeats;
	std::string location;
};

struct LongDistanceBus : LocalBus
{
	std::string assistantDriver;
	int spareTires;
};