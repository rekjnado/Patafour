#include <iostream>
#include "shape.h"
#include "projectile.h"

Circle::Circle(int wielkosc, Color kolor, int x, int y)
{
    this->setRadius(wielkosc);
    this->setFillColor(kolor);
    this->setPosition(x,y);
    this->attacked = false;
}

void Circle::moveDown(float speed)
{
	this->move(0.f, speed);
}

void Circle::moveUp(float speed)
{
	this->move(0.f, -speed);
}

void Circle::moveLeft(float speed)
{
	this->move(-speed, 0.f);
}

void Circle::moveRight(float speed)
{
	this->move(speed, 0.f);
}

void Circle::draw(RenderWindow& window)
{
	window.draw(*this);
}

void Circle::play(RenderWindow& window, sf::Texture& weapon, float startx, float starty)
{
static Projectile projectile(window,weapon,startx,starty,5,-6);
window.draw(*this);

if(this->attacked)
	{
	    projectile.fly();
		projectile.draw(window);
		cout << "attacked" << endl;

            if((projectile.getX() > 640)||(projectile.getY() > 480))
            {
            this->attacked = false;
            cout << "not attacked" << endl;
            }

	}
	else
	{
	    projectile.refresh(5,-6,this->getPosition().x,this->getPosition().y);
		//projectile.setPosition(this->getPosition().x,this->getPosition().y);
	}

}

void Circle::attack()
{
    this->attacked = true;
}
