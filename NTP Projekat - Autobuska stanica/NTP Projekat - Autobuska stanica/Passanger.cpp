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

		std::cout << "\n\n\tChoose an option:"
			<< "\n\t\t1 - ispisi redovne voznje"
			<< "\n\t\t2 - Kupi kartu"
			<< "\n\t\t3 - Isprintaj kartu"
			<< "\n\t\t4 - "
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