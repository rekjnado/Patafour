#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Audio/SoundSource.hpp>
#include "demomenu.h"
#include "tinyxml2.h"
#include "Patafour.h"

using namespace std;
using namespace tinyxml2;

DemoMenu::DemoMenu()
{
    sel = 0;
    completed = 0;

    azito.openFromFile("resources/music/other/azito.ogg");
    doc.LoadFile("resources/localization/Polski.xml");

    tex_popup.loadFromFile("resources/graphics/demo/menu.png");
    tex_selected.loadFromFile("resources/graphics/demo/select.png");
    popup.setTexture(tex_popup);
    selected.setTexture(tex_selected);
    comicsans.loadFromFile("resources/fonts/comic.ttf");

    selected.setOrigin(tex_selected.getSize().x/2,tex_selected.getSize().y/2);

    title.setFont(comicsans);
    mis1.setFont(comicsans);
    mis2.setFont(comicsans);
    mis3.setFont(comicsans);
    mis4.setFont(comicsans);

    title.setCharacterSize(22);
    mis1.setCharacterSize(22);
    mis2.setCharacterSize(22);
    mis3.setCharacterSize(22);
    mis4.setCharacterSize(22);

    title.setColor(sf::Color::Black);
    mis1.setColor(sf::Color::Black);
    mis2.setColor(sf::Color::Black);
    mis3.setColor(sf::Color::Black);
    mis4.setColor(sf::Color::Black);

    mis1.setOrigin(mis1.getGlobalBounds().width/2,mis1.getGlobalBounds().height/2);
    mis2.setOrigin(mis2.getGlobalBounds().width/2,mis2.getGlobalBounds().height/2);
    mis3.setOrigin(mis3.getGlobalBounds().width/2,mis3.getGlobalBounds().height/2);
    mis4.setOrigin(mis4.getGlobalBounds().width/2,mis4.getGlobalBounds().height/2);

    azito.play();
    azito.setLoop(true);
    clock.restart();
}

void DemoMenu::Draw(sf::RenderWindow& window, Patafour* patafour)
{
    sf::String stitle;
    string titlepre = doc.FirstChildElement("Patafour")->FirstChildElement("Demo")->FirstChildElement("Title")->GetText();
    std::basic_string<sf::Uint32> tmp;
    sf::Utf8::toUtf32(titlepre.begin(),titlepre.end(),std::back_inserter(tmp));
    stitle = tmp;
    title.setString(stitle);

    sf::String smis1;
    string mis1pre = doc.FirstChildElement("Patafour")->FirstChildElement("Demo")->FirstChildElement("FirstQuest")->GetText();
    std::basic_string<sf::Uint32> tmp2;
    sf::Utf8::toUtf32(mis1pre.begin(),mis1pre.end(),std::back_inserter(tmp2));
    smis1 = tmp2;
    mis1.setString(smis1);

    sf::String smis2;
    string mis2pre = doc.FirstChildElement("Patafour")->FirstChildElement("Demo")->FirstChildElement("SecondQuest")->GetText();
    std::basic_string<sf::Uint32> tmp3;
    sf::Utf8::toUtf32(mis2pre.begin(),mis2pre.end(),std::back_inserter(tmp3));
    smis2 = tmp3;
    mis2.setString(smis2);

    sf::String smis3;
    string mis3pre = doc.FirstChildElement("Patafour")->FirstChildElement("Demo")->FirstChildElement("ThirdQuest")->GetText();
    std::basic_string<sf::Uint32> tmp4;
    sf::Utf8::toUtf32(mis3pre.begin(),mis3pre.end(),std::back_inserter(tmp4));
    smis3 = tmp4;
    mis3.setString(smis3);

    sf::String smis4;
    string mis4pre = doc.FirstChildElement("Patafour")->FirstChildElement("Demo")->FirstChildElement("FourthQuest")->GetText();
    std::basic_string<sf::Uint32> tmp5;
    sf::Utf8::toUtf32(mis4pre.begin(),mis4pre.end(),std::back_inserter(tmp5));
    smis4 = tmp5;
    mis4.setString(smis4);

    popup.setOrigin(tex_popup.getSize().x/2,tex_popup.getSize().y/2);
    popup.setPosition(window.getSize().x/2,window.getSize().y/2);

    title.setPosition(popup.getPosition().x-tex_popup.getSize().x/2,popup.getPosition().y-tex_popup.getSize().y/2+7);

    mis1.setPosition(window.getSize().x/2-mis1.getGlobalBounds().width/2,popup.getPosition().y-tex_popup.getSize().y/2+170);
    mis2.setPosition(window.getSize().x/2-mis2.getGlobalBounds().width/2,popup.getPosition().y-tex_popup.getSize().y/2+200);
    mis3.setPosition(window.getSize().x/2-mis3.getGlobalBounds().width/2,popup.getPosition().y-tex_popup.getSize().y/2+230);
    mis4.setPosition(window.getSize().x/2-mis4.getGlobalBounds().width/2,popup.getPosition().y-tex_popup.getSize().y/2+260);

    selected.setPosition(window.getSize().x/2,popup.getPosition().y-tex_popup.getSize().y/2+170+sel*30+tex_selected.getSize().y/2);

    if(completed == 0)
    {
        mis1.setColor(sf::Color::Black);
        mis2.setColor(sf::Color(150,150,150,255));
        mis3.setColor(sf::Color(150,150,150,255));
        mis4.setColor(sf::Color(150,150,150,255));
    }

    if(completed == 1)
    {
        mis1.setColor(sf::Color::Black);
        mis2.setColor(sf::Color::Black);
        mis3.setColor(sf::Color(150,150,150,255));
        mis4.setColor(sf::Color(150,150,150,255));
    }

    if(completed == 2)
    {
        mis1.setColor(sf::Color::Black);
        mis2.setColor(sf::Color::Black);
        mis3.setColor(sf::Color::Black);
        mis4.setColor(sf::Color(150,150,150,255));
    }

    if(completed == 3)
    {
        mis1.setColor(sf::Color::Black);
        mis2.setColor(sf::Color::Black);
        mis3.setColor(sf::Color::Black);
        mis4.setColor(sf::Color::Black);
    }

    if(clock.getElapsedTime().asSeconds()>=1)
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
        if(sel == 0)
        {
            patafour->SetMissionFile("mission_1.map");
        }

        if(sel == 1)
        {
            patafour->SetMissionFile("mission_2.map");
        }

        if(sel == 2)
        {
            patafour->SetMissionFile("mission_3.map");
        }

        if(sel == 3)
        {
            patafour->SetMissionFile("mission_4.map");
        }

        azito.stop();
        patafour->ChangeState(13);
        patafour->menu2wait.restart();
    }

    window.draw(popup);
    window.draw(selected);
    window.draw(title);
    window.draw(mis1);
    window.draw(mis2);
    window.draw(mis3);
    window.draw(mis4);
}
