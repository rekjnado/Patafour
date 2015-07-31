#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp>
#include "tinyxml2.h"
#include "Patafour.h"

#include <SFML/Audio.hpp>
#include <SFML/Audio/SoundSource.hpp>

using namespace tinyxml2;

class MainMenu
{
    public:
    sf::Texture tex_logo,tex_arrow;
    sf::Sprite logo,arrow;
    sf::Font patapon;
    sf::Text text[10];

    sf::Music menutune;

    sf::Vector2u windowsize;
    int width;
    int height;
    int selected;
    float timeout;

    float alpha[10];

    XMLDocument doc;

    sf::Clock clock;

    MainMenu(sf::RenderWindow& window);
    void Draw(sf::RenderWindow& window, Patafour* patafour);
    void Keyboard(sf::Event& event);
};

#endif // MAINMENU_H
