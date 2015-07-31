#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <sstream>
#include <windows.h>

#include "tips.h"
#include "tinyxml2.h"

#include "Patafour.h"

using namespace std;
using namespace tinyxml2;

template <typename T>
std::string to_string(T value)
{
    std::ostringstream os;
    os << value;
    return os.str();
}


Tips::Tips(Patafour* patafour)
{
    patafour->patapolisloaded = false;
    patafour->missionloaded = false;

    comic.loadFromFile("resources/fonts/comic.ttf");
    tekton.loadFromFile("resources/fonts/tekton.ttf");
    majalla.loadFromFile("resources/fonts/majalla.ttf");

    header.setFont(comic);
    desc.setFont(tekton);
    load.setFont(majalla);

    desc.setColor(sf::Color::White);
    header.setColor(sf::Color::White);

    header.setOrigin(header.getGlobalBounds().width/2,header.getGlobalBounds().height/2);

    char cudzyslow1=0x22;
    string cudzyslow=to_string(cudzyslow1);
    srand(time(NULL));
    int liczba = rand()%4+1;

    finished = false;
    finished2 = false;

    string tips = "tips";
    string fulltip = tips+to_string(liczba);

    string a="pack e",b=".tip";
    string full = a+" "+"resources\\tips\\"+fulltip+b+" -o"+cudzyslow+"resources\\tips\\"+fulltip+"\\"+cudzyslow;

    system(full.c_str());

    string file="resources\\tips\\"+fulltip+"\\"+fulltip+".png";
    string xml="resources\\tips\\"+fulltip+"\\"+fulltip+".xml";

    tex_tips.loadFromFile(file.c_str());
    sprtips.setTexture(tex_tips);
    XMLDocument xmltips;
    xmltips.LoadFile(xml.c_str());

    sf::String desctips,headertips,loadtips;
    string description = xmltips.FirstChildElement("Polski")->FirstChildElement("Description")->GetText();
    string headers = xmltips.FirstChildElement("Polski")->FirstChildElement("Title")->GetText();
    string loads = xmltips.FirstChildElement("Polski")->FirstChildElement("Loading")->GetText();
    string finishes = xmltips.FirstChildElement("Polski")->FirstChildElement("AnyButton")->GetText();

    std::basic_string<sf::Uint32> tmp,tmp2;
    sf::Utf8::toUtf32(description.begin(),description.end(),std::back_inserter(tmp));
    sf::Utf8::toUtf32(headers.begin(),headers.end(),std::back_inserter(tmp2));
    sf::Utf8::toUtf32(loads.begin(),loads.end(),std::back_inserter(tmp3));
    sf::Utf8::toUtf32(finishes.begin(),finishes.end(),std::back_inserter(tmp4));
    desctips = tmp;
    headertips = tmp2;

    desc.setString(desctips);
    header.setString(headertips);

    remove(file.c_str());
    remove(xml.c_str());
    string rm = "rmdir "+cudzyslow+"resources\\tips\\"+fulltip+"\\"+cudzyslow+" /s /q";
    system(rm.c_str());

    clock.restart();
}

void Tips::refresh(Patafour* patafour)
{
    patafour->patapolisloaded = false;
    patafour->missionloaded = false;
    needsrefresh = false;

    char cudzyslow1=0x22;
    string cudzyslow=to_string(cudzyslow1);
    srand(time(NULL));
    int liczba = rand()%4+1;

    finished = false;
    finished2 = false;

    string tips = "tips";
    string fulltip = tips+to_string(liczba);

    string a="pack e",b=".tip";
    string full = a+" "+"resources\\tips\\"+fulltip+b+" -o"+cudzyslow+"resources\\tips\\"+fulltip+"\\"+cudzyslow;

    system(full.c_str());

    string file="resources\\tips\\"+fulltip+"\\"+fulltip+".png";
    string xml="resources\\tips\\"+fulltip+"\\"+fulltip+".xml";

    tex_tips.loadFromFile(file.c_str());
    sprtips.setTexture(tex_tips);
    XMLDocument xmltips;
    xmltips.LoadFile(xml.c_str());

    sf::String desctips,headertips,loadtips;
    string description = xmltips.FirstChildElement("Polski")->FirstChildElement("Description")->GetText();
    string headers = xmltips.FirstChildElement("Polski")->FirstChildElement("Title")->GetText();
    string loads = xmltips.FirstChildElement("Polski")->FirstChildElement("Loading")->GetText();
    string finishes = xmltips.FirstChildElement("Polski")->FirstChildElement("AnyButton")->GetText();

    std::basic_string<sf::Uint32> tmp,tmp2;
    sf::Utf8::toUtf32(description.begin(),description.end(),std::back_inserter(tmp));
    sf::Utf8::toUtf32(headers.begin(),headers.end(),std::back_inserter(tmp2));
    //sf::Utf8::toUtf32(loads.begin(),loads.end(),std::back_inserter(tmp3));
    //sf::Utf8::toUtf32(finishes.begin(),finishes.end(),std::back_inserter(tmp4));
    desctips = tmp;
    headertips = tmp2;

    desc.setString(desctips);
    header.setString(headertips);

    remove(file.c_str());
    remove(xml.c_str());
    string rm = "rmdir "+cudzyslow+"resources\\tips\\"+fulltip+"\\"+cudzyslow+" /s /q";
    system(rm.c_str());

    clock.restart();
}

void Tips::Draw(sf::RenderWindow& window, Patafour* patafour, int location)
{
    if(finished2==true)
    loadtips = tmp4;
    else
    loadtips = tmp3;

    if(clock.getElapsedTime().asSeconds()>=1)
    finished=true;

    if(clock.getElapsedTime().asSeconds()>=2)
    finished2=true;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
    if(finished2==true) {

    if(location==1)
    patafour->patapolisloaded = true;

    if(location==2)
    patafour->missionloaded = true;

    needsrefresh = true;

    }}

    load.setString(loadtips);

    sf::Vector2u windowsize;
    windowsize = window.getSize();
    float width=windowsize.x,height=windowsize.y;
    sprtips.setScale(width/(double)1920,height/(double)1080);
    desc.setPosition(5,27);
    desc.setCharacterSize(width/21.09);
    header.setPosition(10,0);
    header.setCharacterSize(width/20.21);
    header.setOrigin(0,header.getGlobalBounds().height/2);
    load.setCharacterSize(width/23.79);
    load.setOrigin(0,load.getGlobalBounds().height/2);
    load.setPosition(width-load.getGlobalBounds().width-5,height-load.getGlobalBounds().height/2);
    window.draw(sprtips);
    window.draw(desc);
    window.draw(header);
    window.draw(load);
}

Tips::~Tips()
{
    cout << "bye bye~" << endl;
}
