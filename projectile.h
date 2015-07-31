#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class Projectile
{
private:
    float vspeed,hspeed;
    int height;

public:
    sf::Sprite weapon;

    Projectile(sf::RenderWindow& window, sf::Texture& wpn, float startx, float starty, float xpower, float ypower);
    void draw(sf::RenderWindow& window);
    void setPosition(float x, float y);
    void fly();
    float getX();
    float getY();
    void refresh(float defXpower, float defYpower, float startX, float startY);

};

#endif
