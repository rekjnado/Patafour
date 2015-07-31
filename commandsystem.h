#ifndef COMMANDSYSTEM_H
#define COMMANDSYSTEM_H

#include <SFML/Audio.hpp>
#include <SFML/Audio/SoundSource.hpp>

#include "Patafour.h"

class CommandSystem
{
    public:
    float timeout;
    std::string command;
    sf::Music pata,pon,don,chaka;

    CommandSystem();
    std::string Play();
    void Clear(Patafour* patafour);
};

#endif // COMMANDSYSTEM_H
