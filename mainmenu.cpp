#include <SFML/Graphics.hpp>
#include <iostream>

#include "mainmenu.h"
#include "Patafour.h"

using namespace tinyxml2;
using namespace std;

MainMenu::MainMenu(sf::RenderWindow& window)
{
    menutune.openFromFile("resources/music/other/mainmenu.ogg");
    doc.LoadFile("resources/localization/Polski.xml");
    windowsize = window.getSize();
    width = windowsize.x;
    height = windowsize.y;
    tex_logo.loadFromFile("resources/graphics/teaser/patafourlogo.png");
    logo.setTexture(tex_logo);
    logo.setOrigin(logo.getGlobalBounds().width/2,logo.getGlobalBounds().height/2);
    logo.setPosition(width/2,logo.getGlobalBounds().height/2+32);
    tex_arrow.loadFromFile("resources/graphics/sword.png");
    arrow.setTexture(tex_arrow);
    arrow.setOrigin(arrow.getGlobalBounds().width/2,arrow.getGlobalBounds().height/2);
    arrow.setColor(sf::Color(255,255,255,alpha[1]));

    patapon.loadFromFile("resources/fonts/patapon.ttf");

    timeout = 10;
    selected = 1;

    for(int i=0; i<=5; i++)
    alpha[i]=0;

    text[0].setString(doc.FirstChildElement("Patafour")->FirstChildElement("MainMenu")->FirstChildElement("NewGame")->GetText());
    text[1].setString(doc.FirstChildElement("Patafour")->FirstChildElement("MainMenu")->FirstChildElement("LoadGame")->GetText());
    text[2].setString(doc.FirstChildElement("Patafour")->FirstChildElement("MainMenu")->FirstChildElement("Options")->GetText());
    text[3].setString(doc.FirstChildElement("Patafour")->FirstChildElement("MainMenu")->FirstChildElement("Exit")->GetText());
    //text[4].setString();
    for(int i=0; i<=9; i++)
    {
    text[i].setFont(patapon);
    text[i].setCharacterSize(36);
    text[i].setColor(sf::Color::White);
    text[i].setOrigin(text[i].getGlobalBounds().width/2,text[i].getGlobalBounds().height/2);
    }
}

void MainMenu::Draw(sf::RenderWindow& window, Patafour* patafour)
{
    timeout -= 0.075;
    windowsize = window.getSize();
    width = windowsize.x;
    height = windowsize.y;
    logo.setPosition(width/2,logo.getGlobalBounds().height/2+32);
    arrow.setPosition(width/2-text[selected-1].getGlobalBounds().width,200+selected*40-28);

    if(timeout <= 0) {

    if(selected <= 3)
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    selected+=1;
    timeout = 1;
    }

    if(selected > 1)
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    selected-=1;
    timeout = 1;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
      timeout = 1;
        switch(selected)
        {
            case 1:
            patafour->ChangeState(5);
            menutune.stop();
            break;
            case 2:
            patafour->ChangeState(3);
            menutune.stop();
            break;
            case 3:
            patafour->ChangeState(2);
            menutune.stop();
            break;
            case 4:
            patafour->ChangeState(-3);
            menutune.stop();
            break;
        }
    }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::H)) ///host
    {
        patafour->ChangeState(666);
    }


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::C)) ///client
    {
        patafour->ChangeState(69);
    }

    if(alpha[0]<255)
    alpha[0]+=5;

    if(clock.getElapsedTime().asSeconds()>=1)
    if(alpha[1]<255)
    alpha[1]+=5;

    logo.setColor(sf::Color(255,255,255,alpha[0]));
    arrow.setColor(sf::Color(255,255,255,alpha[1]));

    if(alpha[1]>=250)
    {
        static int k = 0;
        if(k==0) {
        menutune.play();
        k++;
        }
    }

    window.draw(logo);
    window.draw(arrow);

    for(int i=0; i<=4; i++)
    {
    text[i].setPosition(width/2,200+i*40);
    text[i].setColor(sf::Color(255,255,255,alpha[1]));
    window.draw(text[i]);
    }
}
