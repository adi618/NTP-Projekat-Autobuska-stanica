#include <iostream>
#include <vector>

#include "Structs.h"

void passanger()
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
			<< "\n\t\t1 - Ispis redovnih voznji"
			<< "\n\t\t2 - Kupovina nove karte"
			<< "\n\t\t3 - Printanje kupljene karte"
			<< "\n\t\t4 - "
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
			return;
		else
		{
			std::cout << "\n\t\tInvalid option!";
		}
		std::cout << "\n\n\t\t";
		system("pause");
	}
}