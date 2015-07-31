#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Audio/SoundSource.hpp>

#include "tinyxml2.h"
#include "Patafour.h"

using namespace tinyxml2;

class DemoMenu
{
    public:
    int sel;
    int completed;

    sf::Music azito;

    sf::Texture tex_popup,tex_selected;
    sf::Sprite popup,selected;
    sf::Font comicsans;
    sf::Text title,mis1,mis2,mis3,mis4;

    XMLDocument doc;

    sf::Clock clock;

    DemoMenu();
    void Draw(sf::RenderWindow& window, Patafour* patafour);
};
