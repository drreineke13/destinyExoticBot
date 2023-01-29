#include "Bot.h"
#include "botCodes.h"

//the main was kept as empty as possible to make it more readable
int main() {
  //initilizes the bot client with the code and bot type
	Bot client(XurBotCode, SleepyDiscord::USER_CONTROLED_THREADS); //token for storm's test bot
  //sets up listening method
	client.setIntents(SleepyDiscord::Intent::SERVER_MESSAGES);
  //runs the setup
	client.setUp();
  //has the bot start listening
	client.run();
}
