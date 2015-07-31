#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Audio/SoundSource.hpp>

#include "tinyxml2.h"
#include "Patafour.h"

using namespace tinyxml2;
using namespace std;

class NewGameIntro
{
    public:
    XMLDocument doc;

    sf::Music intromusic;
    sf::Clock clock,timeout,fade;
    bool played;

    sf::Font font;
    sf::Text splash[10];

    float alpha[10];
    bool lighted[10];

    NewGameIntro();
    void Draw(sf::RenderWindow& window, Patafour* patafour);
};
