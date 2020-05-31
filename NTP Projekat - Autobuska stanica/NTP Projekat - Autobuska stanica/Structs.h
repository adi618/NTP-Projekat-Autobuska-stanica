#pragma once

class LocalBus
{
private:
	int ID;
	std::string driverName;
	std::string driverSurname;
	std::string model;
	float fuelPer100KM;
	float fuelPercentage;
	int totalSeats;
	int takenSeats;
	std::string location;

public:
	LocalBus()
		: ID(0), driverName(""), driverSurname(""), model(""), fuelPer100KM(0), fuelPercentage(0), totalSeats(0), takenSeats(0), location("") {}

	LocalBus(int a, std::string b, std::string c, std::string d, float e, float f, int g, int h, std::string i)
		: ID(a), driverName(b), driverSurname(c), model(d), fuelPer100KM(e), fuelPercentage(f), totalSeats(g), takenSeats(h), location(i) {}

	// get methods:
	int getID() { return ID; }
	std::string getDriverName() { return driverName; }
	std::string getDriverSurname() { return driverSurname; }
	std::string getModel() { return model; }
	float getFuelPer100KM() { return fuelPer100KM; }
	float getFuelPercentage() { return fuelPercentage; }
	int getTotalSeats() { return totalSeats; }
	int getTakenSeats() { return takenSeats; }
	std::string getLocation() { return location; }

	// set methods:
	void setID(int ID) { this->ID = ID; }
	void setDriver(std::string driverName) { this->driverName = driverName; }
	void setDriver(std::string driverSurname) { this->driverSurname = driverSurname; }
	void setModel(std::string model) { this->model = model; }
	void setFuelPer100KM(float fuelPer100KM) { this->fuelPer100KM = fuelPer100KM; }
	void setFuelPercentage(float fuelPercentage) { this->fuelPercentage = fuelPercentage; }
	void setTotalSeats(int totalSeats) { this->totalSeats = totalSeats; }
	void setTakenSeats(int takenSeats) { this->takenSeats = takenSeats; }
	void setLocation(std::string location) { this->location = location; }
};

class LongDistanceBus : public LocalBus
{
private:
	std::string assistantDriver;
	int spareTires;

public:
	LongDistanceBus()
		: LocalBus(), assistantDriver(""), spareTires(0) {}

	LongDistanceBus(int a, std::string b, std::string c, std::string d, float e, float f, int g, int h, std::string i, std::string j, int k)
		: LocalBus(a, b, c, d, e, f, g, h, i), assistantDriver(j), spareTires(k) {}

	std::string getAssistantDriver() { return assistantDriver; }
	int getSpareTires() { return spareTires; }

	void setAssistantDriver(std::string assistantDriver) { this->assistantDriver = assistantDriver; }
	void setSpareTires(int spareTires) { this->spareTires = spareTires; }
};

struct Drivers
{
	std::string name;
	std::string lastname;
	int ID;
	int busID;
	std::string password;
};

struct Dates
{

};