#ifndef RANDOMEXOTIC_HPP
#define RANDOMEXOTIC_HPP
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>
#include <vector>

enum gunTypes { kinetic, energy, heavy, raid };

class GunGen{

	public:
	GunGen();
	bool loadList(std::string kineticFName, std::string energyFName, std::string heavyFName, std::string raidFName);
	int getRandom();
	bool addSearchType(gunTypes gt);
	bool rmSearchType(gunTypes gt);
	void newRand();
	std::vector<gunTypes> showTypes();
	std::string getGun(int i);
	bool getType(int i);
	std::string rollSecondGun(bool grn, int i);

	private:
	std::vector<std::string> kineticGuns;
	std::vector<bool> kinAmmoGrn;
	std::vector<std::string> energyGuns;
	std::vector<bool> engAmmoGrn;
	std::vector<std::string> heavyGuns;
	std::vector<std::string> raidGuns;
	std::vector<gunTypes> searchTypes;
	std::vector<std::string> allUsedGuns;
	std::vector<bool> allAmmoGrn;

};

#endif
