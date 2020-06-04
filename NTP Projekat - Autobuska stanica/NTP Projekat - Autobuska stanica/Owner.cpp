#include <iostream>
#include <vector>
#include <fstream>

#include "Structs.h"

void pause();

unsigned long long encryptPassword(std::string password, unsigned i = 0);
void loadDriverKeyboard(std::vector <std::pair<LocalBus*, Driver*>>& vec)
{
	bool longDistance;
	// temp values:
	// for bus
	int ID;
	float fuelPer100KM;
	float fuelPercentage;
	int totalSeats;
	int takenSeats;
	std::string location;
	// for driver
	std::string name;
	std::string lastname;
	std::string password;

	std::cout << "\n\tZa registrovanje para vozac-autobus unesite njihov ID: ";
	std::cin >> ID;
	std::cout << "\n\tUnesite potrosnju goriva(l/100km): ";
	std::cin >> fuelPer100KM;
	std::cout << "\n\tUnesite procentualnu kolicinu goriva: ";
	std::cin >> fuelPercentage;
	std::cout << "\n\tUnesite ukupan broj sjedista: ";
	std::cin >> totalSeats;
	std::cout << "\n\tUnesite ukupan broj zauzetih sjedista: ";
	std::cin >> takenSeats;
	std::cout << "\n\tUnesite lokaciju autobusa: ";
	std::cin >> location;

	std::cout << "\n\tUnesite ime vozaca: ";
	std::cin >> name;
	std::cout << "\n\tUnesite prezime vozaca: ";
	std::cin >> lastname;
	std::cout << "\n\tUnesite vozacevu sifru za registraciju: ";
	std::cin >> password;

	std::cout << "\n\n\tDa li se radi o lokalnom ili autobusu za duze voznje \n\t(0 - lokalni, 1 - za duzu voznju): ";
	std::cin >> longDistance;

	if (longDistance)
	{
		std::string assistantDriver;
		int spareTires;
		std::cout << "\n\tUnesite ime pomocnog vozaca: ";
		std::cin >> assistantDriver;
		std::cout << "\n\tUnesite broj rezervnih guma: ";
		std::cin >> spareTires;

		LongDistanceBus* bus = new LongDistanceBus
		(ID, fuelPer100KM, fuelPercentage, totalSeats, takenSeats, location, assistantDriver, spareTires);
		Driver* driver = new Driver(name, lastname, encryptPassword(password));
		vec.push_back(std::make_pair(bus, driver));
	}
	else
	{
		LocalBus* bus = new LocalBus(ID, fuelPer100KM, fuelPercentage, totalSeats, takenSeats, location);
		Driver* driver = new Driver(name, lastname, encryptPassword(password));
		vec.push_back(std::make_pair(bus, driver));
	}
}

void deleteDriver(std::vector <std::pair<LocalBus*, Driver*>>& vec)
{
	int ID;
	bool validID = false;
	std::string newDriversName, newDriversLastname;

	std::cout << "\n\n\tUnesite ID vozaca kojeg zelite otpustiti: ";
	std::cin >> ID;
	for (size_t i = 0; i < vec.size(); i++)
	{
		if (ID == vec[i].first->getID())
		{
			validID = true;
			std::cout << "\n\n\tIme i prezime vozaca kojeg cete otpustiti: ";
			std::cout << vec[i].second->name << " " << vec[i].second->lastname;
			std::cout << "\n\n\tUnesite ime vozaca kojeg cete zaposliti na njegovo mjesto: ";
			std::cin >> newDriversName;
			std::cout << "\n\n\tUnesite prezime vozaca kojeg cete zaposliti na njegovo mjesto: ";
			std::cin >> newDriversLastname;
			vec[i].second->name = newDriversName;
			vec[i].second->lastname = newDriversLastname;
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

void printDrivers(std::vector <std::pair<LocalBus*, Driver*>>& vec)
{
	for (std::size_t i = 0; i < vec.size(); i++)
	{
		std::cout << "\n\n\tID broj: " << vec[i].first->getID();
		std::cout << "\n\tIme vozaca: " << vec[i].second->name;
		std::cout << "\n\tPrezime vozaca: " << vec[i].second->lastname;
	}
}

void printBusses(std::vector <std::pair<LocalBus*, Driver*>>& vec)
{
	for (std::size_t i = 0; i < vec.size(); i++)
	{
		std::cout << "\n\n\tID broj: " << vec[i].first->getID();
		std::cout << "\n\tPotrosnja goriva(l/100km): " << vec[i].first->getFuelPer100KM();
		std::cout << "\n\tProcentualna kolicina goriva: " << vec[i].first->getFuelPercentage();
		std::cout << "\n\tUkupan broj sjedista: " << vec[i].first->getTotalSeats();
		std::cout << "\n\tUkupan broj zauzetih sjedista: " << vec[i].first->getTakenSeats();
		std::cout << "\n\tLokacija autobusa: " << vec[i].first->getLocation();

		if (!vec[i].first->isLocal())
		{
			std::cout << "\n\tIme pomocnog vozaca: " << vec[i].first->getAssistantDriver();
			std::cout << "\n\tBroj rezervnih guma: " << vec[i].first->getSpareTires();
		}
	}
}

void saveLoginInfo(const std::vector <std::pair<LocalBus*, Driver*>>& loginInfo)
{
	std::ofstream finalFile("info.txt");
	for (std::size_t i = 0; i < loginInfo.size(); i++)
	{
		if (loginInfo[i].first->isLocal())
		{
			finalFile << 0 << " ";
		}
		else
		{
			finalFile << 1 << " ";
		}

		finalFile << loginInfo[i].first->getID() << " " << loginInfo[i].first->getFuelPer100KM() << " " << loginInfo[i].first->getFuelPercentage()
			<< " " << loginInfo[i].first->getTotalSeats() << " " << loginInfo[i].first->getTakenSeats() << " " << loginInfo[i].first->getLocation()
			<< " " << loginInfo[i].second->name << " " << loginInfo[i].second->lastname << " " << loginInfo[i].second->encryptedPassword;

		if (!loginInfo[i].first->isLocal())
		{
			finalFile << loginInfo[i].first->getAssistantDriver() << loginInfo[i].first->getSpareTires();
		}

		finalFile << "\n";
	}
	finalFile.close();
}

void loadInfo(std::ifstream& file, std::vector <std::pair<LocalBus*, Driver*>>& vec);

void owner()
{
	// login
	unsigned long long encryptedPassword;
	unsigned long long passwordOwnerTrue;
	unsigned long long passwordOwnerInput;
	int numberOfTries = 3;

	std::ifstream infoFile("info.txt");

	if (!infoFile.is_open())
	{
		std::cout << "\n\n\tNema registrovanih vozaca!";
		pause();
	}

	std::vector <std::pair<LocalBus*, Driver*>> loginInfo;
	loadInfo(infoFile, loginInfo);
	infoFile.close();

	std::ifstream ownerFile("vlasnikSifra.txt");

	if (!ownerFile.is_open())
	{
		std::cout << "\n\n\tNema registrovanog vlasnika!";
		pause();
		return;
	}
	ownerFile >> passwordOwnerTrue;
	ownerFile.close();

	while (true)
	{
		std::cout << "\n\n\tMolimo unesite Vasu sifru: ";
		std::string* password = new std::string;
		std::cin >> *password;
		encryptedPassword = encryptPassword(*password);
		numberOfTries--;
		delete password;

		if (encryptedPassword == passwordOwnerTrue)
		{
			std::cout << "\n\tPrijava uspjesna.\n\tDobro dosli!";
			pause();
			break;
		}
		else if (numberOfTries > 0)
		{
			std::cout << "\n\tPogresan unos!\n\tPreostalo pokusaja: " << numberOfTries;
		}
		else
		{
			std::cout << "\n\tPogresan unos!\n\tNemate preostalih pokusaja, nalog je trenutno blokiran zbog sigurnosti vlasnika.";
			exit(0);
		}
	}

	int option;

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
			loadDriverKeyboard(loginInfo);
		}
		else if (option == 2)
		{
			deleteDriver(loginInfo);
		}
		else if (option == 3)
		{
			printDrivers(loginInfo);
		}
		else if (option == 4)
		{
			printBusses(loginInfo);
		}
		else if (option == 10)
		{
			break;
		}
		else
		{
			std::cout << "\n\t\tPogresan unos!";
		}

		std::cout << "\n\n\t\t";
		system("pause");
	}

	saveLoginInfo(loginInfo);
}