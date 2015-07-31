#ifndef TIPS_H
#define TIPS_H

#include <SFML/Graphics.hpp>
#include "Patafour.h"

class Tips
{
    public:
    sf::Texture tex_tips;
    sf::Sprite sprtips;

    sf::Font comic,tekton,majalla;
    sf::Text header,desc,load;

    sf::Clock clock;

    bool finished;
    bool finished2;
    bool needsrefresh;

    std::string loads,finishes;
    sf::String loadtips;
    std::basic_string<sf::Uint32> tmp3,tmp4;

    Tips(Patafour* patafour);
    ///Location:
    ///1 = Patapolis
    ///2 = Mission
    void refresh(Patafour* patafour);
    void Draw(sf::RenderWindow& window, Patafour* patafour, int location);
    ~Tips();
};

#endif // TIPS_H
