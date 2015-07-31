#ifndef RESOURCES_H
#define RESOURCES_H

#include <SFML/Graphics.hpp>

using namespace std;

class Weapons
{
    public:


    Weapons();
};

class PataponRes
{
    public:
    map<int,sf::Texture> hatatex;
    map<int,sf::String> hataname;
    map<int,sf::String> hatadesc;
    map<int,int> hatamindmg;
    map<int,int> hatamaxdmg;

    map<int,sf::Texture> speartex;
    map<int,sf::String> spearname;
    map<int,sf::String> speardesc;
    map<int,int> spearmindmg;
    map<int,int> spearmaxdmg;
    map<int,int> speardef;
    map<int,int> spearhp;
    map<int,int> spearfiredmg;
    map<int,int> spearicedmg;
    map<int,int> spearpoisondmg;
    map<int,int> spearelectricdmg;
    map<int,int> spearcritdmg;
    map<int,int> spearstaggerdmg;
    map<int,int> spearknockbackdmg;
    map<int,int> spearfireres;
    map<int,int> speariceres;
    map<int,int> spearpoisonres;
    map<int,int> spearelectricres;
    map<int,int> spearcritres;
    map<int,int> spearstaggerres;
    map<int,int> spearknockbackres;

    map<int,sf::Texture> hattex;
    map<int,sf::String> hatname;
    map<int,sf::String> hatdesc;
    map<int,int> hatdef;
    map<int,int> hathp;
    map<int,int> hatdmg;
    map<int,int> hatfiredmg;
    map<int,int> haticedmg;
    map<int,int> hatpoisondmg;
    map<int,int> hatelectricdmg;
    map<int,int> hatcritdmg;
    map<int,int> hatstaggerdmg;
    map<int,int> hatknockbackdmg;
    map<int,int> hatfireres;
    map<int,int> haticeres;
    map<int,int> hatpoisonres;
    map<int,int> hatelectricres;
    map<int,int> hatcritres;
    map<int,int> hatstaggerres;
    map<int,int> hatknockbackres;

    sf::Texture Head,Head_Angry,Eye,Arm_L,Arm_R,Leg_L,Leg_R;
    sf::Texture Arm_R_Holding;
    sf::Texture Leg_L_Walk1,Leg_L_Walk2,Leg_L_Walk3,Leg_L_Walk4,Leg_R_Walk1,Leg_R_Walk2,Leg_R_Walk3,Leg_R_Walk4;
    sf::Texture Leg_L_Attack1,Leg_L_Attack2,Leg_L_Attack3,Leg_L_Attack4,Leg_L_Attack5,Leg_R_Attack1,Leg_R_Attack2,Leg_R_Attack3,Leg_R_Attack4,Leg_R_Attack5;
    sf::Texture Arm_L_Attack1,Arm_L_Attack2,Arm_L_Attack3,Arm_L_Attack4,Arm_L_Attack5,Arm_R_Attack1,Arm_R_Attack2,Arm_R_Attack3,Arm_R_Attack4,Arm_R_Attack5;
    sf::Texture Arm_L_Pata,Arm_R_Pata,Leg_L_Pata,Leg_R_Pata;
    sf::Texture Arm_L_Pon,Arm_R_Pon,Leg_L_Pon,Leg_R_Pon;
    sf::Texture Hatapon_Arm_L_Idle,Hatapon_Arm_R_Idle;
    sf::Texture Hatapon_Arm_L_Action,Hatapon_Arm_R_Action;

    map<int,sf::Texture> spears;
    map<int,int,string> speardata;

    PataponRes();
    void LoadAllWeapons();
};

class OrganizationGraphics
{
    public:
    sf::Texture Barracks_back;
    sf::Texture Barracks_ArmyGui,Barracks_ArmySelected,Barracks_PataponSelected,Barracks_Selected,Barracks_EquipGui,Barracks_PataponGui,Barracks_PataponOptions;
    sf::Texture Barracks_arrow;
    sf::Texture emblem[3];
    sf::Texture Barracks_EquipList;

    OrganizationGraphics();
};



#endif
