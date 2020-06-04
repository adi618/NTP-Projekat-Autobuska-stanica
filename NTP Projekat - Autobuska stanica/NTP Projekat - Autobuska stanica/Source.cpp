#include <iostream>

void driver();

void pause()
{
	std::cout << "\n\n\t";
	system("pause");
}


int main()
{
	int option;

	while (true)
	{
		system("cls");
		std::cout << "\n\tDobro dosli u autobusku stanicu xy!";

		std::cout << "\n\n\tDa li ste:"
			<< "\n\t\t1 - Vozac?"
			<< "\n\t\t2 - Putnik?"
			<< "\n\t\t3 - Vlasnik?"
			<< "\n\t\t10 - Izlaz"
			<< "\n\n\t\tOdabir: ";

		std::cin >> option;

		if (option == 1)
		{
			driver();
		}
		else if (option == 2)
		{

		}
		else if (option == 3)
		{

		}
		else if (option == 10)
		{
			std::cout << "\n\n\t       \n\n\n";
			return 0;
		}
		else
		{
			std::cout << "\n\t\tPogresan unos!";
		}
		std::cout << "\n\n\t\t";
		system("pause");
	}
}