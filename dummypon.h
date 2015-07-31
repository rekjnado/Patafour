#ifndef DUMMYPON_H
#define DUMMYPON_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include "resources.h"

using namespace std;

class Dummypon
{
    public:
	sf::Sprite Head;
	sf::Sprite Eye;
	sf::Sprite Arm_L;
	sf::Sprite Arm_R;
	sf::Sprite Leg_L;
	sf::Sprite Leg_R;
	sf::Sprite Hat;
	sf::Sprite Weapon;

    enum pataponTypes
    {
    HATAPON = -1,
    YARIPON = 0,
    TATEPON = 1,
    YUMIPON = 2,
    KIBAPON = 3,
    TORIPON = 4,
    DEKAPON = 5,
    ROBOPON = 6,
    MEGAPON = 7,
    MAHOPON = 8,
    MIKUPON = 9,
    HERO = 9657
    };

	sf::Clock drumAnimationClock;
    int handstate;

	string action;
	string commandbuffer;
	sf::Clock timingclock;
	sf::Time commandclock;

    int PataponType;
    int WeaponID;
    int HatID;

    sf::Clock walkclock;
    int walkcycle;
    bool started;

    int frame;
    int maxframe;
    float hataponrotation;
    float hataponarmrx,hataponarmry;

    PataponRes pata;

    float x,y;
    float baseposition;

    bool cangotobase;

    Dummypon();
    void LoadResources(PataponRes pata);
    void move(float x, float y);
    void draw(sf::RenderWindow& window);
};

#endif
