#include <SFML/Graphics.hpp>
#include <iostream>
#include "spearthrown.h"

using namespace std;

SpearThrown::SpearThrown()
{
    isback = false;
}

void SpearThrown::Throw(float hspd, float vspd, sf::Texture speartex)
{
    spear.setRotation(25);

    vspeed = vspd;
    hspeed = hspd;

    spear.setTexture(speartex);
}

void SpearThrown::Draw(sf::RenderWindow& window)
{
    cout << spear.getPosition().x << ":" << spear.getPosition().y << " " << vspeed << " " << hspeed << " " << spear.getRotation() << " " << isback << endl;
    vspeed += 0.25;

    if(hspeed >= 2)
    hspeed -= 0.05;

    spear.move(hspeed,vspeed);
    spear.rotate(1.15);

    if(spear.getPosition().y>=window.getSize().y)
    isback = false;

    window.draw(spear);
}
