#include <iostream>
#include <vector>

#include "Structs.h"

void passenger()
{
	// ucitaj datume

	int option;
	int index;
	int num;

	while (true)
	{
		system("cls");
		std::cout << "\n\n\t    ";

		std::cout << "\n\n\tDobrodosli!\n\tOdaberite opciju:"
			<< "\n\t\t1 - Kupovina nove karte"
			<< "\n\t\t2 - Printanje kupljene karte"
			<< "\n\t\t10 - Izlaz"
			<< "\n\n\t\tOdabir: ";

		std::cin >> option;

		if (option == 1)
		{

		}
		else if (option == 2)
		{

		}
		else if (option == 10)
			return;
		else
		{
			std::cout << "\n\t\tPogresan unos!";
		}
		std::cout << "\n\n\t\t";
		system("pause");
	}
}