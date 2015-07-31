#ifndef PATAPONMULTI_H
#define PATAPONMULTI_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "resources.h"
#include "mission.h"

using namespace std;
using namespace sf;

class PataponMulti
{
    public:
	sf::Sprite Head;
	sf::Sprite Eye;
	sf::Sprite Arm_L;
	sf::Sprite Arm_R;
	sf::Sprite Leg_L;
	sf::Sprite Leg_R;
	sf::Sprite Hat;

	string action;

	float x,y;
    int visiblex,realx;

    PataponMulti();
    void LoadResources(PataponRes& pata);

    void moveUp(float speed);
    void moveDown(float speed);
    void moveLeft(float speed);
    void moveRight(float speed);
    void attack();
    void move(int x, int y);
    void play(RenderWindow& window, sf::Texture& weapon, float startx, float starty);
    void draw(RenderWindow& window, Mission& mission);
    bool attacked;
};

#endif
