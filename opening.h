#ifndef OPENING_H
#define OPENING_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Audio/SoundSource.hpp>

#include "Patafour.h"

class Opening
{
    public:
    float alpha[10];
    sf::Music beginning;
    sf::Texture tex_logo,tex_dhhiss,tex_hero,tex_naczynie,tex_ravenous,tex_patapons,tex_charibassa;
    sf::Sprite logo,dhhiss,hero,naczynie,ravenous,patapons,charibassa;
    sf::Clock timeout,fade;
    sf::Font font;
    sf::Text logotext,skip;

    sf::Vector2u windowsize;
    int width;
    int height;

    bool lighted[10];

    Opening(sf::RenderWindow& window);
    ~Opening();
    void Draw(sf::RenderWindow& window, Patafour* patafour);
};


#endif
