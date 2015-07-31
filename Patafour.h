#ifndef PATAFOUR_H
#define PATAFOUR_H

#include <SFML/Graphics.hpp>

#include <SFML/Audio.hpp>
#include <SFML/Audio/SoundSource.hpp>

#include "savecontainer.h"
#include "resources.h"
#include "patapon.h"

/// I
/// hate
/// deadlines.

using namespace std;

class Patafour
{
    public:
    sf::RenderWindow window;
    sf::View view;
    sf::Clock startTimeout;
    sf::Clock waiting;
    sf::Clock menu2wait;

    int state;
    int dmenuselect;
    bool destroyed;
    bool patapolisloaded;
    bool missionloaded;
    bool saveloaded;
    bool sutraplayed;
    bool pataponload;
    bool dmenureset;
    bool menu2open;

    string missionfile;
    string commandbuffer;
    string sutrakeybuffer;

    bool troops[6];

    sf::Texture tex_circle;
    sf::Texture tex_hpoutline;
    sf::Texture tex_hpbar;
    sf::Sprite hpoutline[6];
    sf::Sprite hpbar[6];
    sf::Sprite circle[6];

    int TroopType[6];

    enum troopTypes
    {
    HATAPON = -1,
    YARIPON = 0,
    TATEPON = 1,
    YUMIPON = 2,
    KIBAPON = 3,
    TORIPON = 4,
    DEKAPON = 5,
    ROBOPON = 6,
    MEGAPON = 7,
    MAHOPON = 8,
    MIKUPON = 9
    };

    Patapon hatapon;

    std::vector<Patapon> yaripons;
    std::vector<Patapon> tatepons;
    std::vector<Patapon> yumipons;

    sf::Music pata,pon,don,chaka;

    SaveContainer savecontainer;

    PataponRes res;

    int oselected;
    int pataselected;
    int m1selected;
    int m2selected;
    bool oplaysnd;
    bool missionnotcreated;

    Patafour();
    int Main();
    void ChangeState(int gamestate);
    int Exit();
    void SetMissionFile(string file);
};
#endif // PATAFOUR_H
