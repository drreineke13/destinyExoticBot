#include "imageMsg.h"

//implementation of the imagemsg class

//constructor for the class
ImageMsg::ImageMsg(){
    this->url = genImg();
}

//constructor with string input
ImageMsg::ImageMsg(std::string url){
    this->url = url;
}

//command to set the url
void ImageMsg::setImage(std::string url){
    this->url = url;
}

//creates an embed object for output within a message
SleepyDiscord::Embed ImageMsg::genEmbd(){
    SleepyDiscord::EmbedImage img;
    img.url = this->url;

    SleepyDiscord::Embed emb;
    emb.image = img;

    return emb;
}

//unfinished code to fetch an image from a website/locally stored to display in 
//a discord message
std::string ImageMsg::genImg(){
    std::string urlOut = "";


    return urlOut;
}
