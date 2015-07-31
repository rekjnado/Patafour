#include <iostream>
#include "pataponmulti.h"
#include "projectile.h"
#include "resources.h"
#include "mission.h"

PataponMulti::PataponMulti()
{
    this->x=100;
    this->y=100;
    this->attacked = false;
    this->action = "idle";
}

void PataponMulti::LoadResources(PataponRes& pata)
{
    this->Head.setTexture(pata.Head);
    this->Eye.setTexture(pata.Eye);
    this->Leg_L.setTexture(pata.Leg_L);
    this->Leg_R.setTexture(pata.Leg_R);
    this->Arm_L.setTexture(pata.Arm_L);
    this->Arm_R.setTexture(pata.Arm_R);
    this->Head.setScale(0.5,0.5);
    this->Eye.setScale(0.5,0.5);
    this->Leg_L.setScale(0.5,0.5);
    this->Leg_R.setScale(0.5,0.5);
    this->Arm_L.setScale(0.5,0.5);
    this->Arm_R.setScale(0.5,0.5);
    this->Head.setOrigin(pata.Head.getSize().x/2,pata.Head.getSize().y/2);
    this->Eye.setOrigin(pata.Eye.getSize().x/2,pata.Eye.getSize().y/2);
    this->Head.setPosition(x,y);
    this->Eye.setPosition(x,y);
    this->Leg_L.setPosition(x-18,y+27);
    this->Leg_R.setPosition(x+6,y+27);
    this->Arm_L.setPosition(x-47,y);
    this->Arm_R.setPosition(x+25,y);
}

void PataponMulti::move(int x, int y)
{
    this->Head.move(x,y);
    this->Eye.move(x,y);
    this->Leg_L.move(x,y);
    this->Leg_R.move(x,y);
    this->Arm_L.move(x,y);
    this->Arm_R.move(x,y);
    this->x+=x;
    this->y+=y;
}

void PataponMulti::draw(RenderWindow& window, Mission& mission)
{
    if(mission.commandClock.getElapsedTime().asSeconds()>=2)
    {
    if(mission.commandsystem.Play()=="PataPataPataPon") {
    action = "move";
    } else
    {
    action = "idle";
    }}

    if(x>window.getSize().x/2)
    {
    visiblex = window.getSize().x/2;
    } else {
    visiblex = x;
    }

    realx = x;

    cout << mission.commandsystem.Play() << endl;

    if(action=="move")
    {
        x+=2;
    }

    this->Head.setPosition(visiblex,y);
    this->Eye.setPosition(visiblex,y);
    this->Leg_L.setPosition(visiblex-18,y+27);
    this->Leg_R.setPosition(visiblex+6,y+27);
    this->Arm_L.setPosition(visiblex-47,y);
    this->Arm_R.setPosition(visiblex+25,y);

    window.draw(Head);
    window.draw(Eye);
    window.draw(Leg_L);
    window.draw(Leg_R);
    window.draw(Arm_L);
    window.draw(Arm_R);
}

void PataponMulti::play(RenderWindow& window, sf::Texture& weapon, float startx, float starty)
{
static Projectile projectile(window,weapon,startx,starty,5,-6);

if(this->attacked)
	{
	    projectile.fly();
		projectile.draw(window);
		cout << "attacked" << endl;

            if((projectile.getX() > 640)||(projectile.getY() > 480))
            {
            this->attacked = false;
            cout << "not attacked" << endl;
            }

	}
	else
	{
	    //projectile.refresh(5,-6,this->getPosition().x,this->getPosition().y);
		//projectile.setPosition(this->getPosition().x,this->getPosition().y);
	}

}

void PataponMulti::attack()
{
    this->attacked = true;
}
