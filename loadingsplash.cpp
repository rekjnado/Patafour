#include <iostream>
#include "loadingsplash.h"

#include <SFML/Graphics.hpp>

using namespace tinyxml2;

LoadingSplash::LoadingSplash()
{
    tex_splash1.loadFromFile("resources/graphics/nowloading.png");
    tex_splash2.loadFromFile("resources/graphics/nowloading_2.png");

    splash1.setTexture(tex_splash1);
    splash2.setTexture(tex_splash2);
    splash2.setOrigin(splash2.getGlobalBounds().width/2,splash2.getGlobalBounds().height+6);
    splash1.setOrigin(splash1.getGlobalBounds().width/2,splash1.getGlobalBounds().height/2);

    font.loadFromFile("resources/fonts/patapon.ttf");
    text.setString("Now loading");
    text.setColor(sf::Color::White);
    text.setFont(font);
    text.setOrigin(text.getGlobalBounds().width/2,text.getGlobalBounds().height/2);
    text.setCharacterSize(30);

    playing = true;
}

void LoadingSplash::Draw(sf::RenderWindow& window)
{
    if(playing==true)
    {
    text.setPosition(width/2,height/2-130);
    windowsize = window.getSize();
    width = windowsize.x;
    height = windowsize.y;
    splash1.setPosition(width/2,height/2);
    splash2.setPosition(width/2,height/2);
    splash2.rotate(4);
    window.draw(splash1);
    window.draw(splash2);
    window.draw(text);
    }
}

void LoadingSplash::Start()
{
    playing = true;
}

void LoadingSplash::Stop()
{
    playing = false;
}

LoadingSplash::~LoadingSplash()
{
    std::cout << "loading splash went away!~" << std::endl;
}
