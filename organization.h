#ifndef ORGANIZATION_H
#define ORGANIZATION_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Audio/SoundSource.hpp>
#include "resources.h"
#include "dummypon.h"
#include "savecontainer.h"
#include "resources.h"
#include "tinyxml2.h"
#include "Patafour.h"

using namespace std;
using namespace tinyxml2;

class Organization
{
    public:
    sf::RectangleShape floor;
    sf::Sprite bg;
    sf::Sprite Barracks_ArmyGui,Barracks_ArmySelected,pataponselected,arrow,equipgui,pataponinfo,pataponoptions,Barracks_Icon;
    OrganizationGraphics graphics;

    sf::Music bgm;
    sf::Font sans;
    XMLDocument doc;

    vector<Dummypon> hatapon;
    vector<Dummypon> yaripons;
    vector<Dummypon> tatepons;
    vector<Dummypon> yumipons;
    vector<Dummypon> hero;

    int selected;
    int selected2;
    int menu1selected;
    int menu2selected;

    bool menu2open;

    PataponRes res;

    sf::Text armytext1,armytext2,armytext3;
    sf::Text patatext1,patatext2,patatext3,patatext4,patatext5;
    sf::Text pataname,patadesc,pataexp,patadmg,patahp,pataslot1,pataslot2;

    Organization(SaveContainer& savecontainer);
    void Draw(sf::RenderWindow& window, Patafour* patafour);
};

#endif // ORGANIZATION_H
