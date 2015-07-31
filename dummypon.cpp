#include <iostream>
#include <SFML/Graphics.hpp>
#include "dummypon.h"

using namespace std;

Dummypon::Dummypon()
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
}

void Dummypon::LoadResources(PataponRes pata)
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
}

void Dummypon::move(float x, float y)
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

void Dummypon::draw(sf::RenderWindow& window)
{
    Head.setTexture(pata.Head);
    Eye.setTexture(pata.Eye);
    Leg_L.setTexture(pata.Leg_L);
    Leg_R.setTexture(pata.Leg_R);
    Arm_L.setTexture(pata.Arm_L);
    Arm_R.setTexture(pata.Arm_R);
    Hat.setTexture(pata.hattex[HatID]);
    Hat.setOrigin(pata.hattex[HatID].getSize().x/2,pata.hattex[HatID].getSize().y);
    Hat.setPosition(x,y-23);

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

    Weapon.setPosition(x+18+pata.Arm_R_Holding.getSize().x/2,y-8);
    Weapon.setRotation(0);
    Weapon.setOrigin(pata.speartex[WeaponID].getSize().x/2,pata.speartex[WeaponID].getSize().y/2);
    Weapon.setTexture(pata.speartex[WeaponID],true);
    }

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

    y = window.getSize().y-95;

    window.draw(Head);
    window.draw(Eye);
    window.draw(Leg_L);
    window.draw(Leg_R);
    window.draw(Arm_L);
    window.draw(Arm_R);
    window.draw(Weapon);
    window.draw(Hat);
}
