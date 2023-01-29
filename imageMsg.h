#pragma once
#include "sleepy_discord/sleepy_discord.h"
#include <string>
#include <vector>

//test class for image messages

class ImageMsg{
    public:
    ImageMsg();
    ImageMsg(std::string url);

    void setImage(std::string url);

    SleepyDiscord::Embed genEmbd();

    private:
    std::string url;
    std::string genImg();
};
