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

<<<<<<< Updated upstream
void loadBuses(std::ifstream& file, std::vector <LocalBus>& vec)
=======
void loadInfo(std::ifstream& file, std::vector <std::pair<LocalBus, Driver>>& vec)
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
			vec.push_back(LongDistanceBus(ID, driverName, driverSurname, model, fuelPer100KM, fuelPercentage, totalSeats, takenSeats, location, assistantDriver, spareTires));
		}
		else
		{
			vec.push_back(LocalBus(ID, driverName, driverSurname, model, fuelPer100KM, fuelPercentage, totalSeats, takenSeats, location));
=======
			LongDistanceBus bus(ID, model, fuelPer100KM, fuelPercentage, totalSeats, takenSeats, location, assistantDriver, spareTires);
			Driver driver(name, lastname, password);
			vec.push_back(std::make_pair(bus, driver));
		}
		else
		{			
			LocalBus bus(ID, model, fuelPer100KM, fuelPercentage, totalSeats, takenSeats, location);
			Driver driver(name, lastname, password);
			vec.push_back(std::make_pair(bus, driver));
>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
=======
bool loginConfirmation(std::string name, std::string lastname, int ID, int password, std::vector <Driver> loginInfo)
{
	for (const Driver& driver : loginInfo)
	{
		if (name == driver.name and lastname == driver.lastname and password == driver.encryptedPassword)
		{
			return true;
		}
	}
	return false;
}

>>>>>>> Stashed changes

void driver()
{
	std::ifstream driversFile("vozaci.txt");

	if (!driversFile.is_open())
	{
		std::cout << "\n\n\tNema registrovanih vozaca!";
		pause();
		return;
	}

<<<<<<< Updated upstream
	std::vector <Drivers> loginInfo;
	loadDrivers(driversFile, loginInfo);
=======
	std::vector <Driver> loginInfo;
	std::string name;
	std::string lastname;
	int ID;
	int busID;
	int password;
>>>>>>> Stashed changes

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