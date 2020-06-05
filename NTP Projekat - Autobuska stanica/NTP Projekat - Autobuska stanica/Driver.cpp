#include <iostream>
#include <vector>
#include <fstream>
#include <map>

#include "Structs.h"


struct Info
{
	float time;
	float fuel;

	Info() : time(0), fuel(0) {};

	Info(float time, float fuel) : time(time), fuel(fuel) {};
};


void pause();

void loadInfo(std::ifstream& file, std::vector <std::pair<LocalBus*, Driver*>>& vec)
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
	unsigned long long password;

	while (file >> longDistance)
	{
		file >> ID;
		file >> fuelPer100KM;
		file >> fuelPercentage;
		file >> totalSeats;
		file >> takenSeats;
		file >> location;

		file >> name;
		file >> lastname;
		file >> password;

		if (takenSeats > totalSeats)
			takenSeats = totalSeats;

		if (longDistance)
		{
			std::string assistantDriver;
			int spareTires;
			file >> assistantDriver;
			file >> spareTires;

			LongDistanceBus* bus = new LongDistanceBus
			(ID, fuelPer100KM, fuelPercentage, totalSeats, takenSeats, location, assistantDriver, spareTires);
			Driver* driver = new Driver(name, lastname, password);
			vec.push_back(std::make_pair(bus, driver));
		}
		else
		{
			LocalBus* bus = new LocalBus(ID, fuelPer100KM, fuelPercentage, totalSeats, takenSeats, location);
			Driver* driver = new Driver(name, lastname, password);
			vec.push_back(std::make_pair(bus, driver));
		}
	}
}

void loadMap(std::ifstream& file, std::map <std::string, std::map <std::string, Info>>& adjMatrix, bool undirected = true)
{
	std::string location1, location2;
	float time;
	float fuel;

	while (file >> location1)
	{
		file >> location2;
		file >> time;
		file >> fuel;

		if (time > 0 or fuel > 0)
		{
			if (time > adjMatrix[location1][location2].time)
			{
				adjMatrix[location1][location2] = Info(time, fuel);
				if (undirected)
				{
					adjMatrix[location2][location1] = Info(time, fuel);
				}
			}
		}
	}
}

std::pair <bool, int> loginConfirmation
(std::string name, std::string lastname, unsigned long long password, const std::vector <std::pair<LocalBus*, Driver*>>& loginInfo)
{
	for (int i = 0; i < loginInfo.size(); i++)
	{
		if (name == loginInfo[i].second->name and
			lastname == loginInfo[i].second->lastname and
			password == loginInfo[i].second->encryptedPassword)
		{
			return std::make_pair(true, i);
		}
	}
	return std::make_pair(false, -1);
}

std::ostream& operator<<(std::ostream& stream, std::pair <LocalBus*, Driver*>& driver)
{

	stream << "\n\tPostotak goriva: " << driver.first->getFuelPercentage();
	stream << "\n\tPotrosnja po 100 kilometara: " << driver.first->getFuelPer100KM();
	stream << "\n\tBroj zauzetih sjedista: " << driver.first->getTakenSeats();
	stream << "\n\tBroj ukupnih sjedista: " << driver.first->getTotalSeats();
	stream << "\n\tTrenutna lokacija: " << driver.first->getLocation();

	return stream;
}

unsigned long long encryptPassword(std::string password, unsigned i = 0)
{
	if (i >= password.size())
		return -1;

	return (password[i] * 98257 + 67867967) % 1000000007 + encryptPassword(password, i + 1);
}

std::map <std::string, Info> dijkstra
(std::string source, std::map <std::string, std::map <std::string, Info>>& adjMatrix)
{
	float MAX = std::numeric_limits <float>::max();
	std::map <std::string, Info> time;
	std::map <std::string, bool> visited;
	for (const std::pair<std::string, std::map <std::string, Info>>& it : adjMatrix)
	{
		time[it.first].time = MAX;
		time[it.first].fuel = 0;
		visited[it.first] = false;
	}

	time[source].time = 0;

	for (int i = 0; i < adjMatrix.size() - 1; i++)
	{
		float min = MAX;
		std::string minIndex;

		for (const std::pair<std::string, std::map <std::string, Info>>& v : adjMatrix)
		{
			if (visited[v.first] == false && time[v.first].time <= min)
			{
				min = time[v.first].time;
				minIndex = v.first;
			}
		}
		std::string u = minIndex;

		visited[u] = true;

		for (const std::pair<std::string, std::map <std::string, Info>>& v : adjMatrix)
		{
			if (!visited[v.first] and
				adjMatrix[u][v.first].time > 0 and
				time[u].time != MAX and
				time[u].time + adjMatrix[u][v.first].time < time[v.first].time)
			{
				time[v.first].time = time[u].time + adjMatrix[u][v.first].time;
				time[v.first].fuel = time[u].fuel + adjMatrix[u][v.first].fuel;
			}
		}
	}

	return time;
}

void saveLoginInfo(const std::vector <std::pair<LocalBus*, Driver*>>& loginInfo);

void deleteMemory(const std::vector <std::pair<LocalBus*, Driver*>>& loginInfo)
{
	for (const std::pair<LocalBus*, Driver*>& info : loginInfo)
	{
		delete info.first;
		delete info.second;
	}
}

void driver()
{
	std::ifstream infoFile("info.txt");
	std::ifstream mapFile("mapa.txt");

	if (!infoFile.is_open())
	{
		std::cout << "\n\n\tNema registrovanih vozaca!";
		pause();
		return;
	}

	if (!mapFile.is_open())
	{
		std::cout << "\n\n\tMapa nije pronadjena!";
		pause();
		return;
	}

	std::vector <std::pair<LocalBus*, Driver*>> loginInfo;
	std::pair<LocalBus*, Driver*> driverInfo;
	loadInfo(infoFile, loginInfo);
	std::string name;
	std::string lastname;
	std::string password;
	int numberOfTries = 3;
	std::pair <bool, int> loginRezult;
	int driverIndex;

	while (true)
	{
		std::cout << "\n\n\tMolimo unesite ime: ";
		std::cin >> name;

		std::cout << "\n\n\tMolimo unesite prezime: ";
		std::cin >> lastname;

		std::cout << "\n\n\tMolimo unesite lozinku: ";
		std::cin >> password;

		numberOfTries--;

		unsigned long long encryptedPassword = encryptPassword(password);
		loginRezult = loginConfirmation(name, lastname, encryptedPassword, loginInfo);
		if (loginRezult.first)
		{
			std::cout << "\n\tPrijava uspjesna.\n\tDobro dosli!";
			driverIndex = loginRezult.second;
			driverInfo = loginInfo[driverIndex];
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

	std::map <std::string, std::map <std::string, Info>> map;
	loadMap(mapFile, map);

	if (map.size() == 0)
	{
		std::cout << "\n\tMapa je prazna!";
	}

	std::map <std::string, Info> times;
	times = dijkstra(driverInfo.first->getLocation(), map);

	int option = 0;
	int index = 0;
	int num = 0;
	std::string temp = "";

	while (true)
	{
		system("cls");
		std::cout << "\n\n\tDobrodosli " << name << "!\n"
			<< driverInfo
			<< "\n\n\tOpcije:"
			<< "\n\t\t1 - Odlazak na lokaciju"
			<< "\n\t\t2 - Ispis vremenski najkraceg puta do svake ucitane lokacije"
			<< "\n\t\t3 - Izbaci putnika"
			<< "\n\t\t10 - Izlaz"
			<< "\n\n\t\tOption: ";

		std::cin >> option;

		if (option == 1)
		{
			std::cout << "\n\tNa koju lokaciju zelite otici? ";
			std::cin >> temp;

			for (const std::pair <std::string, Info>& t : times)
			{
				if (temp == t.first and
					t.second.time < std::numeric_limits <float>::max() and
					driverInfo.first->getFuelPercentage() > t.second.fuel)
				{
					driverInfo.first->setFuelPercentage(driverInfo.first->getFuelPercentage() - t.second.fuel);
					driverInfo.first->setLocation(temp);
					loginInfo[driverIndex] = driverInfo;
					times = dijkstra(driverInfo.first->getLocation(), map);

					goto exit;
				}
			}
			std::cout << "\n\tNa unesenu lokaciju ne mozete otici";
		exit:
			std::cout << "\n";
		}
		else if (option == 2)
		{
			for (const std::pair <std::string, Info>& t : times)
			{
				std::cout << "\n\t\t" << t.first << ": ";
				if (t.second.time < std::numeric_limits <float>::max())
				{
					std::cout << t.second.time << " minuta"
						<< "; " << t.second.fuel << "% goriva";
				}
				else
				{
					std::cout << "Nema dostupne putanje";
				}
			}
		}
		else if (option == 3)
		{
			if (driverInfo.first->getTakenSeats() > 0)
			{
				driverInfo.first->setTakenSeats(driverInfo.first->getTakenSeats() - 1);
				loginInfo[driverIndex] = driverInfo;
			}
			else
			{
				std::cout << "\n\tAutobus je prazan";
			}
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

	deleteMemory(loginInfo);
}