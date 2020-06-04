#include <iostream>
#include <vector>
#include <fstream>
#include <map>

#include "Structs.h"



void pause();

void loadInfoTxt(std::ifstream& file, std::vector <std::pair<LocalBus, Driver>>& vec)
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
}

void loadMap(std::ifstream& file, std::map <std::string, std::map <std::string, std::pair<float, float>>>& adjMatrix, bool undirected = true)
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
			if (time > adjMatrix[location1][location2].first)
			{
				adjMatrix[location1][location2] = std::make_pair(time, fuel);
				if (undirected)
				{
					adjMatrix[location2][location1] = std::make_pair(time, fuel);
				}
			}
		}
	}
}

std::pair <bool, int> loginConfirmation
(std::string name, std::string lastname, unsigned long long password, const std::vector <std::pair<LocalBus, Driver>>& loginInfo)
{
	for (int i = 0; i < loginInfo.size(); i++)
	{
		if (name == loginInfo[i].second.name and
			lastname == loginInfo[i].second.lastname and
			password == loginInfo[i].second.encryptedPassword)
		{
			return std::make_pair(true, i);
		}
	}
	return std::make_pair(false, -1);
}

std::ostream& operator<<(std::ostream& stream, std::pair <LocalBus, Driver>& driver)
{

	stream << "\n\tPostotak goriva: " << driver.first.getFuelPercentage();
	stream << "\n\tPotrosnja po 100 kilometara: " << driver.first.getFuelPer100KM();
	stream << "\n\tBroj zauzetih sjedista: " << driver.first.getTakenSeats();
	stream << "\n\tBroj ukupnih sjedista: " << driver.first.getTotalSeats();
	stream << "\n\tTrenutna lokacija: " << driver.first.getLocation();

	return stream;
}

std::ostream& operator<<(std::ostream& stream, std::map <std::string, std::map <std::string, std::pair<float, float>>> map)
{
	for (const std::pair<std::string, std::map <std::string, std::pair<float, float>>>& i : map)
	{
		for (const std::pair <std::string, std::pair<float, float>>& j : i.second)
		{
			stream << "\n\n\tOd " << i.first << " do " << j.first
				<< "\n\tPotrebno vrijeme: " << j.second.first << ", potrebni postotak goriva: " << j.second.second;
		}
	}
	return stream;
}

unsigned long long encryptPassword(std::string password, unsigned i = 0)
{
	if (i >= password.size())
		return -1;

	return (password[i] * 98257 + 67867967) % 1000000007 + encryptPassword(password, i + 1);
}

std::map <std::string, std::pair<float, float>> dijkstra
(std::string source, std::map <std::string, std::map <std::string, std::pair<float, float>>>& adjMatrix)
{
	float MAX = std::numeric_limits <float>::max();
	std::map <std::string, std::pair<float, float>> time;
	std::map <std::string, bool> visited;
	for (const std::pair<std::string, std::map <std::string, std::pair<float, float>>>& it : adjMatrix)
	{
		time[it.first].first = MAX;
		time[it.first].second = 0;
		visited[it.first] = false;
	}

	time[source].first = 0;

	for (int i = 0; i < adjMatrix.size() - 1; i++)
	{
		float min = MAX;
		std::string minIndex;

		for (const std::pair<std::string, std::map <std::string, std::pair<float, float>>>& v : adjMatrix)
		{
			if (visited[v.first] == false && time[v.first].first <= min)
			{
				min = time[v.first].first;
				minIndex = v.first;
			}
		}
		std::string u = minIndex;

		visited[u] = true;

		for (const std::pair<std::string, std::map <std::string, std::pair<float, float>>>& v : adjMatrix)
		{
			if (!visited[v.first] and
				adjMatrix[u][v.first].first > 0 and
				time[u].first != MAX and
				time[u].first + adjMatrix[u][v.first].first < time[v.first].first)
			{
				time[v.first].first = time[u].first + adjMatrix[u][v.first].first;
				time[v.first].second = time[u].second + adjMatrix[u][v.first].second;
			}
		}
	}

	return time;
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

	std::vector <std::pair<LocalBus, Driver>> loginInfo;
	std::pair<LocalBus, Driver> driverInfo;
	loadInfoTxt(infoFile, loginInfo);
	std::string name;
	std::string lastname;
	std::string password;
	int numberOfTries = 3;
	std::pair <bool, int> loginRezult;

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
			driverInfo = loginInfo[loginRezult.second];
			pause();
			break;
		}
		else if (numberOfTries > 0)
		{
			std::cout << "\n\tPogresan unos!\n\tPreostalo pokusaja: " << numberOfTries;
		}
		else
		{
			pause();
		}
	}

	std::map <std::string, std::map <std::string, std::pair<float, float>>> map;
	loadMap(mapFile, map);

	if (map.size() == 0)
	{
		std::cout << "\n\tMapa je prazna!";
	}

	std::map <std::string, std::pair <float, float>> times = dijkstra(driverInfo.first.getLocation(), map);

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
			<< "\n\t\t1 - Ispis mape"
			<< "\n\t\t2 - Odlazak na lokaciju"
			<< "\n\t\t3 - Ispis vremenski najkraceg puta do svake ucitane lokacije"
			<< "\n\t\t10 - Izlaz"
			<< "\n\n\t\tOption: ";

		std::cin >> option;

		if (option == 1)
		{
			std::cout << map;
		}
		else if (option == 2)
		{
			for (const std::pair <std::string, std::pair <float, float>>& t : times)
			{
				if (t.second.first == std::numeric_limits <float>::max())
				{
					std::cout << "\n\t\t" << t.first << ": "
						<< t.second.first << " minuta"
						<< "; " << t.second.second << "% goriva";
				}
			}

			std::cout << "\n\tNa koju lokaciju zelite otici? ";
			std::cin >> temp;
		}
		else if (option == 3)
		{
			for (const std::pair <std::string, std::pair <float, float>>& t : times)
			{
				std::cout << "\n\t\t" << t.first << ": ";
				if (t.second.first < std::numeric_limits <float>::max())
				{
					std::cout << t.second.first << " minuta"
						<< "; " << t.second.second << "% goriva";
				}
				else
				{
					std::cout << "Nema dostupne putanje";
				}
			}
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