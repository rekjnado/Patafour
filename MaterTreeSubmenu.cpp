#include <SFML/Graphics.hpp>
#include <iostream>
#include "MaterTreeSubmenu.h"
#include "SaveContainer.h"
#include <sstream>
#include "enemy.h"

using namespace tinyxml2;
using namespace std;

int toint(string str)
{
    int i;
    istringstream iss(str);
    iss >> i;
    return i;
}

MaterTreeSubmenu::MaterTreeSubmenu()
{
    materorbsareplayed = false;
    amountoftries = 0;
    cout << "constructor" << endl;
    doc.LoadFile("resources/localization/Polski.xml");
    opened = false;
    buypatapon = false;
    showcannotbuy = false;
    buyoption = true;

    maxonscreen=4;
    selected = 0;
    timeout = 1;
    horselected = 0;

    tobuy="";

    komika.loadFromFile("resources/fonts/komika.ttf");
    comicsans.loadFromFile("resources/fonts/comic.ttf");

    tex_overlay.loadFromFile("resources/graphics/matersub/overlap.png");
    tex_overlay_dark.loadFromFile("resources/graphics/matersub/overlap_dark.png");

    patatext[0].setString("Yaripon");
    patatext[1].setString("Tatepon");
    patatext[2].setString("Yumipon");
    patatext[3].setString("Kibapon");
    patatext[4].setString("Toripon");
    patatext[5].setString("Dekapon");
    patatext[6].setString("Robopon");
    patatext[7].setString("Megapon");
    patatext[8].setString("Mahopon");

    tex_icon[0].loadFromFile("resources/graphics/matersub/iconspear.png");

    for(int i=0; i<=9; i++)
    {
    patatext[i].setFont(komika);
    patatext[i].setCharacterSize(29);
    patatext[i].setColor(sf::Color::Black);

    overlay[i].setTexture(tex_overlay);
    overlay_dark[i].setTexture(tex_overlay_dark);
    overlay_dark[i].setColor(sf::Color(0,0,0,128));

    icon[i].setTexture(tex_icon[i]);

    visible[i] = false;
    }

    tex_rarepon_default.loadFromFile("resources/graphics/matersub/rarepon_default.png");
    tex_rarepon_default_big.loadFromFile("resources/graphics/matersub/rarepon_default_big.png");
    tex_rarepon_blank.loadFromFile("resources/graphics/matersub/rarepon_blank.png");
    tex_rarepon_blank_big.loadFromFile("resources/graphics/matersub/rarepon_blank_big.png");

    tex_popup_question.loadFromFile("resources/graphics/matersub/popup_question.png");
    tex_popup_selected.loadFromFile("resources/graphics/matersub/popup_selected.png");
    tex_popup_notavailable.loadFromFile("resources/graphics/matersub/popup_notavailable.png");

    popup_question.setTexture(tex_popup_question);
    popup_selected.setTexture(tex_popup_selected);
    popup_notavailable.setTexture(tex_popup_notavailable);

    question.setFont(comicsans);
    question.setCharacterSize(27);
    question.setColor(sf::Color::Black);

    for(int i=0; i<3; i++)
    {
    item[i].setFont(comicsans);
    item[i].setCharacterSize(27);
    }

    yes.setFont(comicsans);
    yes.setCharacterSize(22);
    yes.setColor(sf::Color::Black);

    no.setFont(comicsans);
    no.setCharacterSize(22);
    no.setColor(sf::Color::Black);

    cannotbuy.setFont(comicsans);
    cannotbuy.setCharacterSize(27);
    cannotbuy.setColor(sf::Color::Black);

    close.setFont(comicsans);
    close.setCharacterSize(22);
    close.setColor(sf::Color::Black);


    for(int i=0; i<50; i++)
    {
    rarepon_default[i].setTexture(tex_rarepon_default,true);
    rarepon_default_big[i].setTexture(tex_rarepon_default_big,true);

    rarepon_default[i].setOrigin(tex_rarepon_default.getSize().x/2,tex_rarepon_default.getSize().y/2);
    rarepon_default_big[i].setOrigin(tex_rarepon_default_big.getSize().x/2,tex_rarepon_default_big.getSize().y/2);

    rarepon_blank[i].setTexture(tex_rarepon_blank,true);
    rarepon_blank_big[i].setTexture(tex_rarepon_blank_big,true);

    rarepon_blank[i].setOrigin(tex_rarepon_blank.getSize().x/2,tex_rarepon_blank.getSize().y/2);
    rarepon_blank_big[i].setOrigin(tex_rarepon_blank_big.getSize().x/2,tex_rarepon_blank_big.getSize().y/2);
    }

    tex_arrow.loadFromFile("resources/graphics/matersub/arrow.png");
    tex_background.loadFromFile("resources/graphics/matersub/back.png");

    arrow.setTexture(tex_arrow);
    background.setTexture(tex_background);
    cout << "constructor is done" << endl;
}

void MaterTreeSubmenu::Open()
{
    selected=0;
    horselected=0;
    opened = true;
    buypatapon = false;
    buyoption = true;
}

void MaterTreeSubmenu::Close()
{
    opened = false;
}

void MaterTreeSubmenu::Draw(sf::RenderWindow& window, SaveContainer& savecontainer)
{
    static Enemy materorbs(string("MaterOrbs"),window.getSize().x/2,285);

    if(materorbs.play == true)
    materorbsareplayed = true;
    else
    materorbsareplayed = false;

    if(toMake.size()>=1)
    {
        materorbs.visible = true;
        materorbs.play = true;
        materorbs.repeat = true;

        if(materorbs.currentframe >= materorbs.framelimit[materorbs.currentAnimationID])
        toMake.erase(toMake.begin());
    }

    if(toMake.size()==0)
    {
        materorbs.visible = false;
        materorbs.repeat = false;
        materorbs.play = false;
        materorbs.currentframe = 0;
    }

    materorbs.DrawObjects(window);

    if(opened==true)
    {
        window.draw(background);
        timeout -= 0.05;

        background.setPosition(window.getSize().x-tex_background.getSize().x,0);
        background.setScale(1,window.getSize().y/(50-1));

        if(timeout <= 0)
        {
            if(buypatapon!=true)
            {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                selected += 1;
                timeout = 1;
                horselected = 0;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                selected -= 1;
                timeout = 1;
                horselected = 0;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                timeout = 1;
                horselected -= 1;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                timeout = 1;
                horselected += 1;
            }}

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                    {
                            if(showcannotbuy==true)
                            {
                                timeout = 1;
                                amountoftries += 1;
                                showcannotbuy = false;
                                buypatapon = false;
                            }
                    }

            if(buypatapon==true)
                {
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    {
                        timeout = 1;
                        buypatapon = false;
                    }

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                    {
                        if(showcannotbuy==false)
                        {
                        if(buyoption==true)
                        {
                            timeout = 1;
                            if(tobuy=="yaripon")
                            {
                                if(savecontainer.items[25]>=1)
                                {
                                    if(savecontainer.items[13]>=1)
                                    {
                                        if(savecontainer.kaching>=10)
                                        {
                                            savecontainer.yaripons[horselected][0]="1";
                                            savecontainer.yaripons[horselected][1]="Yaripon";
                                            savecontainer.yaripons[horselected][2]="0";
                                            savecontainer.yaripons[horselected][3]="0";
                                            savecontainer.yaripons[horselected][4]="0";
                                            savecontainer.yaripons[horselected][5]="1";
                                            savecontainer.yaripons[horselected][6]="0";

                                            savecontainer.items[25]-=1;
                                            savecontainer.items[13]-=1;
                                            savecontainer.kaching -= 10;

                                            toMake.push_back("yaripon");

                                            timeout = 1;
                                            buypatapon = false;
                                            amountoftries = 0;
                                        } else {
                                        timeout = 1;
                                        showcannotbuy = true;
                                        }
                                    } else {
                                    timeout = 1;
                                    showcannotbuy = true;
                                    }
                                } else {
                                timeout = 1;
                                showcannotbuy = true;
                                }
                            }
                        }
                        }
                    }
                }

            if(showcannotbuy == false)
            {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                timeout = 1;

                if(selected==0)
                {
                    if(savecontainer.yaripons[horselected][1]=="")
                    {
                        if(buypatapon==false)
                        {
                            sf::String squestion;
                            string questionpre = doc.FirstChildElement("Patafour")->FirstChildElement("Patapolis")->FirstChildElement("MaterSubmenu")->FirstChildElement("CreateYaripon")->GetText();
                            std::basic_string<sf::Uint32> tmp;

                            sf::Utf8::toUtf32(questionpre.begin(),questionpre.end(),std::back_inserter(tmp));

                            squestion = tmp;

                            question.setString(squestion);
                            buyoption = true;
                        }

                        buypatapon = true;
                        tobuy="yaripon";
                    }
                }
            }}

            if(buypatapon==true)
                {
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                    {
                        if(buyoption==false)
                        {
                            timeout = 1;
                            buypatapon = false;
                            amountoftries = 0;
                        }
                    }
                }
        }

        for(int i=0; i<=9; i++)
        {
            if(overlay[i].getPosition().y+104<=window.getSize().y)
            {
                window.draw(overlay[i]);
            }
        }

        for(int p=0; p<=5; p++)
            {

                if(selected==0)
                {
                    if(savecontainer.yaripons[p][1]!="")
                    {
                        if(toint(savecontainer.yaripons[p][3])==0)
                        {
                            rarepon_default[6*selected+p+1].setTexture(tex_rarepon_default,true);
                            rarepon_default_big[6*selected+p+1].setTexture(tex_rarepon_default_big,true);

                            if(horselected==p)
                            {
                                rarepon_default_big[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_default_big[6*selected+p+1]);
                            }

                            if(horselected!=p)
                            {
                                rarepon_default[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_default[6*selected+p+1]);
                            }
                        }
                    } else {
                            rarepon_blank[6*selected+p+1].setTexture(tex_rarepon_blank,true);
                            rarepon_blank_big[6*selected+p+1].setTexture(tex_rarepon_blank_big,true);

                            if(horselected==p)
                            {
                                rarepon_blank_big[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_blank_big[6*selected+p+1]);
                            }

                            if(horselected!=p)
                            {
                                rarepon_blank[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_blank[6*selected+p+1]);
                            }
                    }
                }

                if(selected==1)
                {
                    if(savecontainer.tatepons[p][1]!="")
                    {
                        if(toint(savecontainer.tatepons[p][3])==0)
                        {
                            rarepon_default[6*selected+p+1].setTexture(tex_rarepon_default,true);
                            rarepon_default_big[6*selected+p+1].setTexture(tex_rarepon_default_big,true);

                            if(horselected==p)
                            {
                                rarepon_default_big[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_default_big[6*selected+p+1]);
                            }

                            if(horselected!=p)
                            {
                                rarepon_default[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_default[6*selected+p+1]);
                            }
                        }
                    } else {
                            rarepon_blank[6*selected+p+1].setTexture(tex_rarepon_blank,true);
                            rarepon_blank_big[6*selected+p+1].setTexture(tex_rarepon_blank_big,true);

                            if(horselected==p)
                            {
                                rarepon_blank_big[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_blank_big[6*selected+p+1]);
                            }

                            if(horselected!=p)
                            {
                                rarepon_blank[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_blank[6*selected+p+1]);
                            }
                    }
                }

                if(selected==2)
                {
                    if(savecontainer.yumipons[p][1]!="")
                    {
                        if(toint(savecontainer.yumipons[p][3])==0)
                        {
                            rarepon_default[6*selected+p+1].setTexture(tex_rarepon_default,true);
                            rarepon_default_big[6*selected+p+1].setTexture(tex_rarepon_default_big,true);

                            if(horselected==p)
                            {
                                rarepon_default_big[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_default_big[6*selected+p+1]);
                            }

                            if(horselected!=p)
                            {
                                rarepon_default[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_default[6*selected+p+1]);
                            }
                        }
                    } else {
                            rarepon_blank[6*selected+p+1].setTexture(tex_rarepon_blank,true);
                            rarepon_blank_big[6*selected+p+1].setTexture(tex_rarepon_blank_big,true);

                            if(horselected==p)
                            {
                                rarepon_blank_big[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_blank_big[6*selected+p+1]);
                            }

                            if(horselected!=p)
                            {
                                rarepon_blank[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_blank[6*selected+p+1]);
                            }
                    }
                }

                /**if(selected==3)
                {
                    if(savecontainer.kibapons[p][1]!="")
                    {
                        if(toint(savecontainer.kibapons[p][3])==0)
                        {
                            rarepon_default[6*selected+p+1].setTexture(tex_rarepon_default,true);
                            rarepon_default_big[6*selected+p+1].setTexture(tex_rarepon_default_big,true);

                            if(horselected==p)
                            {
                                rarepon_default_big[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_default_big[6*selected+p+1]);
                            }

                            if(horselected!=p)
                            {
                                rarepon_default[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_default[6*selected+p+1]);
                            }
                        }
                    } else {
                            rarepon_blank[6*selected+p+1].setTexture(tex_rarepon_blank,true);
                            rarepon_blank_big[6*selected+p+1].setTexture(tex_rarepon_blank_big,true);

                            if(horselected==p)
                            {
                                rarepon_blank_big[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_blank_big[6*selected+p+1]);
                            }

                            if(horselected!=p)
                            {
                                rarepon_blank[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_blank[6*selected+p+1]);
                            }
                    }
                }

                if(selected==4)
                {
                    if(savecontainer.toripons[p][1]!="")
                    {
                        if(toint(savecontainer.toripons[p][3])==0)
                        {
                            rarepon_default[6*selected+p+1].setTexture(tex_rarepon_default,true);
                            rarepon_default_big[6*selected+p+1].setTexture(tex_rarepon_default_big,true);

                            if(horselected==p)
                            {
                                rarepon_default_big[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_default_big[6*selected+p+1]);
                            }

                            if(horselected!=p)
                            {
                                rarepon_default[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_default[6*selected+p+1]);
                            }
                        }
                    } else {
                            rarepon_blank[6*selected+p+1].setTexture(tex_rarepon_blank,true);
                            rarepon_blank_big[6*selected+p+1].setTexture(tex_rarepon_blank_big,true);

                            if(horselected==p)
                            {
                                rarepon_blank_big[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_blank_big[6*selected+p+1]);
                            }

                            if(horselected!=p)
                            {
                                rarepon_blank[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_blank[6*selected+p+1]);
                            }
                    }
                }

                if(selected==5)
                {
                    if(savecontainer.dekapons[p][1]!="")
                    {
                        if(toint(savecontainer.dekapons[p][3])==0)
                        {
                            rarepon_default[6*selected+p+1].setTexture(tex_rarepon_default,true);
                            rarepon_default_big[6*selected+p+1].setTexture(tex_rarepon_default_big,true);

                            if(horselected==p)
                            {
                                rarepon_default_big[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_default_big[6*selected+p+1]);
                            }

                            if(horselected!=p)
                            {
                                rarepon_default[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_default[6*selected+p+1]);
                            }
                        }
                    } else {
                            rarepon_blank[6*selected+p+1].setTexture(tex_rarepon_blank,true);
                            rarepon_blank_big[6*selected+p+1].setTexture(tex_rarepon_blank_big,true);

                            if(horselected==p)
                            {
                                rarepon_blank_big[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_blank_big[6*selected+p+1]);
                            }

                            if(horselected!=p)
                            {
                                rarepon_blank[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_blank[6*selected+p+1]);
                            }
                    }
                }

                if(selected==6)
                {
                    if(savecontainer.robopons[p][1]!="")
                    {
                        if(toint(savecontainer.robopons[p][3])==0)
                        {
                            rarepon_default[6*selected+p+1].setTexture(tex_rarepon_default,true);
                            rarepon_default_big[6*selected+p+1].setTexture(tex_rarepon_default_big,true);

                            if(horselected==p)
                            {
                                rarepon_default_big[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_default_big[6*selected+p+1]);
                            }

                            if(horselected!=p)
                            {
                                rarepon_default[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_default[6*selected+p+1]);
                            }
                        }
                    } else {
                            rarepon_blank[6*selected+p+1].setTexture(tex_rarepon_blank,true);
                            rarepon_blank_big[6*selected+p+1].setTexture(tex_rarepon_blank_big,true);

                            if(horselected==p)
                            {
                                rarepon_blank_big[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_blank_big[6*selected+p+1]);
                            }

                            if(horselected!=p)
                            {
                                rarepon_blank[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_blank[6*selected+p+1]);
                            }
                    }
                }

                if(selected==7)
                {
                    if(savecontainer.megapons[p][1]!="")
                    {
                        if(toint(savecontainer.megapons[p][3])==0)
                        {
                            rarepon_default[6*selected+p+1].setTexture(tex_rarepon_default,true);
                            rarepon_default_big[6*selected+p+1].setTexture(tex_rarepon_default_big,true);

                            if(horselected==p)
                            {
                                rarepon_default_big[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_default_big[6*selected+p+1]);
                            }

                            if(horselected!=p)
                            {
                                rarepon_default[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_default[6*selected+p+1]);
                            }
                        }
                    } else {
                            rarepon_blank[6*selected+p+1].setTexture(tex_rarepon_blank,true);
                            rarepon_blank_big[6*selected+p+1].setTexture(tex_rarepon_blank_big,true);

                            if(horselected==p)
                            {
                                rarepon_blank_big[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_blank_big[6*selected+p+1]);
                            }

                            if(horselected!=p)
                            {
                                rarepon_blank[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_blank[6*selected+p+1]);
                            }
                    }
                }

                if(selected==8)
                {
                    if(savecontainer.mahopons[p][1]!="")
                    {
                        if(toint(savecontainer.mahopons[p][3])==0)
                        {
                            rarepon_default[6*selected+p+1].setTexture(tex_rarepon_default,true);
                            rarepon_default_big[6*selected+p+1].setTexture(tex_rarepon_default_big,true);

                            if(horselected==p)
                            {
                                rarepon_default_big[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_default_big[6*selected+p+1]);
                            }

                            if(horselected!=p)
                            {
                                rarepon_default[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_default[6*selected+p+1]);
                            }
                        }
                    } else {
                            rarepon_blank[6*selected+p+1].setTexture(tex_rarepon_blank,true);
                            rarepon_blank_big[6*selected+p+1].setTexture(tex_rarepon_blank_big,true);

                            if(horselected==p)
                            {
                                rarepon_blank_big[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_blank_big[6*selected+p+1]);
                            }

                            if(horselected!=p)
                            {
                                rarepon_blank[6*selected+p+1].setPosition(window.getSize().x-tex_overlay.getSize().x+90+52*p,137+150*selected);
                                window.draw(rarepon_blank[6*selected+p+1]);
                            }
                    }
                } */
            }

        for(int i=0; i<=9; i++)
        {
            overlay[i].setPosition(window.getSize().x-tex_overlay.getSize().x,70+150*i);
            overlay_dark[i].setPosition(window.getSize().x-tex_overlay.getSize().x,70+150*i);
            overlay_dark[i].setColor(sf::Color(0,0,0,128));

            patatext[i].setPosition(window.getSize().x-tex_overlay.getSize().x+68,70+150*i);

            icon[i].setPosition(window.getSize().x-tex_overlay.getSize().x+3,73+150*i);

            if(overlay[i].getPosition().y+104<=window.getSize().y)
            {
                maxonscreen=i+1;
                window.draw(patatext[i]);
                window.draw(icon[i]);

                if(selected!=i)
                {
                window.draw(overlay_dark[i]);
                }
            }
        }

    if(buypatapon==true)
    {
        if(showcannotbuy==false)
        {
            popup_question.setPosition(window.getSize().x/2-tex_popup_question.getSize().x/2,window.getSize().y/2-tex_popup_question.getSize().y/2);
            question.setPosition(window.getSize().x/2-tex_popup_question.getSize().x/2-76,window.getSize().y/2-tex_popup_question.getSize().y/2-33);
            window.draw(popup_question);
            window.draw(question);

            if(tobuy=="yaripon")
            {
                sf::String item1,item2,item3;
                string item1prepre = doc.FirstChildElement("Patafour")->FirstChildElement("Items")->FirstChildElement("ID25")->GetText();
                string item1pre = item1prepre+" x1";
                string item2prepre = doc.FirstChildElement("Patafour")->FirstChildElement("Items")->FirstChildElement("ID13")->GetText();
                string item2pre = item2prepre+" x1";
                string item3prepre = doc.FirstChildElement("Patafour")->FirstChildElement("Items")->FirstChildElement("Ka-ching")->GetText();
                string item3pre = string("10 ")+item3prepre;
                std::basic_string<sf::Uint32> tmp1,tmp2,tmp3;
                sf::Utf8::toUtf32(item1pre.begin(),item1pre.end(),std::back_inserter(tmp1));
                sf::Utf8::toUtf32(item2pre.begin(),item2pre.end(),std::back_inserter(tmp2));
                sf::Utf8::toUtf32(item3pre.begin(),item3pre.end(),std::back_inserter(tmp3));
                item1 = tmp1;
                item2 = tmp2;
                item3 = tmp3;
                item[0].setString(item1);
                item[1].setString(item2);
                item[2].setString(item3);

                if(savecontainer.items[25]>=1)
                item[0].setColor(sf::Color(0,90,0,255));
                else
                item[0].setColor(sf::Color(139,0,0,255));

                if(savecontainer.items[13]>=1)
                item[1].setColor(sf::Color(0,90,0,255));
                else
                item[1].setColor(sf::Color(139,0,0,255));

                if(savecontainer.kaching>=10)
                item[2].setColor(sf::Color(0,90,0,255));
                else
                item[2].setColor(sf::Color(139,0,0,255));

                item[0].setOrigin(item[0].getLocalBounds().width/2,item[0].getLocalBounds().height/2);
                item[1].setOrigin(item[1].getLocalBounds().width/2,item[1].getLocalBounds().height/2);
                item[2].setOrigin(item[2].getLocalBounds().width/2,item[2].getLocalBounds().height/2);

                item[0].setPosition(window.getSize().x/2-tex_popup_question.getSize().x/2+item[0].getLocalBounds().width/2+20,window.getSize().y/2-tex_popup_question.getSize().y/2+88);
                item[1].setPosition(window.getSize().x/2-tex_popup_question.getSize().x/2+item[1].getLocalBounds().width/2+20,window.getSize().y/2-tex_popup_question.getSize().y/2+122);
                item[2].setPosition(window.getSize().x/2-tex_popup_question.getSize().x/2+item[2].getLocalBounds().width/2+20,window.getSize().y/2-tex_popup_question.getSize().y/2+160);

                sf::String syes,sno;
                string preyes = doc.FirstChildElement("Patafour")->FirstChildElement("Patapolis")->FirstChildElement("MaterSubmenu")->FirstChildElement("Yes")->GetText();
                string preno = doc.FirstChildElement("Patafour")->FirstChildElement("Patapolis")->FirstChildElement("MaterSubmenu")->FirstChildElement("No")->GetText();
                std::basic_string<sf::Uint32> temp1,temp2;
                sf::Utf8::toUtf32(preyes.begin(),preyes.end(),std::back_inserter(temp1));
                sf::Utf8::toUtf32(preno.begin(),preno.end(),std::back_inserter(temp2));
                syes = temp1;
                sno = temp2;
                yes.setString(syes);
                no.setString(sno);

                yes.setOrigin(yes.getLocalBounds().width/2,yes.getLocalBounds().height/2);
                no.setOrigin(no.getLocalBounds().width/2,no.getLocalBounds().height/2);

                yes.setPosition(window.getSize().x/2,window.getSize().y/2+78);
                no.setPosition(window.getSize().x/2,window.getSize().y/2+103);
            }

            if(buyoption==true)
            {
                popup_selected.setPosition(window.getSize().x/2-tex_popup_selected.getSize().x/2,window.getSize().y/2+69);
            } else {
                popup_selected.setPosition(window.getSize().x/2-tex_popup_selected.getSize().x/2,window.getSize().y/2+95);
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            buyoption=true;

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            buyoption=false;

            for(int i=0; i<3; i++)
            {
                window.draw(item[i]);
            }

            window.draw(yes);
            window.draw(no);
            window.draw(popup_selected);
        } else {
            sf::String scantbuy,sclose,EEcantbuy;
            string precantbuy = doc.FirstChildElement("Patafour")->FirstChildElement("Patapolis")->FirstChildElement("MaterSubmenu")->FirstChildElement("NotEnough")->GetText();
            string preclose = doc.FirstChildElement("Patafour")->FirstChildElement("Patapolis")->FirstChildElement("MaterSubmenu")->FirstChildElement("Close")->GetText();
            string preEEcantbuy = doc.FirstChildElement("Patafour")->FirstChildElement("Patapolis")->FirstChildElement("MaterSubmenu")->FirstChildElement("NotEnough2")->GetText();
            std::basic_string<sf::Uint32> temp1,temp2,temp3;
            sf::Utf8::toUtf32(precantbuy.begin(),precantbuy.end(),std::back_inserter(temp1));
            sf::Utf8::toUtf32(preclose.begin(),preclose.end(),std::back_inserter(temp2));
            sf::Utf8::toUtf32(preEEcantbuy.begin(),preEEcantbuy.end(),std::back_inserter(temp3));
            scantbuy = temp1;
            sclose = temp2;
            EEcantbuy = temp3;

            if(amountoftries <= 10)
            cannotbuy.setString(scantbuy);

            if(amountoftries >= 11)
            cannotbuy.setString(EEcantbuy);

            close.setString(sclose);

            popup_notavailable.setPosition(window.getSize().x/2-tex_popup_notavailable.getSize().x/2,window.getSize().y/2-tex_popup_notavailable.getSize().y/2);
            cannotbuy.setPosition(window.getSize().x/2-tex_popup_notavailable.getSize().x/2-76,window.getSize().y/2-tex_popup_notavailable.getSize().y/2-33);

            close.setOrigin(close.getLocalBounds().width/2,close.getLocalBounds().height/2);
            close.setPosition(window.getSize().x/2,window.getSize().y/2+44);
            popup_selected.setPosition(window.getSize().x/2-tex_popup_selected.getSize().x/2,window.getSize().y/2+32);

            window.draw(popup_notavailable);
            window.draw(cannotbuy);
            window.draw(close);
            window.draw(popup_selected);
        }
    }

    }



}
