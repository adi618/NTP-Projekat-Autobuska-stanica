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

	Road(std::string location1, std::string location2, float time, float fuel)
		: location1(location1), location2(location2), time(time), fuel(fuel) {}
};

void pause();

void loadInfo(std::ifstream& file, std::vector <std::pair<LocalBus, Driver>>& vec)
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

	while (file >> longDistance)
	{
		file >> ID;
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

		if (time > 0 or fuel > 0)
		{
			if (time > adjMatrix[location1][location2].first)
				adjMatrix[location1][location2] = std::make_pair(time, fuel);
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

std::ostream& operator<<(std::ostream& stream, std::map <std::string, std::map <std::string, std::pair<float, float>>> map)
{
	for (const std::pair<std::string, std::map <std::string, std::pair<float, float>>>& i : map)
	{
		for (const std::pair <std::string, std::pair<float, float>>& j : i.second)
		{
			stream << "\n\tOd " << i.first << " do " << j.first
				<< "\n\tPotrebno vrijeme: " << j.second.first << ", potrebni postotak goriva: " << j.second.second;
		}
	}
	return stream;
}

unsigned long long encryptPassword(std::string password, int i = 0)
{
	if (i >= password.size())
		return -1;

	return (password[i] * 98257 + 67867967) % 1000000007 + encryptPassword(password, i + 1);
}

std::map <std::string, float> dijkstra(std::string source, std::map <std::string, std::map <std::string, std::pair<float, float>>>& adjMatrix)
{
	float MAX = std::numeric_limits <float>::max();
	std::map <std::string, float> dist;
	std::map <std::string, bool> visited;
	for (const std::pair<std::string, std::map <std::string, std::pair<float, float>>>& it : adjMatrix)
	{
		dist[it.first] = MAX;
		visited[it.first] = false;
	}

	dist[source] = 0;

	for (int i = 0; i < adjMatrix.size() - 1; i++)
	{
		float min = MAX;
		std::string minIndex;

		for (const std::pair<std::string, std::map <std::string, std::pair<float, float>>>& v : adjMatrix)
		{
			if (visited[v.first] == false && dist[v.first] <= min)
			{
				min = dist[v.first];
				minIndex = v.first;
			}
		}
		std::string u = minIndex;

		visited[u] = true;

		for (const std::pair<std::string, std::map <std::string, std::pair<float, float>>>& v : adjMatrix)
		{
			if (!visited[v.first] and adjMatrix[u][v.first].first >= 0 and
				dist[u] != MAX and
				dist[u] + adjMatrix[u][v.first].first < dist[v.first])
			{
				dist[v.first] = dist[u] + adjMatrix[u][v.first].first;
			}
		}
	}

	return dist;
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
	std::pair<LocalBus, Driver> driver;
	loadInfo(infoFile, loginInfo);
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
			driver = loginInfo[loginRezult.second];
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

	int option;
	int index;
	int num;

	while (true)
	{
		system("cls");
		std::cout << "\n\n\tDobrodosli " << name
			<< "\n\n\tChoose an option:"
			<< "\n\t\t1 - Ispis mape"
			<< "\n\t\t2 - Odlazak na lokaciju"
			<< "\n\t\t3 - Ispis vremenski najkraceg puta do svake ucitane lokacije"
			<< "\n\t\t4 - "
			<< "\n\t\t5 - Ispis redovnih voznji"
			<< "\n\t\t10 - Izlaz"
			<< "\n\n\t\tOption: ";

		std::cin >> option;

		if (option == 1)
		{
			std::cout << map;
		}
		else if (option == 2)
		{

		}
		else if (option == 3)
		{
			std::map <std::string, float> times = dijkstra(driver.first.getLocation(), map);
			for (const std::pair <std::string, float>& t : times)
			{
				std::cout << "\n\t\t" << t.first << ": ";
				if (t.second > 0)
					std::cout << t.second << "minuta";
				else
					std::cout << "Nema dostupne putanje";
			}
		}
		else if (option == 10)
		{
			return;
		}
		else
		{
			std::cout << "\n\t\tInvalid option!";
		}
		std::cout << "\n\n\t\t";
		system("pause");
	}
}