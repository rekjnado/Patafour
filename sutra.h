#ifndef SUTRA_H
#define SUTRA_H

#include <SFML/Graphics.hpp>

#include <SFML/Audio.hpp>
#include <SFML/Audio/SoundSource.hpp>

#include "missioncamera.h"
#include "Patafour.h"

#include <map>

using namespace std;

class Sutra
{
    public:
    sf::Texture tex_sutrabackground,tex_sutratotem,tex_pata,tex_pon,tex_don,tex_chaka,tex_tick,tex_beat,tex_overlay;
    sf::Texture tex_pataslider,tex_ponslider,tex_chakaslider,tex_donslider,tex_patasliderend,tex_ponsliderend,tex_chakasliderend,tex_donsliderend;
    sf::Sprite sutrabackground,sutratotem,tick[26],beat,overlay;
    std::vector<sf::Sprite> pataslidersstarts;
    std::vector<sf::Sprite> ponslidersstarts;
    std::vector<sf::Sprite> chakaslidersstarts;
    std::vector<sf::Sprite> donslidersstarts;
    std::vector<sf::Sprite> patasliders;
    std::vector<sf::Sprite> ponsliders;
    std::vector<sf::Sprite> chakasliders;
    std::vector<sf::Sprite> donsliders;
    std::vector<sf::Sprite> pataslidersends;
    std::vector<sf::Sprite> ponslidersends;
    std::vector<sf::Sprite> chakaslidersends;
    std::vector<sf::Sprite> donslidersends;
    std::vector<sf::Sprite> patas;
    std::vector<sf::Sprite> pons;
    std::vector<sf::Sprite> dons;
    std::vector<sf::Sprite> chakas;

    std::map<int,bool> patasliderspress;
    std::map<int,bool> ponsliderspress;
    std::map<int,bool> chakasliderspress;
    std::map<int,bool> donsliderspress;
    std::map<int,bool> patapress;
    std::map<int,bool> ponpress;
    std::map<int,bool> donpress;
    std::map<int,bool> chakapress;

    std::map<int,bool> pataslidersready;
    std::map<int,bool> ponslidersready;
    std::map<int,bool> chakaslidersready;
    std::map<int,bool> donslidersready;
    std::map<int,bool> pataready;
    std::map<int,bool> ponready;
    std::map<int,bool> donready;
    std::map<int,bool> chakaready;

    int pataslidersstartsamount;
    int ponslidersstartsamount;
    int chakaslidersstartsamount;
    int donslidersstartsamount;
    int pataslidersamount;
    int ponslidersamount;
    int chakaslidersamount;
    int donslidersamount;
    int pataslidersendsamount;
    int ponslidersendsamount;
    int chakaslidersendsamount;
    int donslidersendsamount;
    int patasamount;
    int ponsamount;
    int donsamount;
    int chakasamount;

    float points;

    sf::Music sutratune;

    sf::Clock clock;

    bool played;
    int ticklength;

    float beatx,beatspeed;
    float bpm;
    float hitsoundoffset;

    bool press;

    std::map<int,string> timeline;

    Sutra();
    void Load(string sutrafile);
    void Play(MissionCamera camera, sf::RenderWindow& window);
    void Stop();
    void Draw(sf::RenderWindow& window, MissionCamera camera, float fps, Patafour* patafour);
};

#endif // SUTRA_H
