#include <iostream>
#include "CommandSystem.h"
#include "mission.h"
#include <SFML/Graphics.hpp>
#include "Patafour.h"

using namespace std;

CommandSystem::CommandSystem()
{
timeout = 1;
pata.openFromFile("resources/music/other/pata.ogg");
pon.openFromFile("resources/music/other/pon.ogg");
don.openFromFile("resources/music/other/don.ogg");
chaka.openFromFile("resources/music/other/chaka.ogg");
}

std::string CommandSystem::Play()
{
/*
timeout -= 0.06;

if(timeout <= 0)
{
if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
{
    command+="Pata";
    pata.play();
    timeout = 1;
}

if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
{
    command+="Pon";
    pon.play();
    timeout = 1;
}

if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
{
    command+="Chaka";
    chaka.play();
    timeout = 1;
}

if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
{
    command+="Don";
    don.play();
    timeout = 1;
}

}*/

return command;
}

void CommandSystem::Clear(Patafour* patafour)
{
    command="";
    patafour->commandbuffer = "";
}
