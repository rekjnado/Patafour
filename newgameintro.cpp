#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Audio/SoundSource.hpp>
#include "newgameintro.h"

#include "Patafour.h"

using namespace std;
using namespace tinyxml2;

NewGameIntro::NewGameIntro()
{
    cout << "constructor is ok" << endl;
    doc.LoadFile("resources/localization/Polski.xml");
    cout << "loaded language file" << endl;
    intromusic.openFromFile("resources/music/other/newgameintro.ogg");
    cout << "loaded music file" << endl;

    font.loadFromFile("resources/fonts/gara.ttf");

    sf::String tsplash[10];
    string presplash[10];
    presplash[1] = doc.FirstChildElement("Patafour")->FirstChildElement("NewGameIntro")->FirstChildElement("FirstSplash")->GetText();
    presplash[2] = doc.FirstChildElement("Patafour")->FirstChildElement("NewGameIntro")->FirstChildElement("SecondSplash")->GetText();
    presplash[3] = doc.FirstChildElement("Patafour")->FirstChildElement("NewGameIntro")->FirstChildElement("ThirdSplash")->GetText();
    presplash[4] = doc.FirstChildElement("Patafour")->FirstChildElement("NewGameIntro")->FirstChildElement("FourthSplash")->GetText();
    presplash[5] = doc.FirstChildElement("Patafour")->FirstChildElement("NewGameIntro")->FirstChildElement("FifthSplash")->GetText();
    presplash[6] = doc.FirstChildElement("Patafour")->FirstChildElement("NewGameIntro")->FirstChildElement("SixthSplash")->GetText();
    presplash[7] = doc.FirstChildElement("Patafour")->FirstChildElement("NewGameIntro")->FirstChildElement("SeventhSplash")->GetText();

    for(int i=1; i<9; i++)
    {
    cout << i << endl;
    std::basic_string<sf::Uint32> temp;
    sf::Utf8::toUtf32(presplash[i].begin(),presplash[i].end(),std::back_inserter(temp));
    tsplash[i] = temp;
    splash[i].setString(tsplash[i]);
    }

    clock.restart();
    timeout.restart();
    fade.restart();
}

void NewGameIntro::Draw(sf::RenderWindow& window, Patafour* patafour)
{
    int width = window.getSize().x;
    int height = window.getSize().y;

    for(int i=1; i<9; i++)
    {
    splash[i].setFont(font);
    splash[i].setOrigin(splash[i].getGlobalBounds().width/2,splash[i].getGlobalBounds().height/2);
    splash[i].setPosition(width/2,height/2);
    }

    cout << "timeout: " << timeout.getElapsedTime().asSeconds() << endl;

    if(played==false)
        {
            if(clock.getElapsedTime().asSeconds() >= 1.5)
                {
                    intromusic.play();
                    played = true;
                }
        }

    if(timeout.getElapsedTime().asSeconds()>=2.5)
    {
        if(fade.getElapsedTime().asSeconds()<=10)
        {
        if(alpha[0] < 254)
        alpha[0] += 2;
        }

        if(fade.getElapsedTime().asSeconds()>=10)
        {
        if(alpha[0] > 0)
        alpha[0] -= 2;
    }}

    if(timeout.getElapsedTime().asSeconds()>=12)
    {
        if(fade.getElapsedTime().asSeconds()<=20)
        {
        if(alpha[1] <= 252)
        alpha[1] += 2;
        }

        if(fade.getElapsedTime().asSeconds()>=20)
        {
        if(alpha[1]>0)
        alpha[1] -= 2;
    }}

    if(timeout.getElapsedTime().asSeconds()>=22)
    {
        if(fade.getElapsedTime().asSeconds()<=30)
        {
        if(alpha[2] <= 252)
        alpha[2] += 2;
        }

        if(fade.getElapsedTime().asSeconds()>=30)
        {
        if(alpha[2]>0)
        alpha[2] -= 2;
    }}

    if(timeout.getElapsedTime().asSeconds()>=32)
    {
        if(fade.getElapsedTime().asSeconds()<=36)
        {
        if(alpha[3] <= 252)
        alpha[3] += 2;
        }

        if(fade.getElapsedTime().asSeconds()>=36)
        {
        if(alpha[3]>0)
        alpha[3] -= 2;
    }}

    if(timeout.getElapsedTime().asSeconds()>=38)
    {
        if(fade.getElapsedTime().asSeconds()<=43)
        {
        if(alpha[4] <= 252)
        alpha[4] += 2;
        }

        if(fade.getElapsedTime().asSeconds()>=43)
        {
        if(alpha[4]>0)
        alpha[4] -= 2;
    }}

    if(timeout.getElapsedTime().asSeconds()>=45)
    {
        if(fade.getElapsedTime().asSeconds()<=49)
        {
        if(alpha[5] <= 252)
        alpha[5] += 2;
        }

        if(fade.getElapsedTime().asSeconds()>=49)
        {
        if(alpha[5]>0)
        alpha[5] -= 2;
    }}

    if(timeout.getElapsedTime().asSeconds()>=51)
    {
        if(fade.getElapsedTime().asSeconds()<=55)
        {
        if(alpha[6] <= 252)
        alpha[6] += 2;
        }

        if(fade.getElapsedTime().asSeconds()>=55)
        {
        if(alpha[6]>0)
        alpha[6] -= 2;
    }}

    if(timeout.getElapsedTime().asSeconds()>=60)
    {
        patafour->ChangeState(7);
        patafour->SetMissionFile("mission_1.map");
    }

    for(int i=0; i<9; i++)
    {
        splash[i+1].setColor(sf::Color(255,255,255,alpha[i]));
        window.draw(splash[i+1]);
    }
}
