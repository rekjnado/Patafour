#include <iostream>
#include <SFML/Graphics.hpp>

#include "cutscene.h"

using namespace std;

Cutscene::Cutscene(string cutscenefile)
{
    cout << "hello" << endl;
}

void Cutscene::Play()
{
    isplayed = true;
}

void Cutscene::Stop()
{
    isplayed = false;
}

void Cutscene::Draw(sf::RenderWindow& window)
{
    if(isplayed==true)
    {
    cout << "drawing here" << endl;
    }
}
