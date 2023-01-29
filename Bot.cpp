#include "Bot.h"

std::string botcall = "d2!";

void Bot::onMessage(SleepyDiscord::Message message) {
  //standard call and response test command for the bot
	if (message.startsWith(botcall + " hello")) {
		sendMessage(message.channelID, "Hello " + message.author.username);
	}
  //roll command
	else if (message.startsWith(botcall + " roll")) {
		if (!roll(message)) {
			sendMessage(message.channelID, "Failed to find a gun for " + message.author.username);
		}
	}
  //commands for adding certain gun types to the randomizer
	else if (message.startsWith(botcall + " add kinetic")) {
		if (gg.addSearchType(kinetic)) {
			sendMessage(message.channelID, "Added kinetic type");
		}
		else {
			sendMessage(message.channelID, "Failed to add kinetic type");
		}
	}
	else if (message.startsWith(botcall + " add energy")) {
		if (gg.addSearchType(energy)) {
			sendMessage(message.channelID, "Added energy type");
		}
		else {
			sendMessage(message.channelID, "Failed to add energy type");
		}
	}
	else if (message.startsWith(botcall + " add heavy")) {
		if (gg.addSearchType(heavy)) {
			sendMessage(message.channelID, "Added heavy type");
		}
		else {
			sendMessage(message.channelID, "Failed to add heavy type");
		}
	}
	else if (message.startsWith(botcall + " add raid")) {
		if (gg.addSearchType(raid)) {
			sendMessage(message.channelID, "Added raid type");
		}
		else {
			sendMessage(message.channelID, "Failed to add raid type");
		}
	}
  //commands for removing certian gun types from the randomizer
	else if (message.startsWith(botcall + " remove raid")) {
		if (gg.rmSearchType(raid)) {
			sendMessage(message.channelID, "Removed raid guns");
		}
		else {
			sendMessage(message.channelID, "Failed to remove raid guns");
		}
	}
	else if (message.startsWith(botcall + " remove kinetic")) {
		if (gg.rmSearchType(kinetic)) {
			sendMessage(message.channelID, "Removed kinetic type");
		}
		else {
			sendMessage(message.channelID, "Failed to Remove kinetic type");
		}
	}
	else if (message.startsWith(botcall + " remove energy")) {
		if (gg.rmSearchType(energy)) {
			sendMessage(message.channelID, "Removed energy type");
		}
		else {
			sendMessage(message.channelID, "Failed to remove energy type");
		}
	}
	else if (message.startsWith(botcall + " remove heavy")) {
		if (gg.rmSearchType(heavy)) {
			sendMessage(message.channelID, "Removed heavy type");
		}
		else {
			sendMessage(message.channelID, "Failed to remove heavy type");
		}
	}
  //help command
	else if (message.startsWith(botcall + " help")) {
		help(message);
	}
  //displays the currently enabled weapon types
	else if (message.startsWith(botcall + " types")) {
		std::vector<gunTypes> tps = gg.showTypes();
		bool kin = false;
		bool ene = false;
		bool hev = false;
		bool rd = false;
		for (int i = 0; i < tps.size(); i++) {
			gunTypes gt = tps.at(i);
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
		if (kin) {
			sendMessage(message.channelID, "Kinetic is enabled");
		}
		if (ene) {
			sendMessage(message.channelID, "Energy is enabled");
		}
		if (hev) {
			sendMessage(message.channelID, "Heavy is enabled");
		}
		if (rd) {
			sendMessage(message.channelID, "Raid is enabled");
		}
	}
	else if(message.startsWith(botcall + " image")){
    //test case for image fucntionality
		SleepyDiscord::Embed emb = getImg("");
		sendMessage(message.channelID, "", emb);
	}
}

//rolls to get a random exotic from the pool
bool Bot::roll(SleepyDiscord::Message message) {
	std::vector<gunTypes> tps = gg.showTypes();
	bool kin = false;
	bool ene = false;
	bool hev = false;
	bool rd = false;
	for (int i = 0; i < tps.size(); i++) {
		gunTypes gt = tps.at(i);
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


	gg.newRand();
	int i = gg.getRandom();
	std::string gun = gg.getGun(i);
	bool isGrn = gg.getType(i);
	sendMessage(message.channelID, message.author.username + " rolled : " + gun);
	if ((kin || ene) && (!hev && !rd)) {
		std::string gun2 = gg.rollSecondGun(isGrn, i);
		sendMessage(message.channelID, "Your second gun is a " + gun2);
	}
	return true;
}

//loads the text file lists of all the guns that are stored
void Bot::setUp() {
	gg = GunGen();
	gg.loadList("kineticGuns.txt", "energyGuns.txt", "heavyGuns.txt", "raidGuns.txt");
	gg.addSearchType(kinetic);
	gg.addSearchType(energy);
}

//displays the help message for the bot
void Bot::help(SleepyDiscord::Message message) {
	char c = '0';
	std::string str = "";

	std::ifstream fs("help.txt");
	while (fs.get(c)) {
		if (c != '\n' && c != '\r') {
			str += c;
		}
		else {
			sendMessage(message.channelID, str);
			str = "";
		}

	}
	if (str != "") {
		sendMessage(message.channelID, str);
	}
	fs.close();
}

SleepyDiscord::Embed Bot::getImg(std::string txtIn){
	ImageMsg img(txtIn);
	return img.genEmbd();
}
