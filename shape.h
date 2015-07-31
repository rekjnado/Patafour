#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Kaczka
{
public:
    int kwa;
};

class Circle: public CircleShape
{
    public:
    int width;
    int height;

    Circle(int wielkosc=20, Color kolor=Color::Green, int x=20, int y=20);

    void moveUp(float speed);
    void moveDown(float speed);
    void moveLeft(float speed);
    void moveRight(float speed);
    void attack();
    void play(RenderWindow& window, sf::Texture& weapon, float startx, float starty);
    void draw(RenderWindow& window);
    bool attacked;
};

#endif /// SHAPE_H
