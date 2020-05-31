#include <iostream>
#include <vector>
#include <fstream>
#include <map>

#include "Structs.h"


struct Road
{
	std::string location1, location2;
	float time;
	float fuel;
};

void pause();

void loadDrivers(std::ifstream& file, std::vector <Drivers>& vec)
{

}

void loadBuses(std::ifstream& file, std::vector <LocalBus>& vec)
{
	bool longDistance;

	// temp values:
	int ID;
	std::string driverName;
	std::string driverSurname;
	std::string model;
	float fuelPer100KM;
	float fuelPercentage;
	int totalSeats;
	int takenSeats;
	std::string location;
	std::string assistantDriver;
	int spareTires;

	while (file >> longDistance)
	{
		file >> ID;
		file >> driverName;
		file >> driverSurname;
		file >> model;
		file >> fuelPer100KM;
		file >> fuelPercentage;
		file >> totalSeats;
		file >> takenSeats;
		file >> location;

		if (longDistance)
		{
			file >> assistantDriver;
			file >> spareTires;
			vec.push_back(LongDistanceBus(ID, driverName, driverSurname, model, fuelPer100KM, fuelPercentage, totalSeats, takenSeats, location, assistantDriver, spareTires));
		}
		else
		{
			vec.push_back(LocalBus(ID, driverName, driverSurname, model, fuelPer100KM, fuelPercentage, totalSeats, takenSeats, location));
		}
	}
}

std::map <std::string, std::map <std::string, std::pair<float, float>>> loadMap(std::ifstream& file)
{
	std::map <std::string, std::map <std::string, std::pair <float, float>>> adjMatrix;

	std::string location1, location2;
	float time;
	float fuel;

	while (file >> location1)
	{
		file >> location2;
		file >> time;
		file >> fuel;

		if (time >= 0 or fuel >= 0)
		{
			if (time > adjMatrix[location1][location2].first)
				adjMatrix[location1][location2] = std::make_pair(time, fuel);
		}
	}

	return adjMatrix;
}


void driver()
{
	std::ifstream driversFile("vozaci.txt");

	if (!driversFile.is_open())
	{
		std::cout << "\n\n\tNema registrovanih vozaca!";
		pause();
		return;
	}

	std::vector <Drivers> loginInfo;
	loadDrivers(driversFile, loginInfo);

	std::cout << "\n\n\tMolimo unesite ime: ";

	// login

	std::vector <Road> map;

	// iz mapa.txt upis u road
	std::map <std::string, std::map <std::string, int>> adjMatrix;
	// ucitaj upis iz autobusa
	// ucitaj datume

	int option;
	int index;
	int num;

	while (true)
	{
		system("cls");
		std::cout << "\n\n\t    ";

		std::cout << "\n\n\tChoose an option:"
			<< "\n\t\t1 - mapa i autobusi txt za dijkstrin algoritam"
			<< "\n\t\t2 - ode na lokaciju // oduzet ce gorivo"
			<< "\n\t\t3 - provjera goriva"
			<< "\n\t\t4 - ispisi redovne voznje"
			<< "\n\n\t\tOption: ";

		std::cin >> option;

		if (option == 1)
		{

		}
		else if (option == 2)
		{

		}
		else if (option == 3)
		{

		}
		else if (option == 10)
			return;
		else
		{
			std::cout << "\n\t\tInvalid option!";
		}
		std::cout << "\n\n\t\t";
		system("pause");
	}
}