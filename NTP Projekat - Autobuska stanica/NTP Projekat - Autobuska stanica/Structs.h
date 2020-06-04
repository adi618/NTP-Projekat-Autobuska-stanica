#pragma once

class LocalBus
{
private:
	int ID;
	float fuelPer100KM;
	float fuelPercentage;
	int totalSeats;
	int takenSeats;
	std::string location;

public:
	LocalBus()
		: ID(0), fuelPer100KM(0), fuelPercentage(0), totalSeats(0), takenSeats(0), location("") {}


	LocalBus(int a, float e, float f, int g, int h, std::string& i)
		: ID(a), fuelPer100KM(e), fuelPercentage(f), totalSeats(g), takenSeats(h), location(i) {}

	// get methods:
	int getID() { return ID; }
	float getFuelPer100KM() { return fuelPer100KM; }
	float getFuelPercentage() { return fuelPercentage; }
	int getTotalSeats() { return totalSeats; }
	int getTakenSeats() { return takenSeats; }
	std::string getLocation() { return location; }

	// set methods:
	void setID(int ID) { this->ID = ID; }
	void setFuelPer100KM(float fuelPer100KM) { this->fuelPer100KM = fuelPer100KM; }
	void setFuelPercentage(float fuelPercentage) { this->fuelPercentage = fuelPercentage; }
	void setTotalSeats(int totalSeats) { this->totalSeats = totalSeats; }
	void setTakenSeats(int takenSeats) { this->takenSeats = takenSeats; }
	void setLocation(const std::string location) { this->location = location; }
};

class LongDistanceBus : public LocalBus
{
private:
	std::string assistantDriver;
	int spareTires;

public:
	LongDistanceBus()
		: LocalBus(), assistantDriver(""), spareTires(0) {}


	LongDistanceBus(int a, float e, float f, int g, int h, std::string& i, std::string& j, int k)
		: LocalBus(a, e, f, g, h, i), assistantDriver(j), spareTires(k) {}

	std::string getAssistantDriver() { return assistantDriver; }
	int getSpareTires() { return spareTires; }

	void setAssistantDriver(const std::string assistantDriver) { this->assistantDriver = assistantDriver; }
	void setSpareTires(int spareTires) { this->spareTires = spareTires; }
};

struct Driver
{
	std::string name;
	std::string lastname;

	unsigned long long encryptedPassword;

	Driver()
		: name(), lastname(""), encryptedPassword(0) {}

	Driver(const std::string& name, const std::string& lastname, unsigned long long encryptedPassword)
		: name(name), lastname(lastname), encryptedPassword(encryptedPassword) {}
};