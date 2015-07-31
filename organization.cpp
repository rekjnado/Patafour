#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Audio/SoundSource.hpp>

#include "organization.h"
#include "tinyxml2.h"
#include "Patafour.h"
#include <sstream>
#include <math.h>

using namespace tinyxml2;

Organization::Organization(SaveContainer& savecontainer)
{
    selected = 0;
    menu1selected = 0;
    menu2selected = 0;
    menu2open = false;
    doc.LoadFile("resources/localization/Polski.xml");
    sans.loadFromFile("resources/fonts/opensanslight.ttf");

    floor.setSize(sf::Vector2f(10000, 50));
    floor.setFillColor(sf::Color(0, 0, 0));

    bg.setTexture(graphics.Barracks_back);
    bg.setTextureRect(sf::IntRect(0, 0, 100000, 600));
    bg.setPosition(0,0);

    Barracks_ArmyGui.setTexture(graphics.Barracks_ArmyGui);
    Barracks_ArmySelected.setTexture(graphics.Barracks_ArmySelected);

    pataponselected.setTexture(graphics.Barracks_PataponSelected);
    arrow.setTexture(graphics.Barracks_arrow);
    equipgui.setTexture(graphics.Barracks_EquipGui);
    pataponinfo.setTexture(graphics.Barracks_PataponGui);
    pataponoptions.setTexture(graphics.Barracks_PataponOptions);
    Barracks_Icon.setTexture(graphics.emblem[1]);
    Barracks_Icon.setPosition(505,5);

    armytext1.setFont(sans);
    armytext2.setFont(sans);
    armytext3.setFont(sans);

    armytext1.setCharacterSize(34);
    armytext2.setCharacterSize(34);
    armytext3.setCharacterSize(34);

    sf::String sarmytext1;
    string armytext1pre = doc.FirstChildElement("Patafour")->FirstChildElement("Patapolis")->FirstChildElement("Barracks")->FirstChildElement("Show")->GetText();
    std::basic_string<sf::Uint32> tmp1;
    sf::Utf8::toUtf32(armytext1pre.begin(),armytext1pre.end(),std::back_inserter(tmp1));
    sarmytext1 = tmp1;
    armytext1.setString(sarmytext1);

    sf::String sarmytext2;
    string armytext2pre = doc.FirstChildElement("Patafour")->FirstChildElement("Patapolis")->FirstChildElement("Barracks")->FirstChildElement("StartMission")->GetText();
    std::basic_string<sf::Uint32> tmp2;
    sf::Utf8::toUtf32(armytext2pre.begin(),armytext2pre.end(),std::back_inserter(tmp2));
    sarmytext2 = tmp2;
    armytext2.setString(sarmytext2);

    sf::String sarmytext3;
    string armytext3pre = doc.FirstChildElement("Patafour")->FirstChildElement("Patapolis")->FirstChildElement("Barracks")->FirstChildElement("BackToPatapolis")->GetText();
    std::basic_string<sf::Uint32> tmp3;
    sf::Utf8::toUtf32(armytext3pre.begin(),armytext3pre.end(),std::back_inserter(tmp3));
    sarmytext3 = tmp3;
    armytext3.setString(sarmytext3);

    armytext1.setColor(sf::Color::Black);
    armytext2.setColor(sf::Color::Black);
    armytext3.setColor(sf::Color::Black);

    armytext1.setPosition(40,15);
    armytext2.setPosition(40,60);
    armytext3.setPosition(40,105);

    patatext1.setFont(sans);
    patatext2.setFont(sans);
    patatext3.setFont(sans);
    patatext4.setFont(sans);
    patatext5.setFont(sans);

    patatext1.setCharacterSize(34);
    patatext2.setCharacterSize(34);
    patatext3.setCharacterSize(34);
    patatext4.setCharacterSize(34);
    patatext5.setCharacterSize(34);

    cout << "this sucks" << endl;
    sf::String spatatext1;
    string patatext1pre = doc.FirstChildElement("Patafour")->FirstChildElement("Patapolis")->FirstChildElement("Barracks")->FirstChildElement("Equipment")->GetText();
    std::basic_string<sf::Uint32> ttmp1;
    sf::Utf8::toUtf32(patatext1pre.begin(),patatext1pre.end(),std::back_inserter(ttmp1));
    spatatext1 = ttmp1;
    patatext1.setString(spatatext1);

    sf::String spatatext2;
    string patatext2pre = doc.FirstChildElement("Patafour")->FirstChildElement("Patapolis")->FirstChildElement("Barracks")->FirstChildElement("SetSkills")->GetText();
    std::basic_string<sf::Uint32> ttmp2;
    sf::Utf8::toUtf32(patatext2pre.begin(),patatext2pre.end(),std::back_inserter(ttmp2));
    spatatext2 = ttmp2;
    patatext2.setString(spatatext2);

    sf::String spatatext3;
    string patatext3pre = doc.FirstChildElement("Patafour")->FirstChildElement("Patapolis")->FirstChildElement("Barracks")->FirstChildElement("ClassSkills")->GetText();
    std::basic_string<sf::Uint32> ttmp3;
    sf::Utf8::toUtf32(patatext3pre.begin(),patatext3pre.end(),std::back_inserter(ttmp3));
    spatatext3 = ttmp3;
    patatext3.setString(spatatext3);

    sf::String spatatext4;
    string patatext4pre = doc.FirstChildElement("Patafour")->FirstChildElement("Patapolis")->FirstChildElement("Barracks")->FirstChildElement("Rarepon")->GetText();
    std::basic_string<sf::Uint32> ttmp4;
    sf::Utf8::toUtf32(patatext4pre.begin(),patatext4pre.end(),std::back_inserter(ttmp4));
    spatatext4 = ttmp4;
    patatext4.setString(spatatext4);

    sf::String spatatext5;
    string patatext5pre = doc.FirstChildElement("Patafour")->FirstChildElement("Patapolis")->FirstChildElement("Barracks")->FirstChildElement("ChangeName")->GetText();
    std::basic_string<sf::Uint32> ttmp5;
    sf::Utf8::toUtf32(patatext5pre.begin(),patatext5pre.end(),std::back_inserter(ttmp5));
    spatatext5 = ttmp5;
    patatext5.setString(spatatext5);

    patatext1.setColor(sf::Color::Black);
    patatext2.setColor(sf::Color::Black);
    patatext3.setColor(sf::Color::Black);
    patatext4.setColor(sf::Color::Black);
    patatext5.setColor(sf::Color::Black);

    patatext1.setPosition(40,15);
    patatext2.setPosition(40,60);
    patatext3.setPosition(40,105);
    patatext4.setPosition(40,150);
    patatext5.setPosition(40,195);

    pataname.setFont(sans);
    patadesc.setFont(sans);
    pataexp.setFont(sans);
    patadmg.setFont(sans);
    patahp.setFont(sans);
    pataslot1.setFont(sans);
    pataslot2.setFont(sans);
    pataname.setCharacterSize(37);
    patadesc.setCharacterSize(28);
    pataexp.setCharacterSize(28);
    patadmg.setCharacterSize(28);
    patahp.setCharacterSize(28);
    pataslot1.setCharacterSize(29);
    pataslot2.setCharacterSize(29);
    pataname.setColor(sf::Color::Black);
    patadesc.setColor(sf::Color::Black);
    pataexp.setColor(sf::Color::Black);
    patadmg.setColor(sf::Color::Black);
    patahp.setColor(sf::Color::Black);
    pataslot1.setColor(sf::Color::Black);
    pataslot2.setColor(sf::Color::Black);
    pataname.setPosition(560,7);
    patadesc.setPosition(560,40);
    pataexp.setPosition(510,120);
    patadmg.setPosition(510,150);
    patahp.setPosition(510,90);
    pataslot1.setPosition(900,7);
    pataslot2.setPosition(900,40);

    for(int i=0; i<=5; i++)
    {
        if(savecontainer.yaripons[i][1]!="")
        {
            Dummypon temp;
            temp.LoadResources(res);
            temp.PataponType = temp.YARIPON;
            temp.x = 50+i*100;
            yaripons.push_back(temp);
        }
    }

    Dummypon htemp;
    htemp.LoadResources(res);
    htemp.PataponType = htemp.HATAPON;
    htemp.x = 600;
    hatapon.push_back(htemp);

    Dummypon herotemp;
    herotemp.LoadResources(res);
    herotemp.PataponType = herotemp.HERO;
    herotemp.x = 450;
    hero.push_back(herotemp);

    bgm.openFromFile("resources/music/other/organization.ogg");
    bgm.play();
    bgm.setLoop(true);
}

void Organization::Draw(sf::RenderWindow& window, Patafour* patafour)
{
    float width = window.getSize().x;
    float height = window.getSize().y;
    floor.setPosition(0,height-50);
    bg.setScale(width/800,height/600);

    window.draw(bg);
    window.draw(floor);

    for (int i = yaripons.size(); i --> 0;)
    {
        yaripons[i].x = (50+window.getSize().x/35)+i*(window.getSize().x/20);
        yaripons[i].draw(window);
    }

    for(unsigned int i=0; i<hero.size(); i++)
    {
        hero[i].x = window.getSize().x/2;
        hero[i].draw(window);
    }

    for(unsigned int i=0; i<hatapon.size(); i++)
    {
        hatapon[i].x = window.getSize().x-(60+window.getSize().x/50);
        hatapon[i].draw(window);
    }

    if(menu2open == false)
    {
        if(selected == 0)
        {
            pataponselected.setScale((window.getSize().x/20*yaripons.size()+window.getSize().x/35)/(float)126,1);

            if(pataponselected.getScale().x<=1.5)
            pataponselected.setScale(1.5,1);

            pataponselected.setPosition(-7+window.getSize().x/35,window.getSize().y-170);
        }

        if(selected == 1)
        {
            pataponselected.setScale(1,1);
            pataponselected.setPosition(window.getSize().x/2-60,window.getSize().y-170);
        }

        if(selected == 2)
        {
            pataponselected.setScale(1,1);
            pataponselected.setPosition(window.getSize().x-(60+window.getSize().x/50)-60,window.getSize().y-170);
        }

        window.draw(pataponselected);

        arrow.setPosition(15,25+45*menu1selected);

        window.draw(equipgui);
        window.draw(armytext1);
        window.draw(armytext2);
        window.draw(armytext3);
        window.draw(arrow);
    }

    if(menu1selected == 1)
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    bgm.stop();

    if(menu2open == true)
    {
        if(selected == 0)
        {
            pataponselected.setPosition(window.getSize().x/35+(selected2*window.getSize().x/20),window.getSize().y-170);
            pataponselected.setScale(0.85,1);

            pataname.setString(patafour->savecontainer.yaripons[selected2][1]);
            patadesc.setString("lvl "+patafour->savecontainer.yaripons[selected2][0]);
            pataexp.setString(patafour->savecontainer.yaripons[selected2][4]+"/"+patafour->savecontainer.yaripons[selected2][5]+" exp");
            float fmindmg = round(patafour->res.spearmindmg[atof(patafour->savecontainer.yaripons[selected2][6].c_str())]+patafour->res.hatdmg[atof(patafour->savecontainer.yaripons[selected2][6].c_str())]+patafour->res.spearmindmg[atof(patafour->savecontainer.yaripons[selected2][6].c_str())]/3*patafour->res.spearmindmg[atof(patafour->savecontainer.yaripons[selected2][8].c_str())]+(atof(patafour->savecontainer.yaripons[selected2][0].c_str())-1)*2);
            ostringstream smin;
            smin << fmindmg;
            float fmaxdmg = round(patafour->res.spearmaxdmg[atof(patafour->savecontainer.yaripons[selected2][6].c_str())]+patafour->res.hatdmg[atof(patafour->savecontainer.yaripons[selected2][6].c_str())]+patafour->res.spearmaxdmg[atof(patafour->savecontainer.yaripons[selected2][6].c_str())]/3*patafour->res.spearmaxdmg[atof(patafour->savecontainer.yaripons[selected2][8].c_str())]+(atof(patafour->savecontainer.yaripons[selected2][0].c_str())-1)*2.5);
            ostringstream smax;
            smax << fmaxdmg;
            patadmg.setString(smin.str()+"-"+smax.str()+" dmg");
            patahp.setString(patafour->savecontainer.yaripons[selected2][3]+" hp");

        }

        if(selected == 1)
        {
            pataponselected.setScale(1,1);
            pataponselected.setPosition(window.getSize().x/2-60,window.getSize().y-170);
        }

        if(selected == 2)
        {
            pataponselected.setScale(1,1);
            pataponselected.setPosition(window.getSize().x-(60+window.getSize().x/50)-60,window.getSize().y-170);
        }

        window.draw(pataponselected);

        arrow.setPosition(15,25+45*menu2selected);
        pataponinfo.setPosition(500,0);

        window.draw(pataponoptions);
        window.draw(pataponinfo);
        window.draw(patatext1);
        window.draw(patatext2);
        window.draw(patatext3);
        window.draw(patatext4);
        window.draw(patatext5);
        window.draw(pataname);
        window.draw(patadesc);
        window.draw(pataexp);
        window.draw(patadmg);
        window.draw(patahp);
        window.draw(arrow);
    }
}
