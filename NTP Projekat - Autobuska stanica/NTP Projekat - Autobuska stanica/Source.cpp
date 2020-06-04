#include <iostream>

void driver();
void owner();
void passenger();

void pause()
{
	std::cout << "\n\n\t";
	system("pause");
}

enum option { optDriver = 1, optPassenger, optOwner };

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

		if (option == optDriver)
		{
			driver();
		}
		else if (option == optPassenger)
		{
			passenger();
		}
		else if (option == optOwner)
		{
			owner();
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