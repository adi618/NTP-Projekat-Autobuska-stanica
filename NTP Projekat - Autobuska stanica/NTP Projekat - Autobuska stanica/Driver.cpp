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

void loadDrivers(std::ifstream& file, std::vector <Driver>& vec)
{

}


void loadInfo(std::ifstream& file, std::vector <std::pair<LocalBus, Driver>>& vec)
{
	bool longDistance;

	// temp values:
		// for bus
	int ID;
	std::string driverName;
	std::string driverSurname;
	std::string model;
	float fuelPer100KM;
	float fuelPercentage;
	int totalSeats;
	int takenSeats;
	std::string location;
		// for driver
	std::string name;
	std::string lastname;
	int password;

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

		file >> name;
		file >> lastname;
		file >> password;


		if (longDistance)
		{
			std::string assistantDriver;
			int spareTires;
			file >> assistantDriver;
			file >> spareTires;

			LongDistanceBus bus(ID, model, fuelPer100KM, fuelPercentage, totalSeats, takenSeats, location, assistantDriver, spareTires);
			Driver driver(name, lastname, password);
			vec.push_back(std::make_pair(bus, driver));
		}
		else
		{			
			LocalBus bus(ID, model, fuelPer100KM, fuelPercentage, totalSeats, takenSeats, location);
			Driver driver(name, lastname, password);
			vec.push_back(std::make_pair(bus, driver));
		}
	}
}

void loadMap(std::ifstream& file, std::map <std::string, std::map <std::string, std::pair<float, float>>>& adjMatrix)
{
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
}

bool loginConfirmation(std::string name, std::string lastname, int password, const std::vector <std::pair<LocalBus, Driver>>& loginInfo)
{
	for (const std::pair<LocalBus, Driver>& driver : loginInfo)
	{
		if (name == driver.second.name and 
			lastname == driver.second.lastname and 
			password == driver.second.encryptedPassword)
		{
			return true;
		}
	}
	return false;
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

	std::vector <Driver> loginInfo;
	std::string name;
	std::string lastname;
	int ID;
	int busID;
	int password;

	std::cout << "\n\n\tMolimo unesite ime: ";

	// login

	std::vector <Road> map;

	// iz mapa.txt upis u road
	//std::map <std::string, std::map <std::string, std::pair<float, float>>> adjMatrix = loadMap(file);
	// ucitaj upis iz autobusa
	// ucitaj datume

	int option;
	int index;
	int num;

	while (true)
	{
		system("cls");
		std::cout << "\n\n\t    "
			<< "\n\n\tChoose an option:"
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