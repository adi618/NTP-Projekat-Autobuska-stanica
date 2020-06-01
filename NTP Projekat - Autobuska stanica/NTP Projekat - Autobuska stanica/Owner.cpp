#include <iostream>
#include <vector>

#include "Structs.h"

<<<<<<< Updated upstream
=======
void loadDriver(std::vector <Drivers>& vec)
{

	while (true)
	{
		std::cout << "";
	}
};
void deleteDriver(std::vector <Drivers>& vec)
{

};
void printDrivers(std::vector <Drivers>& vec)
{

};
void printBusses(std::vector <Busses>& vec) // jel ima vektor za sve buseve ili su odvojeno local i longDistance?
{

};

>>>>>>> Stashed changes
void owner()
{
	// login
	// ja sam mislio da se vlasnik log inuje samo pomocu passworda, buduci da ima samo jedan vlasnik
	// password vlasnika isto nek bude enkriptiran, kasnije mozemo napravit funkciju za enkriptiranje
	// i taj enkriptirani broj/string nek bude u nekom txt fileu
	
	

	int option;
	int index;
	int num;

	while (true)
	{
		system("cls");
		std::cout << "\n\n\t    ";

		std::cout << "\n\n\tChoose an option:"
			<< "\n\t\t1 - registruj vozaca"		// registrovanje nek snimi vozace u vozaci.txt: ime prezime ID busID password
			<< "\n\t\t2 - otpusti vozaca"
			<< "\n\t\t3 - ispisi sve informacije vozaca"
			<< "\n\t\t4 - ispisi sve informacije autobusa"
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