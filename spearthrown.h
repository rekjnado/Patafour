#ifndef SPEARTHROWN_H
#define SPEARTHROWN_H

#include <SFML/Graphics.hpp>
#include <iostream>

class SpearThrown
{
    public:
    sf::Sprite spear;
    float vspeed;
    float hspeed;

    bool isback;

    SpearThrown();
    void Throw(float hspd, float vspd, sf::Texture speartex);
    void Draw(sf::RenderWindow& window);
};

#endif // SPEARTHROWN_H
