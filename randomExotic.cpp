#include "randomExotic.hpp"

//seeds the random number generator
GunGen::GunGen(){
	srand(time(NULL));
}

void GunGen::newRand() {
	srand(time(NULL));
}

//loads the list of guns into the vector
bool GunGen::loadList(std::string kineticFName, std::string energyFName, std::string heavyFName, std::string raidFName){
	std::ifstream fs(kineticFName);
	
	char c = 'a'; //char to store the current character
	
	std::string str = ""; //string to store the name
	 
	while(fs.get(c)){ //gets the current character
		if(c != '\n' && c != '\r'){ //if its not the end of a line,
			if (c == ',') {
				fs.get(c);
				if (c == 'g') {
					kinAmmoGrn.push_back(true);
				}
				else if(c == 'k'){
					kinAmmoGrn.push_back(false);
				}
			}
			else {
				str += c; //adds it to the string
			}
		}
		else{ //if its the end of the line
			if(!str.empty()){ //if the string is not empty
				kineticGuns.push_back(str); //adds the string to the list
				str = ""; //clears the string
			}
		}
	}
	if (str != "") { //after, if the string is not empty
		kineticGuns.push_back(str); //adds it to the list
		str = "";
	}
	fs.close(); //closes the file

	//opens the heavy text file
	fs.open(heavyFName);
	while (fs.get(c)) { //gets the current character
		if (c != '\n' && c != '\r') { //if its not the end of a line,
			str += c; //adds it to the string
		}
		else { //if its the end of the line
			if (!str.empty()) { //if the string is not empty
				heavyGuns.push_back(str); //adds the string to the list
				str = ""; //clears the string
			}
		}
	}
	if (str != "") { //after, if the string is not empty
		heavyGuns.push_back(str); //adds it to the list
		str = "";
	}
	fs.close();

	fs.open(energyFName);
	while (fs.get(c)) { //gets the current character
		if (c != '\n' && c != '\r') { //if its not the end of a line,
			if (c == ',') {
				fs.get(c);
				if (c == 'g') {
					engAmmoGrn.push_back(true);
				}
				else if(c == 'k'){
					engAmmoGrn.push_back(false);
				}
			}
			else {
				str += c; //adds it to the string
			}
		}
		else { //if its the end of the line
			if (!str.empty()) { //if the string is not empty
				energyGuns.push_back(str); //adds the string to the list
				str = ""; //clears the string
			}
		}
	}
	if (str != "") { //after, if the string is not empty
		energyGuns.push_back(str); //adds it to the list
		str = "";
	}
	fs.close();

	fs.open(raidFName);
	while (fs.get(c)) { //gets the current character
		if (c != '\n' && c != '\r') { //if its not the end of a line,
			str += c; //adds it to the string
		}
		else { //if its the end of the line
			if (!str.empty()) { //if the string is not empty
				raidGuns.push_back(str); //adds the string to the list
				str = ""; //clears the string
			}
		}
	}
	if (str != "") { //after, if the string is not empty
		raidGuns.push_back(str); //adds it to the list
	}
	fs.close();

	return true;
}

//gets a random item from the list
int GunGen::getRandom() {
	bool kin = false;
	bool ene = false;
	bool hev = false;
	bool rd = false;
	for (int i = 0; i < searchTypes.size(); i++) {
		gunTypes gt = searchTypes.at(i);
		switch (gt)
		{
		case kinetic:
			kin = true;
			break;
		case energy:
			ene = true;
			break;
		case heavy:
			hev = true;
			break;
		case raid:
			rd = true;
			break;
		}
	}

	allUsedGuns.clear();
	allAmmoGrn.clear();
	//all 4 types
	if (kin) {
		for (int i = 0; i < kineticGuns.size(); i++) {
			allUsedGuns.push_back(kineticGuns.at(i));
			allAmmoGrn.push_back(kinAmmoGrn.at(i));
		}
	}
	if (ene) {
		for (int i = 0; i < energyGuns.size(); i++) {
			allUsedGuns.push_back(energyGuns.at(i));
			allAmmoGrn.push_back(engAmmoGrn.at(i));
		}
	}
	if (hev) {
		for (int i = 0; i < heavyGuns.size(); i++) {
			allUsedGuns.push_back(heavyGuns.at(i));
			allAmmoGrn.push_back(false);
		}
	}
	if (rd) {
		for (int i = 0; i < raidGuns.size(); i++) {
			allUsedGuns.push_back(raidGuns.at(i));
			allAmmoGrn.push_back(false);
		}
	}

	if (allUsedGuns.size() == 0) {
		return -1;
	}

	int i = std::rand() % allUsedGuns.size(); //gets a number mod the size of the list

	return i;
}

//adds a new type to be searched
bool GunGen::addSearchType(gunTypes gt) {
	for (int i = 0; i < searchTypes.size(); i++) {
		if (gt == searchTypes.at(i)) {
			return false;
		}
	}
	searchTypes.push_back(gt);
	return true;
}

//removes a weapon type from the search
bool GunGen::rmSearchType(gunTypes gt) {
	std::vector<gunTypes> newVect;
	for (int i = 0; i < searchTypes.size(); i++) {
		if (gt != searchTypes.at(i)) {
			newVect.push_back(searchTypes.at(i));
		}
	}
	searchTypes = newVect;
	return true;
}

//lists the current types
std::vector<gunTypes> GunGen::showTypes() {
	return this->searchTypes;
}

//attempts to get a weapon at location i
std::string GunGen::getGun(int i) {
	if (i == -1) {
		return "failed to find gun";
	}
	return allUsedGuns.at(i);
}

//attempts to get a weapon type at location i
bool GunGen::getType(int i) {
	if (i == -1) {
		return false;
	}
	return allAmmoGrn.at(i);
}

//rolls for a secondary weapon type
//this feature needs work, something is having it only
//give stasis fusions
std::string GunGen::rollSecondGun(bool grn, int i) {

	std::vector<std::string> LGunTypes;
	if (grn) {
		LGunTypes.push_back("Auto Rifle");
		LGunTypes.push_back("Bow");
		LGunTypes.push_back("Hand Cannon");
		LGunTypes.push_back("Pulse Rifle");
		LGunTypes.push_back("Scout Rifle");
		LGunTypes.push_back("Sidearm");
		LGunTypes.push_back("Submachine Gun");
	}
	else {
		LGunTypes.push_back("Fusion Rifle");
		LGunTypes.push_back("Grenade Launcher");
		LGunTypes.push_back("Shotgun");
		LGunTypes.push_back("Sniper Rifle");
		if(i < kineticGuns.size()){
			LGunTypes.push_back("Trace Rifle");
		}
	}

	std::vector<std::string> element;

	if (i < kineticGuns.size()) {
		element.push_back("solar");
		element.push_back("arc");
		element.push_back("void");
	}
	else {
		element.push_back("stasis");
		element.push_back("kinetic");
	}

	int j = std::rand();

	std::string out = LGunTypes.at(j % LGunTypes.size());
	out = out + " of " + element.at(j % element.size()) + " type.";
	return out;
}
