#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Audio/SoundSource.hpp>

#include "opening.h"
#include "effects.h"
#include "Patafour.h"

using namespace std;

Opening::Opening(sf::RenderWindow& window)
{
    windowsize = window.getSize();
    width = windowsize.x;
    height = windowsize.y;

    for(int i=0; i<=9; i++)
    alpha[i]=0;

    for(int i=0; i<=9; i++)
    lighted[i]=false;

    beginning.openFromFile("resources/music/other/begin.ogg");
    tex_logo.loadFromFile("resources/graphics/logo.png");
    tex_dhhiss.loadFromFile("resources/graphics/teaser/covethiss.png");
    tex_hero.loadFromFile("resources/graphics/teaser/hero.png");
    tex_naczynie.loadFromFile("resources/graphics/teaser/naczynie.png");
    tex_ravenous.loadFromFile("resources/graphics/teaser/ravenous.png");
    tex_patapons.loadFromFile("resources/graphics/teaser/patapons.png");
    tex_charibassa.loadFromFile("resources/graphics/teaser/charibassa.png");
    tex_naczynie.setSmooth(true);
    tex_ravenous.setSmooth(true);
    tex_patapons.setSmooth(true);
    tex_charibassa.setSmooth(true);
    logo.setTexture(tex_logo);
    logo.setOrigin(tex_logo.getSize().x/2,tex_logo.getSize().y/2);
    logo.setPosition(width/2,height/2);
    dhhiss.setTexture(tex_dhhiss);
    dhhiss.setPosition(width-190,height-242);
    hero.setTexture(tex_hero);
    hero.setPosition(30,height-353);
    font.loadFromFile("resources/fonts/gara.ttf");
    logotext.setString("prezentuje...");
    logotext.setFont(font);
    logotext.setOrigin(logotext.getGlobalBounds().width/2,logotext.getGlobalBounds().height/2);
    logotext.setPosition(width/2,height/2);
    naczynie.setTexture(tex_naczynie);
    ravenous.setTexture(tex_ravenous);
    patapons.setTexture(tex_patapons);
    charibassa.setTexture(tex_charibassa);
    skip.setString("Nacisnij ENTER by pominac...");
    skip.setFont(font);
    skip.setOrigin(skip.getGlobalBounds().width/2,skip.getGlobalBounds().height/2);
    skip.setCharacterSize(16);
    skip.setPosition(width-16,height-4);

    timeout.restart();
    fade.restart();
    beginning.play();
}

Opening::~Opening()
{
    std::cout << "Opening went away!" << endl;
}


void Opening::Draw(sf::RenderWindow& window, Patafour* patafour)
{
    window.draw(naczynie);
    window.draw(ravenous);
    window.draw(patapons);
    window.draw(charibassa);

    windowsize = window.getSize();
    width = windowsize.x;
    height = windowsize.y;
    logo.setPosition(width/2,height/2);
    dhhiss.setPosition(width-190,height-242);
    hero.setPosition(30,height-353);
    logotext.setPosition(width/2,height/2);
    naczynie.setScale(width/(double)1920,height/(double)1080);
    ///cout << width/(double)1920 << ":" << height/(double)1080 << endl;
    ravenous.setScale(width/(double)1920,height/(double)1080);
    patapons.setScale(width/(double)1920,height/(double)1080);
    charibassa.setScale(width/(double)1920,height/(double)1080);

    static Flash flash;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
    patafour->ChangeState(34);
    beginning.pause();
    }

    if(timeout.getElapsedTime().asSeconds()>=3)
    {

        if(fade.getElapsedTime().asSeconds()<=8)
        {
        if(alpha[0] < 254)
        alpha[0]+=2;
        }

        if(fade.getElapsedTime().asSeconds()>=8)
        {
        if(alpha[0]>0)
        alpha[0] -= 2;
    }}

    if(timeout.getElapsedTime().asSeconds()>=12)
    {
        if(fade.getElapsedTime().asSeconds()<=14)
        {
        if(alpha[1] <= 128)
        alpha[1]+=3;
        }

        if(fade.getElapsedTime().asSeconds()>=14)
        {
        if(alpha[1]>0)
        alpha[1] -= 3;
    }}

    if(timeout.getElapsedTime().asSeconds()>=14)
    if(timeout.getElapsedTime().asSeconds()<18)
    {
        if(alpha[8] <= 128)
        alpha[8]+=3;
    }

    if(timeout.getElapsedTime().asSeconds()>=18)
    {
        if(alpha[8] >= 32)
        alpha[8]-=3;
    }

    if(timeout.getElapsedTime().asSeconds()>=15)
    {
        if(fade.getElapsedTime().asSeconds()<=17)
        {
        if(alpha[2] <= 100)
        alpha[2]+=2;
        }

        if(fade.getElapsedTime().asSeconds()>=17)
        {
        if(alpha[2]>0)
        alpha[2] -= 2;
    }}

    if(timeout.getElapsedTime().asSeconds()>=12)
    {
        if(fade.getElapsedTime().asSeconds()<=17)
        {
        if(alpha[3] < 252)
        alpha[3]+=3;
        }

        if(fade.getElapsedTime().asSeconds()>=17)
        {
        if(alpha[3]>0)
        alpha[3] -= 3;
    }}

    if(timeout.getElapsedTime().asSeconds()>=20)
    {
        if(timeout.getElapsedTime().asSeconds()<=20.1)
        alpha[4]=255;

        if(alpha[4]>0)
        alpha[4]-=2.5;
    if(timeout.getElapsedTime().asSeconds()<21.5)
    {

        if(lighted[0]==false)
        {
        flash.Start();
        lighted[0]=true;
        }

        flash.Draw(2.5,flash,window,width,height);
    }}

    if(timeout.getElapsedTime().asSeconds()>=21.5)
    {
        if(timeout.getElapsedTime().asSeconds()<=21.6)
        alpha[5]=255;

        if(alpha[5]>0)
        alpha[5]-=2.5;
    if(timeout.getElapsedTime().asSeconds()<23.1)
    {
        if(lighted[1]==false)
        {
        flash.Start();
        lighted[1]=true;
        }
        flash.Draw(2.5,flash,window,width,height);
    }}

    if(timeout.getElapsedTime().asSeconds()>=23.1)
    {
        if(timeout.getElapsedTime().asSeconds()<=23.2)
        alpha[6]=255;

        if(alpha[6]>0)
        alpha[6]-=2.5;
    if(timeout.getElapsedTime().asSeconds()<24.7)
    {
        if(lighted[2]==false)
        {
        flash.Start();
        lighted[2]=true;
        }
        flash.Draw(2.5,flash,window,width,height);
    }}

    if(timeout.getElapsedTime().asSeconds()>=24.7)
    {
        if(timeout.getElapsedTime().asSeconds()<=24.8)
        alpha[7]=255;

        if(alpha[7]>0)
        alpha[7]-=2.5;

        if(lighted[3]==false)
        {
        flash.Start();
        lighted[3]=true;
        }
        flash.Draw(2.5,flash,window,width,height);
    }

    if(timeout.getElapsedTime().asSeconds()>=48)
    {
        patafour->ChangeState(34);
        beginning.pause();

    }

    ///cout << timeout.getElapsedTime().asSeconds() << endl;

        logo.setColor(sf::Color(255, 255, 255, alpha[0]));
        dhhiss.setColor(sf::Color(255, 255, 255, alpha[1]));
        hero.setColor(sf::Color(255, 255, 255, alpha[2]));
        logotext.setColor(sf::Color(255, 255, 255, alpha[3]));
        naczynie.setColor(sf::Color(255, 255, 255, alpha[4]));
        ravenous.setColor(sf::Color(255, 255, 255, alpha[5]));
        patapons.setColor(sf::Color(255, 255, 255, alpha[6]));
        charibassa.setColor(sf::Color(255, 255, 255, alpha[7]));
        skip.setColor(sf::Color(255, 255, 255, alpha[8]));

        window.draw(logo);
        window.draw(dhhiss);
        window.draw(hero);
        window.draw(logotext);
        window.draw(skip);
}
