#include <iostream>
#include <fstream>
#include <vector>

#include "Structs.h"

void pause();

struct Ticket
{
	std::string currentLocation;
	std::string wantsToVisit;
	std::string name;
	std::string lastname;
	int busIndex;
	int seatNumber;
};

void printTicket(Ticket& tic)
{
	std::ofstream ticketFile("printTicket.txt");
	ticketFile << "\n\t=================================================" << std::endl;
	ticketFile << "\n\tIme i prezime putnika: " << tic.name << " " << tic.lastname << std::endl;
	ticketFile << "\n\tPolazna lokacija: " << tic.currentLocation << std::endl;
	ticketFile << "\n\tOdrediste: " << tic.wantsToVisit << std::endl;
	ticketFile << "\n\tSjediste broj: " << tic.seatNumber << std::endl;
	ticketFile << "\n\t=================================================" << std::endl;
	ticketFile.close();
}

void buyTicket(std::vector <std::pair<LocalBus*, Driver*>>& vec)
{
	Ticket tempTicket;
	std::cout << "\n\n\tUnesite lokaciju na kojoj se nalazite: ";
	std::cin >> tempTicket.currentLocation;

	bool locationExists = false;

	for (std::size_t i = 0; i < vec.size(); i++)
	{
		if (tempTicket.currentLocation == vec[i].first->getLocation() && vec[i].first->getTakenSeats() < vec[i].first->getTotalSeats())
		{
			locationExists = true;
			tempTicket.busIndex = i;
		}
	}

	if (!locationExists)
	{
		std::cout << "\n\n\tZao nam je, na Vasoj lokaciji se ne nalazi nijedan autobus.";
	}
	else
	{
		bool printIt;
		std::cout << "\n\n\tUnesite lokaciju koju zelite posjetiti: ";
		std::cin >> tempTicket.wantsToVisit;
		vec[tempTicket.busIndex].first->setTakenSeats(vec[tempTicket.busIndex].first->getTakenSeats() + 1);
		std::cout << "\tUnesite Vase ime: ";
		std::cin >> tempTicket.name;
		std::cout << "\tUnesite Vase prezime: ";
		std::cin >> tempTicket.lastname;
		tempTicket.seatNumber = vec[tempTicket.busIndex].first->getTakenSeats();

		std::cout << "\n\n\tVasa karta bi izgledala ovako:";
		std::cout << "\n\t================================================="
			<< "\n\tIme i prezime putnika: " << tempTicket.name << " " << tempTicket.lastname
			<< "\n\tPolazna lokacija: " << tempTicket.currentLocation
			<< "\n\tOdrediste: " << tempTicket.wantsToVisit
			<< "\n\tSjediste broj: " << tempTicket.seatNumber
			<< "\n\t=================================================";
		std::cout << "\n\n\tDa li zelite isprintati kartu?\n\t1-DA  0-NE\n\t";
		std::cin >> printIt;
		if (printIt)
		{
			printTicket(tempTicket);
		}
		else
		{
			std::cout << "\n\n\tVasa kupovina je uspjesno obavljena.Sretno!";
		}
	}
}

void printBussesOnCurrentLocation(std::vector <std::pair<LocalBus*, Driver*>>& vec)
{
	std::string currentLocation;
	std::cout << "\n\n\tUnesite lokaciju na kojoj se nalazite: ";
	std::cin >> currentLocation;

	bool locationExists = false;

	for (std::size_t i = 0; i < vec.size(); i++)
	{
		if (currentLocation == vec[i].first->getLocation())
		{
			locationExists = true;
			std::cout << "\n\n\tNa Vasoj lokaciji se nalazi autobus sa ID brojem: " << vec[i].first->getID()
				<< "\n\tOn posjeduje ukupno: " << vec[i].first->getTotalSeats() << " sjedista od cega je " << vec[i].first->getTakenSeats() << " zauzeto.";
		}
	}

	if (!locationExists)
	{
		std::cout << "\n\n\tZao nam je, na Vasoj lokaciji se ne nalazi nijedan autobus.";
	}
}

void loadInfo(std::ifstream& file, std::vector <std::pair<LocalBus*, Driver*>>& vec);

void saveLoginInfo(const std::vector <std::pair<LocalBus*, Driver*>>& loginInfo);

void deleteMemory(const std::vector <std::pair<LocalBus*, Driver*>>& loginInfo);

void passenger()
{
	std::vector <std::pair<LocalBus*, Driver*>> loginInfo;

	std::ifstream infoFile("info.txt");

	if (!infoFile.is_open())
	{
		std::cout << "\n\n\tNema registrovanih vozaca!";
		pause();
	}
	loadInfo(infoFile, loginInfo);
	infoFile.close();
	
	int option;
	while (true)
	{
		system("cls");
		std::cout << "\n\n\t    ";

		std::cout << "\n\n\tDobrodosli!\n\tOdaberite opciju:"
			<< "\n\t\t1 - Kupovina nove karte"
			<< "\n\t\t2 - Ispisi autobuse na trenutnoj lokaciji"
			<< "\n\t\t10 - Izlaz"
			<< "\n\n\t\tOdabir: ";

		std::cin >> option;

		if (option == 1)
		{
			buyTicket(loginInfo);
		}
		else if (option == 2)
		{
			printBussesOnCurrentLocation(loginInfo);
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