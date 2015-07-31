#include <iostream>
#include <SFML/Graphics.hpp>
#include "patapolis.h"
#include "MaterTreeSubmenu.h"
#include "savecontainer.h"
#include "Patafour.h"

using namespace std;

Patapolis::Patapolis(sf::RenderWindow& window, SaveContainer& savecontainer)
{
    camerax=0;
    chosen=0;
    right=true;
    left=false;
    prefps=0;
    fps=60;
    tex_background.loadFromFile("resources/graphics/patapolis/back.png");
    tex_altar.loadFromFile("resources/graphics/patapolis/altar.png");
    tex_obelisk.loadFromFile("resources/graphics/patapolis/obelisk.png");
    tex_party.loadFromFile("resources/graphics/patapolis/party.png");
    tex_mater.loadFromFile("resources/graphics/patapolis/matertree.png");

    creatingpatapon = false;
    creatingframe = 0;

    background.setTexture(tex_background);
    altar.setTexture(tex_altar);
    obelisk.setTexture(tex_obelisk);
    party.setTexture(tex_party);
    mater.setTexture(tex_mater);

    podloga.setSize(sf::Vector2f(5000,60));
    podloga.setFillColor(sf::Color::Black);
    podloga.setOutlineColor(sf::Color::Black);

    party.setOrigin(tex_party.getSize().x/2,tex_party.getSize().y/2);
    party.setPosition(window.getSize().x,window.getSize().y-(tex_party.getSize().y/2)-59);

    mater.setOrigin(tex_mater.getSize().x/2,tex_mater.getSize().y/2);
    mater.setPosition(window.getSize().x+window.getSize().x,window.getSize().y-(tex_mater.getSize().y/2)-59);

    altar.setOrigin(tex_altar.getSize().x/2,tex_altar.getSize().y/2);
    altar.setPosition(window.getSize().x+window.getSize().x+window.getSize().x,window.getSize().y-(tex_altar.getSize().y/2)-59);

    obelisk.setOrigin(tex_obelisk.getSize().x/2,tex_obelisk.getSize().y/2);
    obelisk.setPosition(window.getSize().x+window.getSize().x+window.getSize().x+window.getSize().x,window.getSize().y-(tex_obelisk.getSize().y/2)-59);

    fpscounter.restart();
    prefps = 10;
}

void Patapolis::Draw(sf::RenderWindow& window, SaveContainer& savecontainer, Patafour* patafour)
{
    window.setView(patapolisview);
    patapolisview.setCenter(sf::Vector2f(0, window.getSize().y/2));
    patapolisview.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));

    /// Patapolis Navigation
    if(fpscounter.getElapsedTime().asSeconds()<=0.1)
    {
    prefps+=10;
    } else {
    fps=prefps+1;
    prefps=0;
    fpscounter.restart();
    }

    background.setScale(6,window.getSize().y/(double)600);
    background.setPosition(-1000,0);
    podloga.setPosition(-1000,window.getSize().y-60);

    party.setPosition(0-camerax,window.getSize().y-(tex_party.getSize().y/2)-59);
    mater.setPosition(2000-camerax,window.getSize().y-(tex_mater.getSize().y/2)-59);
    altar.setPosition(4000-camerax,window.getSize().y-(tex_altar.getSize().y/2)-59);
    obelisk.setPosition(6000-camerax,window.getSize().y-(tex_obelisk.getSize().y/2)-59);

    //if(t imeout <= 0) {
    //if(cameraspeed <= 1) {
    //camerax=chosen*window.getSize().x*2;
    //}
    //}

    if(matersubmenu.opened==false)
    {

    cout << camerax << " " << cameraspeed << " " << right << " " << left << " " << chosen << endl;

    if(timeout <= 0) {
    right = false;
    left = false;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        right = true;
        left = false;
        cameraspeed=44.467;
        chosen+=1;
        timeout = 9.5;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        left = true;
        right = false;
        chosen-=1;
        cameraspeed=44.467;
        timeout = 9.5;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
    {
        creatingpatapon = true;
    }

    }

    timeout -= 0.1;

    if(right==true)
    camerax+=cameraspeed;

    if(left==true)
    camerax-=cameraspeed;

    cameraspeed-=0.5;

    if(cameraspeed<=0)
    cameraspeed=0;

    }

    /// Main Functions
    if(timeout<=0) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
    if(chosen==1)
    {
    if(matersubmenu.opened==false)
    matersubmenu.Open();
    }

    if(chosen==2)
    {
    cout << "inventory open" << endl;
    }

    if(chosen==3)
    {
    patafour->ChangeState(9);
    }

    }
    }

    if(timeout<=0) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
    if(chosen==1)
    {
    if(matersubmenu.buypatapon!=true)
    if(matersubmenu.timeout<=0)
    if(matersubmenu.materorbsareplayed==false)
    matersubmenu.Close();
    }

    if(chosen==2)
    {
    cout << "inventory closed" << endl;
    }

    if(chosen==3)
    {
    cout << "mission closed" << endl;
    }

    }
    }

    window.draw(background);
    window.draw(mater);
    window.draw(altar);

    if(creatingpatapon==true)
    {
    creatingframe+=1;
    cout << creatingframe/(double)fps << "(" << creatingframe << ")" << endl;

    if(creatingframe>=300)
    {
    creatingpatapon=false;
    creatingframe=0;
    }
    }

    window.draw(obelisk);
    window.draw(party);
    window.draw(podloga);

    matersubmenu.Draw(window,savecontainer);
}
