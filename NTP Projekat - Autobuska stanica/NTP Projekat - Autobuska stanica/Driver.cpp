#include <iostream>
#include <vector>
#include <fstream>

#include "Structs.h"

struct Road
{
	std::string location1, location2;
	float time;
	float fuel;
};


void driver()
{
	std::ifstream file("nesta.txt");

	if (!file.is_open())
	{
		std::cout << "\n\n\tNema registrovanih vozaca!";
		return;
	}

	// login

	std::vector <Road> map;

	// iz mapa.txt upis u road
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