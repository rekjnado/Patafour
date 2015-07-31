#ifndef LOADINGSPLASH_H
#define LOADINGSPLASH_H

#include <SFML/Graphics.hpp>
#include "tinyxml2.h"

using namespace tinyxml2;

class LoadingSplash
{
    public:
    sf::Texture tex_splash1,tex_splash2;
    sf::Sprite splash1,splash2;
    sf::Font font;
    sf::Text text;

    sf::Vector2u windowsize;
    int width;
    int height;

    bool playing;

    XMLDocument localize;

    LoadingSplash();
    ~LoadingSplash();
    void Draw(sf::RenderWindow& window);
    void Start();
    void Stop();
};
#endif // LOADINGSPLASH_H
