#pragma once
#include "sleepy_discord/sleepy_discord.h"
#include "imageMsg.h"
#include "randomExotic.hpp"

//header file for bot class

class Bot : public SleepyDiscord::DiscordClient {
public:
	using SleepyDiscord::DiscordClient::DiscordClient;
	void onMessage(SleepyDiscord::Message message) override;
	void setUp();
private:
	bool roll(SleepyDiscord::Message message);
	void help(SleepyDiscord::Message message);
	SleepyDiscord::Embed getImg(std::string txtIn);
	GunGen gg;
	std::vector<gunTypes> sTypes;
};
