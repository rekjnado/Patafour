#ifndef EFFECTS_H
#define EFFECTS_H

#include <SFML/Graphics.hpp>

class Flash
{
    public:
    sf::RectangleShape white;
    float alpha;
    bool lighted;

    Flash();
    void Light(float duration);
    void Draw(float duration, Flash& flash, sf::RenderWindow& window, float x, float y);
    void Flush();
    void Start();
    void Stop();
};

#endif // EFFECTS_H
