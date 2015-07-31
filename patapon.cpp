#include <iostream>
#include <SFML/Graphics.hpp>
#include "patapon.h"
#include "spearthrown.h"

using namespace std;

Patapon::Patapon()
{
    x=100;
    y=100;
    baseposition = x+0;
    action = "idle";
    drumAnimationClock.restart();
    handstate = 0;
    commandbuffer = "";
    cangotobase = true;
    WeaponID = 1;
    HatID = 1;

    walkclock.restart();
    walkcycle = 1;
    started = false;
    hataponrotation = 0;

    frame = 0;
    maxframe = 0;

    hataponarmrx = 0;
    hataponarmry = 0;

    pata.LoadAllWeapons();
    spear.spear.setPosition(0,4000);

    vspeed = 0;
    hspeed = 0;
}

void Patapon::LoadResources(PataponRes pata)
{
    Head.setTexture(pata.Head);
    Eye.setTexture(pata.Eye);
    Leg_L.setTexture(pata.Leg_L);
    Leg_R.setTexture(pata.Leg_R);
    Arm_L.setTexture(pata.Arm_L);
    Arm_R.setTexture(pata.Arm_R);
    Head.setScale(0.5,0.5);
    Eye.setScale(0.5,0.5);
    Leg_L.setScale(0.5,0.5);
    Leg_R.setScale(0.5,0.5);
    Arm_L.setScale(0.5,0.5);
    Arm_R.setScale(0.5,0.5);
    Head.setOrigin(pata.Head.getSize().x/2,pata.Head.getSize().y/2);
    Eye.setOrigin(pata.Eye.getSize().x/2,pata.Eye.getSize().y/2);
    Head.setPosition(x,y);
    Eye.setPosition(x,y);
    Leg_L.setPosition(x-18,y+27);
    Leg_R.setPosition(x+6,y+27);
    Arm_L.setPosition(x-47,y);
    Arm_R.setPosition(x+25,y);

    pata.LoadAllWeapons();
}

void Patapon::move(float x, float y)
{
    Head.move(x,y);
    Eye.move(x,y);
    Leg_L.move(x,y);
    Leg_R.move(x,y);
    Arm_L.move(x,y);
    Arm_R.move(x,y);
    x+=x;
    y+=y;
}

void Patapon::draw(sf::RenderWindow& window)
{
    Head.setScale(0.5,0.5);
    Eye.setScale(0.5,0.5);
    Leg_L.setScale(0.5,0.5);
    Leg_R.setScale(0.5,0.5);
    Arm_L.setScale(0.5,0.5);
    Arm_R.setScale(0.5,0.5);
    Head.setOrigin(pata.Head.getSize().x/2,pata.Head.getSize().y/2);
    Eye.setOrigin(pata.Eye.getSize().x/2,pata.Eye.getSize().y/2);
    Head.setPosition(x,y);
    Eye.setPosition(x,y);
    Leg_L.setPosition(x-18,y+27);
    Leg_R.setPosition(x+6,y+27);
    Arm_L.setPosition(x-47,y);
    Arm_R.setPosition(x+25,y);

    Head.setTexture(pata.Head);
    Eye.setTexture(pata.Eye);
    Leg_L.setTexture(pata.Leg_L);
    Leg_R.setTexture(pata.Leg_R);
    Arm_L.setTexture(pata.Arm_L);
    Arm_R.setTexture(pata.Arm_R);
    Hat.setTexture(pata.hattex[HatID]);
    Hat.setOrigin(pata.hattex[HatID].getSize().x/2,pata.hattex[HatID].getSize().y);
    Hat.setPosition(x,y-23);

    if(PataponType == HATAPON)
    {
    Head.setPosition(x,y);
    Eye.setPosition(x,y);
    Leg_L.setPosition(x-18,y+27);
    Leg_R.setPosition(x+6,y+27);
    Arm_L.setPosition(x-22,y+8);
    Arm_R.setPosition(x+6,y);
    Leg_L.setTexture(pata.Leg_L,true);
    Leg_R.setTexture(pata.Leg_R,true);
    Arm_L.setTexture(pata.Hatapon_Arm_L_Idle,true);
    Arm_R.setTexture(pata.Hatapon_Arm_R_Idle,true);
    Weapon.setPosition(x+3,y+45);
    Weapon.setOrigin(pata.hatatex[WeaponID].getSize().x/2,pata.hatatex[WeaponID].getSize().y+8);
    Weapon.setTexture(pata.hatatex[WeaponID],true);
    }

    if(PataponType == YARIPON)
    {
    Arm_R.setTexture(pata.Arm_R_Holding,true);
    Arm_R.setPosition(x+25,y-8);

    Weapon.setPosition(x+18+pata.Arm_R_Holding.getSize().x/2,y-8);
    Weapon.setRotation(0);
    Weapon.setOrigin(pata.speartex[WeaponID].getSize().x/2,pata.speartex[WeaponID].getSize().y/2);
    Weapon.setTexture(pata.speartex[WeaponID],true);
    }

    if(PataponType != HATAPON)
    {
    Head.setPosition(x,y);
    Eye.setPosition(x,y);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        handstate = 1;
        drumAnimationClock.restart();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        handstate = 2;
        drumAnimationClock.restart();
    }

    if(drumAnimationClock.getElapsedTime().asSeconds()>=0.25) {
        handstate = 0;
    }

    if(handstate==2)
    {
    Head.setPosition(x,y);
    Eye.setPosition(x+6,y-6);
    Leg_L.setPosition(x-23,y+27);
    Leg_R.setPosition(x+6,y+22);
    Arm_L.setPosition(x-48,y);
    Arm_R.setPosition(x+25,y-40);
    Leg_L.setTexture(pata.Leg_L_Pon,true);
    Leg_R.setTexture(pata.Leg_R_Pon,true);
    Arm_L.setTexture(pata.Arm_L_Pon,true);
    Arm_R.setTexture(pata.Arm_R_Pon,true);

    Weapon.setRotation(-20);
    Weapon.setPosition(x+10+pata.Arm_R_Holding.getSize().x/2,y-38);
    }

    if(handstate==1)
    {
    Head.setPosition(x,y);
    Leg_L.setPosition(x-18,y+27);
    Leg_R.setPosition(x+6,y+27);
    Arm_R.setPosition(x+25,y);
    Leg_L.setTexture(pata.Leg_L_Pata,true);
    Leg_R.setTexture(pata.Leg_R_Pata,true);
    Arm_L.setTexture(pata.Arm_L_Pata,true);
    Arm_L.setPosition(x-50,y-40);
    Arm_R.setTexture(pata.Arm_R_Pata,true);
    Eye.setPosition(x-6,y-6);

    Weapon.setRotation(35);
    Weapon.setPosition(x+15+pata.Arm_R_Holding.getSize().x/2,y+10);
    }

    if(handstate==0)
    {
    Head.setPosition(x,y);
    Eye.setPosition(x,y);
    Leg_L.setPosition(x-18,y+27);
    Leg_R.setPosition(x+6,y+27);
    Arm_L.setPosition(x-47,y);
    Arm_R.setPosition(x+25,y);
    Leg_L.setTexture(pata.Leg_L,true);
    Leg_R.setTexture(pata.Leg_R,true);
    Arm_L.setTexture(pata.Arm_L,true);
    Arm_R.setTexture(pata.Arm_R,true);

    if(PataponType == YARIPON)
    {
    Arm_R.setTexture(pata.Arm_R_Holding,true);
    Arm_R.setPosition(x+25,y-8);
    }

    }

    }

    if(cangotobase == true)
    {
    if(x<baseposition)
    x+=0.5;

    if(x>baseposition)
    x-=0.5;
    }

    if(commandclock.asSeconds()>=1.9)
    {

    if(commandbuffer=="") {
    action = "idle";
    }

    if(commandbuffer!="PataPataPataPon") {
    if(commandbuffer!="PonPonPataPon") {
    if(commandbuffer!="ChakaChakaPataPon") {
    action = "idle";
    }}}

    }

    if(commandclock.asSeconds()>=1.95)
    {

    if(commandbuffer=="PataPataPataPon")
    {
    action = "move"; ///rusz dupe lafiryndo
    }

    if(commandbuffer=="PonPonPataPon")
    {
    action = "attack";
    }

    if(commandbuffer=="ChakaChakaPataPon")
    {
    action = "defense";
    }

    if(commandbuffer=="DonDonChakaChaka")
    {
    action = "jump";
    }

    if(commandbuffer=="PonPonChakaChaka")
    {
    action = "power";
    }

    if(commandbuffer=="PonPataPonPata")
    {
    action = "runaway";
    }

    if(commandbuffer=="PataPonDonChaka")
    {
    action = "dance";
    }

    if(commandbuffer=="ChakaPataChakaPata")
    {
    action = "stepback";
    }

    }

    frame += 1;

    if(frame>=maxframe)
    frame=0;

    if(PataponType == YARIPON)
    {
        if(action == "attack")
        {
        Head.setTexture(pata.Head_Angry,true);
        Eye.setPosition(x+6,y);

        cout << frame << endl;
        maxframe = 200;

        if(frame>=0)
        if(frame<=20)
        {
            Arm_L.setTexture(pata.Arm_L_Attack1,true);
            Arm_R.setTexture(pata.Arm_R_Attack1,true);
            Leg_L.setTexture(pata.Leg_L_Attack1,true);
            Leg_R.setTexture(pata.Leg_R_Attack1,true);
        }

        if(frame>=21)
        if(frame<=40)
        {
            Arm_L.setTexture(pata.Arm_L_Attack2,true);
            Arm_R.setTexture(pata.Arm_R_Attack2,true);
            Leg_L.setTexture(pata.Leg_L_Attack2,true);
            Leg_R.setTexture(pata.Leg_R_Attack2,true);
            Weapon.setRotation(25);
            Weapon.setPosition(x+11+pata.Arm_R_Holding.getSize().x/2,y+10);
        }

        if(frame>=41)
        if(frame<=80)
        {
            Arm_L.setTexture(pata.Arm_L_Attack3,true);
            Arm_R.setTexture(pata.Arm_R_Attack3,true);
            Leg_L.setTexture(pata.Leg_L_Attack3,true);
            Leg_R.setTexture(pata.Leg_R_Attack3,true);
            Arm_L.setPosition(x-40,y);
            Arm_R.setPosition(x+25,y-32);
            Leg_L.setPosition(x-18,y+17);
            Leg_R.setPosition(x,y+17);
            Weapon.setPosition(x+34,y-28);
            Weapon.setRotation(-35);
        }

        if(frame>=81)
        if(frame<=95)
        {
            Arm_L.setTexture(pata.Arm_L_Attack4,true);
            Arm_R.setTexture(pata.Arm_R_Attack4,true);
            Leg_L.setTexture(pata.Leg_L_Attack4,true);
            Leg_R.setTexture(pata.Leg_R_Attack4,true);
            Arm_L.setPosition(x-26,y+10);
            Arm_R.setPosition(x-8,y-32);
            Weapon.setPosition(x-10,y-20);
            Weapon.setRotation(55);
        }

        if(frame>=96)
        if(frame<=120)
        {
            Arm_L.setTexture(pata.Arm_L_Attack5,true);
            Arm_R.setTexture(pata.Arm_R_Attack5,true);
            Leg_L.setTexture(pata.Leg_L_Attack5,true);
            Leg_R.setTexture(pata.Leg_R_Attack5,true);
            Leg_L.setPosition(x-38,y+20);
            Weapon.setPosition(-3000,-3000);
        }

        if(frame>=41)
        if(frame<=100)
        {
        y -= 2;
        vspeed = -5;
        }

        if(frame==96)
        if(spear.isback == false)
        {
        spear.spear.setPosition(x,y);
        spear.Throw(7,-11,*Weapon.getTexture());
        spear.isback = true;
        }

        } else {
        maxframe = 0;
        }
    }

    spear.spear.setTexture(*Weapon.getTexture());

    if(walkclock.getElapsedTime().asSeconds()>=0.25)
    {
        walkcycle+=1;
        walkclock.restart();
    }

    if(walkcycle>=5)
    walkcycle = 1;

    if(action == "move")
    {
        if(walkcycle == 1)
        {
            Leg_L.setTexture(pata.Leg_L_Walk1,true);
            Leg_R.setTexture(pata.Leg_R_Walk1,true);
            Leg_L.setPosition(x-20,y+27);
            Leg_R.setPosition(x+8,y+27);
        }

        if(walkcycle == 2)
        {
            Leg_L.setTexture(pata.Leg_L_Walk2,true);
            Leg_R.setTexture(pata.Leg_R_Walk2,true);
            Leg_L.setPosition(x-8,y+27);
            Leg_R.setPosition(x-2,y+27);
        }

        if(walkcycle == 3)
        {
            Leg_L.setTexture(pata.Leg_L_Walk3,true);
            Leg_R.setTexture(pata.Leg_R_Walk3,true);
            Leg_L.setPosition(x-14,y+27);
            Leg_R.setPosition(x+2,y+27);
        }

        if(walkcycle == 4)
        {
            Leg_L.setTexture(pata.Leg_L_Walk4,true);
            Leg_R.setTexture(pata.Leg_R_Walk4,true);
            Leg_L.setPosition(x-6,y+27);
            Leg_R.setPosition(x-6,y+27);
        }
    }

    if(PataponType == HATAPON)
    {
        if(action != "idle")
        {
        Weapon.setPosition(x+3,y-8);
        Arm_L.setPosition(x,y-20);
        Arm_L.setTexture(pata.Hatapon_Arm_L_Action,true);
        Arm_L.setOrigin(pata.Hatapon_Arm_L_Action.getSize().x/2,pata.Hatapon_Arm_L_Action.getSize().y+1);
        Arm_R.setTexture(pata.Hatapon_Arm_R_Action,true);
        Arm_R.setOrigin(pata.Hatapon_Arm_R_Action.getSize().x/2,pata.Hatapon_Arm_R_Action.getSize().y+1);
        Arm_R.setPosition(x+8,y-20);
        maxframe = 80;

            if(frame>=0)
            if(frame<=20)
            {
                Weapon.rotate(0.7);
                Arm_L.rotate(1);
                Arm_R.rotate(1);
            }

            if(frame>=21)
            if(frame<=60)
            {
                Weapon.rotate(-0.7);
                Arm_L.rotate(-1);
                Arm_R.rotate(-1);
            }

            if(frame>=61)
            if(frame<=80)
            {
                Weapon.rotate(0.7);
                Arm_L.rotate(1);
                Arm_R.rotate(1);
            }
        }

        if(action == "idle")
        {
        Weapon.setRotation(0);
        Weapon.setPosition(x+3,y+45);
        Arm_L.setPosition(x-8,y+12);
        Arm_R.setPosition(x+20,y+8);
        Arm_R.setTexture(pata.Hatapon_Arm_R_Idle,true);
        Arm_R.setOrigin(pata.Hatapon_Arm_R_Idle.getSize().x/2,pata.Hatapon_Arm_R_Idle.getSize().y/2);
        Arm_L.setTexture(pata.Hatapon_Arm_L_Idle,true);
        Arm_L.setOrigin(pata.Hatapon_Arm_L_Idle.getSize().x/2,pata.Hatapon_Arm_L_Idle.getSize().y/2);
        Arm_R.setRotation(0);
        Arm_L.setRotation(0);
        Arm_L.setScale(0.5,0.5);
        Arm_R.setScale(0.5,0.5);
        hataponarmrx = 0;
        hataponarmry = 0;
        hataponrotation = 0;
        maxframe = 0;
        }
    }

    if(y>=window.getSize().y-45)
    {
    vspeed = 0;
    y = window.getSize().y-45;
    }

    if(y<window.getSize().y-45)
    vspeed += 0.25;

    x += hspeed;
    y += vspeed;

    window.draw(Head);
    window.draw(Eye);
    window.draw(Leg_L);
    window.draw(Leg_R);
    window.draw(Arm_L);
    window.draw(Arm_R);
    window.draw(Weapon);
    window.draw(Hat);

    if(PataponType == YARIPON)
    spear.Draw(window);
}
