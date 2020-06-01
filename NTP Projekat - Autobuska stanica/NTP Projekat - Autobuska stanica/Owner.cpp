#include <iostream>
#include <vector>
#include <fstream>

#include "Structs.h"


void pause();

void loadDriver(std::vector <Driver>& vec)
{

	while (true)
	{
		std::cout << "";
	}
}

void deleteDriver(std::vector <Driver>& vec)
{

}

void printDrivers(const std::vector <Driver>& vec)
{

}

void printBusses(const std::vector <LocalBus>& vec)
{

}

void owner()
{
	// login

	long passwordOwnerInput;
	long passwordOwnerTrue;
	int numberOfTries = 3;

	std::ifstream ownerPassword("vlasnikSifra.txt");

	if (!ownerPassword.is_open())
	{
		std::cout << "\n\n\tNema registrovanog vlasnika!";
		pause();
		return;
	}
	ownerPassword >> passwordOwnerTrue;

	while (true)
	{
		std::cout << "\n\n\tMolimo unesite Vasu sifru: ";
		std::cin >> passwordOwnerInput;
		numberOfTries--;
		if (passwordOwnerInput == passwordOwnerTrue) // trenutno bez enkripcije
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
	ownerPassword.close();

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