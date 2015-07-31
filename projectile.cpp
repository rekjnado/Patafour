#include <iostream>
#include "projectile.h"

Projectile::Projectile(sf::RenderWindow& window, sf::Texture& wpn, float startx, float starty, float xpower=5, float ypower=-6)
{
    weapon.setTexture(wpn);
    weapon.setScale(0.5,0.5);
    weapon.setOrigin(wpn.getSize().x/2,wpn.getSize().y/2);
    weapon.setPosition(startx,starty);
    weapon.setRotation(30);
    hspeed=xpower;
    vspeed=ypower;
    height=window.getSize().y;
}

void Projectile::fly()
{
    if(weapon.getPosition() != sf::Vector2f(640, 480))
    {
    weapon.move(hspeed,vspeed);

    if(weapon.getRotation()<175)
    weapon.rotate(1.25);

    hspeed-=0.025;
    vspeed+=0.125;

    if(hspeed <= 0)
    hspeed = 0;
    }
}

void Projectile::draw(sf::RenderWindow& window)
{
	window.draw(weapon);
}

void Projectile::setPosition(float x, float y)
{
    weapon.setPosition(x,y);
}

float Projectile::getX()
{
    return weapon.getPosition().x;
}

float Projectile::getY()
{
    return weapon.getPosition().y;
}

void Projectile::refresh(float defXpower,float defYpower, float startX, float startY)
{
    hspeed=defXpower;
    vspeed=defYpower;
    weapon.setRotation(30);
    weapon.setPosition(startX,startY);
}
