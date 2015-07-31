#ifndef BEATFRAME_H
#define BEATFRAME_H

#include <SFML/Graphics.hpp>

class BeatFrame
{
    public:
    int alpha;
    sf::RectangleShape Frame_1;
    sf::Clock clock;

    BeatFrame();
    void Start();
    void Restart();
    void Draw(sf::RenderWindow& window);
};

#endif // BEATFRAME_H
