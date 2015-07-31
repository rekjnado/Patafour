#ifndef CUTSCENE_H
#define CUTSCENE_H

#include <SFML/Graphics.hpp>

using namespace std;

class Cutscene
{
    public:
    bool isplayed = false;

    Cutscene(string cutscenefile);
    void Play();
    void Stop();
    void Draw(sf::RenderWindow& window);
};

#endif // CUTSCENE_H
