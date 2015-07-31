#ifndef DMGCOUNT_H
#define DMGCOUNT_H

#include <SFML/Graphics.hpp>

class DmgCount
{
    public:
    float dmg;
    float alpha;
    bool crit;
    sf::Font font;
    sf::Text text;

    DmgCount();
    void Draw(sf::RenderWindow& window);
};

#endif // DMGCOUNT_H
