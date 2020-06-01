#include <iostream>
#include <vector>

#include "Structs.h"

<<<<<<< Updated upstream
<<<<<<< Updated upstream
=======
void loadDriver(std::vector <Drivers>& vec)
=======
void pause();

void loadDriver(std::vector <Driver>& vec)
>>>>>>> Stashed changes
{

	while (true)
	{
		std::cout << "";
	}
};
void deleteDriver(std::vector <Driver>& vec)
{

};
void printDrivers(const std::vector <Driver>& vec)
{

};
void printBusses(const std::vector <LocalBus>& vec)
{

};

>>>>>>> Stashed changes
void owner()
{
	// login
<<<<<<< Updated upstream
	// ja sam mislio da se vlasnik log inuje samo pomocu passworda, buduci da ima samo jedan vlasnik
	// password vlasnika isto nek bude enkriptiran, kasnije mozemo napravit funkciju za enkriptiranje
	// i taj enkriptirani broj/string nek bude u nekom txt fileu
	
	
=======
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
>>>>>>> Stashed changes

	int option;
	int index;
	int num;

	while (true)
	{
<<<<<<< Updated upstream
		system("cls");
		std::cout << "\n\n\t    ";

		std::cout << "\n\n\tChoose an option:"
			<< "\n\t\t1 - registruj vozaca"		// registrovanje nek snimi vozace u vozaci.txt: ime prezime ID busID password
			<< "\n\t\t2 - otpusti vozaca"
			<< "\n\t\t3 - ispisi sve informacije vozaca"
			<< "\n\t\t4 - ispisi sve informacije autobusa"
=======
		system("CLS");
		std::cout << "\n\n\tDobrodosli!"
			<< "\n\n\tOdaberite opciju:"
			<< "\n\t\t1 - Registruj vozaca"
			<< "\n\t\t2 - Otpusti vozaca"
			<< "\n\t\t3 - Ispisi sve informacije o vozacima"
			<< "\n\t\t4 - Ispisi sve informacije o autobusima"
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
			std::cout << "\n\t\tInvalid option!";
		}
=======
			std::cout << "\n\t\tPogresan unos!";
		}

>>>>>>> Stashed changes
		std::cout << "\n\n\t\t";
		system("pause");
	}
}