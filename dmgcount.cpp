#include <iostream>
#include <SFML/Graphics.hpp>
#include "dmgcount.h"
#include <sstream>

DmgCount::DmgCount()
{
    font.loadFromFile("resources/fonts/tekton.ttf");
    text.setFont(font);

    dmg = 0;
    alpha = 255;
    crit = false;
}

void DmgCount::Draw(sf::RenderWindow& window)
{
    if(crit == true)
    {
    text.setCharacterSize(24);
    text.setColor(sf::Color(177,0,0));
    }

    if(crit == false)
    {
    text.setCharacterSize(16);
    text.setColor(sf::Color(128,128,128));
    }

    std::ostringstream ss;
    ss << dmg;
    text.setString("pico i jego ochinchin");

    std::cout << dmg << " + a:" << alpha << " >> " << text.getPosition().x << " : " << text.getPosition().y << std::endl;

    if(alpha >= 0.10)
    alpha -= 0.5;

    text.move(0,-1);
    text.setColor(sf::Color(177,0,0,alpha));

    window.draw(text);
}
