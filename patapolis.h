#ifndef PATAPOLIS_H
#define PATAPOLIS_H

#include <SFML/Graphics.hpp>
#include "MaterTreeSubmenu.h"
#include "savecontainer.h"
#include "Patafour.h"

class Patapolis
{
    public:
    sf::Texture tex_background,tex_altar,tex_party,tex_obelisk,tex_mater;
    sf::Sprite background,altar,party,obelisk,mater;
    sf::RectangleShape podloga;
    float camerax;
    float cameraspeed;

    float timeout;

    bool left,right;

    sf::Clock fpscounter;
    int fps,prefps;
    int chosen;

    bool creatingpatapon;
    int creatingframe;

    sf::View patapolisview;

    MaterTreeSubmenu matersubmenu;

    sf::Texture tex_rock1,tex_rock2;
    sf::Texture tex_shovel;

    Patapolis(sf::RenderWindow& window,SaveContainer& savecontainer);
    void Draw(sf::RenderWindow& window,SaveContainer& savecontainer, Patafour* patafour);
};

#endif // PATAPOLIS_H
