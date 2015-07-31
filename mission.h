#ifndef MISSION_H
#define MISSION_H

#include <SFML/Graphics.hpp>
#include "tips.h"
#include <SFML/Audio.hpp>
#include <SFML/Audio/SoundSource.hpp>
#include "beatframe.h"
#include "commandsystem.h"
#include "enemy.h"
#include "cutscene.h"
#include "Patafour.h"
#include "missioncamera.h"
#include "sutra.h"
#include <iostream>

using namespace std;

class Mission
{
    public:
    sf::Texture tex_background[20];
    sf::Sprite background[20];
    sf::Vector2f backSize[20];
    double backMoveX[20];
    sf::Music bgm[30];
    sf::Music shouts_patapata[5];
    sf::Music shouts_ponpon[5];
    sf::Music shouts_chakachaka[5];
    sf::Music shouts_ponchaka[4];
    sf::Music shouts_donchaka[4];
    sf::Music shouts_dondon[4];
    sf::Music shouts_ponpata[4];

    MissionCamera camera;
    Sutra sutra;
    bool cameramove;
    bool cancameramove;

    bool backResizeToWindow[20];
    string currentbgm;
    int backgroundcount;
    bool loaded;
    bool beatframeNotStarted;
    BeatFrame beatframe;
    CommandSystem commandsystem;
    sf::Clock themeClock;
    sf::Clock commandClock;
    sf::Clock failClock;
    sf::Clock nextpressClock;
    int combo;
    int kolej;
    float timeout;

    float fps,prefps;
    sf::Clock fpscounter;

    vector<Enemy> entities;
    vector<Cutscene> cutscenes;

    Mission();
    void Load(string missionfile, sf::RenderWindow& window);
    void Draw(sf::RenderWindow& window, std::string commandbuffer, Patafour* patafour);
    ~Mission();
};

#endif // MISSION_H
