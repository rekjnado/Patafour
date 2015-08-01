#include <iostream>
#include <SFML/Graphics.hpp>
#include "dmgcount.h"

using namespace std;

DmgCount::DmgCount()
{
    cout << "LOAD" << endl;
    cout << "LOAD" << endl;
    cout << "LOAD" << endl;
    cout << "LOAD" << endl;
    cout << "LOAD" << endl;
    cout << "LOAD" << endl;

    font.loadFromFile("resources/fonts/opensanslight.ttf");
    dmgtext.setFont(font);
    dmgtext.setCharacterSize(24);

    dmg = 0;
    alpha = 255;
    crit = false;
}

void DmgCount::Draw(sf::RenderWindow& window)
{
    if(crit == true)
    {
    dmgtext.setCharacterSize(24);
    dmgtext.setColor(sf::Color(177,0,0));
    }

    if(crit == false)
    {
    dmgtext.setCharacterSize(16);
    dmgtext.setColor(sf::Color(128,128,128));
    }

    dmgtext.setString("why this isn't working");

    std::cout << dmg << "crit: " << crit << " + a:" << alpha << " >> " << dmgtext.getPosition().x << " : " << dmgtext.getPosition().y << std::endl;

    if(alpha >= 0.10)
    alpha -= 0.5;

    dmgtext.move(0,-1);
    dmgtext.setColor(sf::Color(0,0,0,alpha));

    window.draw(dmgtext);
}
