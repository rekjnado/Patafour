#include <iostream>
#include "effects.h"

Flash::Flash()
{
    lighted = false;
    alpha = 255;
}

void Flash::Light(float duration)
{
    white.setFillColor(sf::Color(255,255,255,alpha));
    white.setOutlineColor(sf::Color(255,255,255,alpha));

    if(alpha>0)
    alpha -= duration;

    ///automatic data reset
    if(alpha==0)
    {
    lighted = false;
    }
}

void Flash::Draw(float duration, Flash& flash, sf::RenderWindow& window, float x, float y)
{
    if(lighted==true)
    {
    sf::Vector2f temp(x,y);
    white.setSize(temp);
    flash.Light(duration);
    window.draw(white);
    }
}

///Useless functions

void Flash::Flush()
{
    alpha = 255;
}

void Flash::Start()
{
    alpha = 255;
    lighted = true;
}

void Flash::Stop()
{
    alpha = 0;
    lighted = false;
}
