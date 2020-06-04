#include <iostream>
#include <vector>
#include <fstream>

#include "Structs.h"

void pause();

void loadDriver(std::vector <std::pair<LocalBus, Driver>>& vec)
{
	bool longDistance;

	// temp values:
	// for bus
	int ID;
	std::string model;
	float fuelPer100KM;
	float fuelPercentage;
	int totalSeats;
	int takenSeats;
	std::string location;
	// for driver
	std::string name;
	std::string lastname;
	unsigned long long password;

	std::cout << "\n\n\tZa registrovanje para vozac-autobus unesite njihov ID: ";
	std::cin >> ID;
	std::cout << "\n\n\tUnesite model autobusa: ";
	std::cin >> model;
	std::cout << "\n\n\tUnesite potrosnju goriva(l/100km): ";
	std::cin >> fuelPer100KM;
	std::cout << "\n\n\tUnesite procentualnu kolicinu goriva: ";
	std::cin >> fuelPercentage;
	std::cout << "\n\n\tUnesite ukupan broj sjedista: ";
	std::cin >> totalSeats;
	std::cout << "\n\n\tUnesite ukupan broj zauzetih sjedista: ";
	std::cin >> takenSeats;
	std::cout << "\n\n\tUnesitelokaciju autobusa: ";
	std::cin >> location;

	std::cout << "\n\n\tUnesite ime vozaca: ";
	std::cin >> name;
	std::cout << "\n\n\tUnesite prezime vozaca: ";
	std::cin >> lastname;
	std::cout << "\n\n\tUnesite vozacevu sifru za registraciju: ";
	std::cin >> password;

	std::cout << "\n\n\tDa li se radi o lokalnom ili autobusu za duze voznje \n\n\t(0 - lokalni, 1 - za duzu voznju): ";
	std::cin >> longDistance;

	if (longDistance)
	{
		std::string assistantDriver;
		int spareTires;
		std::cout << "\n\n\tUnesite ime pomocnog vozaca: ";
		std::cin >> assistantDriver;
		std::cout << "\n\n\tUnesite broj rezervnih guma: ";
		std::cin >> spareTires;

		LongDistanceBus bus(ID, fuelPer100KM, fuelPercentage, totalSeats, takenSeats, location, assistantDriver, spareTires);
		Driver driver(name, lastname, password);
		vec.push_back(std::make_pair(bus, driver));
	}
	else
	{
		LocalBus bus(ID, fuelPer100KM, fuelPercentage, totalSeats, takenSeats, location);
		Driver driver(name, lastname, password);
		vec.push_back(std::make_pair(bus, driver));
	}
}

void deleteDriver(std::vector <std::pair<LocalBus, Driver>>& vec)
{
	int ID;
	bool validID = false;
	std::string newDriversName, newDriversLastname;

	std::cout << "\n\n\tUnesite ID vozaca kojeg zelite otpustiti: ";
	std::cin >> ID;
	for (size_t i = 0; i < vec.size(); i++)
	{
		if (ID == vec[i].first.getID())
		{
			validID == true;
			std::cout << "\n\n\tIme i prezime vozaca kojeg cete otpustiti: ";
			std::cout << vec[i].second.name << " " << vec[i].second.lastname;
			std::cout << "\n\n\tUnesite ime vozaca kojeg cete zaposliti na njegovo mjesto: ";
			std::cin >> newDriversName;
			std::cout << "\n\n\tUnesite prezime vozaca kojeg cete zaposliti na njegovo mjesto: ";
			std::cin >> newDriversLastname;
			vec[i].second.name = newDriversName;
			vec[i].second.lastname = newDriversLastname;
			break;
		}
	}
	if (validID)
	{
		std::cout << "\n\n\tUspjesno ste zamijenili vozaca!";
	}
	else
	{
		std::cout << "\n\n\tNe postoji vozac s tim ID brojem.";
	}
}

void printDrivers(std::vector <std::pair<LocalBus, Driver>>& vec)
{
	for (std::size_t i = 0; i < vec.size(); i++)
	{
		std::cout << "\n\n\tIme vozaca: " << vec[i].second.name;
		std::cout << "\n\n\tPrezime vozaca: " << vec[i].second.lastname;
	}
}

void printBusses(std::vector <std::pair<LocalBus, Driver>>& vec)
{
	for (std::size_t i = 0; i < vec.size(); i++)
	{
		std::cout << "\n\n\tPotrosnja goriva(l/100km): " << vec[i].first.getFuelPer100KM();
		std::cout << "\n\n\tProcentualna kolicina goriva: " << vec[i].first.getFuelPercentage();
		std::cout << "\n\n\tUkupan broj sjedista: " << vec[i].first.getTotalSeats();
		std::cout << "\n\n\tUkupan broj zauzetih sjedista: " << vec[i].first.getTakenSeats();
		std::cout << "\n\n\tLokacija autobusa: " << vec[i].first.getLocation();
	}
}

unsigned long long encryptPassword(std::string password, unsigned i = 0);

void owner()
{
	// login

	unsigned long long encryptedPassword;
	unsigned long long passwordOwnerTrue;
	int numberOfTries = 3;

	std::ifstream ownerFile("vlasnikSifra.txt");

	if (!ownerFile.is_open())
	{
		std::cout << "\n\n\tNema registrovanog vlasnika!";
		pause();
		return;
	}
	ownerFile >> passwordOwnerTrue;

	while (true)
	{
		std::cout << "\n\n\tMolimo unesite Vasu sifru: ";
		std::string* password = new std::string;
		std::cin >> *password;
		encryptedPassword = encryptPassword(*password);
		numberOfTries--;
		delete password;

		if (encryptedPassword == passwordOwnerTrue) // 
		{
			std::cout << "\n\tPrijava uspjesna.\n\tDobro dosli!";
			break;
		}
		else if (numberOfTries > 0)
		{
			std::cout << "\n\tPogresan unos!\n\tPreostalo pokusaja: " << numberOfTries;
		}
		else
		{
			std::cout << "\n\tPogresan unos!\n\tNemate preostalih pokusaja, nalog je trenutno blokiran zbog sigurnosti vlasnika.";
			return;
		}
	}
	ownerFile.close();

	int option;
	int index;
	int num;

	while (true)
	{
		system("CLS");
		std::cout << "\n\n\tDobrodosli!"
			<< "\n\n\tOdaberite opciju:"
			<< "\n\t\t1 - Registruj vozaca"
			<< "\n\t\t2 - Otpusti vozaca"
			<< "\n\t\t3 - Ispisi sve informacije o vozacima"
			<< "\n\t\t4 - Ispisi sve informacije o autobusima"
			<< "\n\t\t10 - Izlaz"
			<< "\n\n\t\tOdabir: ";

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
		{
			return;
		}
		else
		{
			std::cout << "\n\t\tPogresan unos!";
		}

		std::cout << "\n\n\t\t";
		system("pause");
	}
}