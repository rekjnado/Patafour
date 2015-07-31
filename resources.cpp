#include <iostream>
#include <fstream>

#include "resources.h"
#include <sys/stat.h>
#include <sstream>

using namespace std;

inline bool fexists(const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

int FetchWeaponType(string type)
{
    int counter=1;

    ostringstream ss;
    ss << counter;
    string str = ss.str();

    string tempname = type+"_"+str+".dat";
    string path = "resources/equip/";
    cout << tempname << endl;

    while(fexists(path+tempname))
    {
        ///something
        cout << "fetching " << type << ", found: " << counter << endl;

        counter++;

        ostringstream ts;
        ts << counter;
        string tstr = ts.str();
        tempname = type+"_"+tstr+".dat";
    }

    return counter;
}

int FetchArmorType(string type)
{
    int counter=1;

    ostringstream ss;
    ss << counter;
    string str = ss.str();

    string tempname = type+"_"+str+".dat";
    string path = "resources/equip/armor/";
    cout << tempname << endl;

    while(fexists(path+tempname))
    {
        ///something
        cout << "fetching " << type << ", found: " << counter << endl;

        counter++;

        ostringstream ts;
        ts << counter;
        string tstr = ts.str();
        tempname = type+"_"+tstr+".dat";
    }

    return counter;
}

void UnzipWeaponFile(string name)
{
    string path = "resources/equip/";
    string fullname = path+name;

    cout << "unzipping " << fullname << endl;

    char cs=0x22;
    string p1="pack e ";
    string p2=p1+cs+"resources/equip/"+name+cs+" -o"+cs+"resources/equip/"+name.substr(0,name.find_first_of("."))+"/"+cs;

    system(p2.c_str());
}

void DeleteWeaponFile(string name)
{
    string path = "resources/equip/";
    string fullname = path+name;

    char cs=0x22;
    string p1="rmdir ";
    string p2=p1+cs+"resources/equip/"+name.substr(0,name.find_first_of("."))+"/"+cs+" /s /q";

    system(p2.c_str());
}

void UnzipArmorFile(string name)
{
    string path = "resources/equip/armor/";
    string fullname = path+name;

    cout << "unzipping " << fullname << endl;

    char cs=0x22;
    string p1="pack e ";
    string p2=p1+cs+"resources/equip/armor/"+name+cs+" -o"+cs+"resources/equip/armor/"+name.substr(0,name.find_first_of("."))+"/"+cs;
    cout << p2 << endl;

    system(p2.c_str());
}

void DeleteArmorFile(string name)
{
    string path = "resources/equip/armor/";
    string fullname = path+name;

    char cs=0x22;
    string p1="rmdir ";
    string p2=p1+cs+"resources/equip/armor/"+name.substr(0,name.find_first_of("."))+"/"+cs+" /s /q";

    system(p2.c_str());
}


PataponRes::PataponRes()
{
    spearmindmg[1] = 1;
    spearmaxdmg[1] = 4;
    hatdmg[1] = 0;

    cout << "loading resources" << endl;
    Head.loadFromFile("resources/graphics/head.png");
    Head_Angry.loadFromFile("resources/graphics/head_angry.png");
    Eye.loadFromFile("resources/graphics/eye.png");
    Arm_L.loadFromFile("resources/graphics/arm_left.png");
    Arm_R.loadFromFile("resources/graphics/arm_right.png");
    Leg_L.loadFromFile("resources/graphics/foot_left.png");
    Leg_R.loadFromFile("resources/graphics/foot_right.png");

    Arm_R_Holding.loadFromFile("resources/graphics/arm_right_holding.png");

    Leg_L_Walk1.loadFromFile("resources/graphics/foot_left_walk1.png");
    Leg_L_Walk2.loadFromFile("resources/graphics/foot_left_walk2.png");
    Leg_L_Walk3.loadFromFile("resources/graphics/foot_left_walk3.png");
    Leg_L_Walk4.loadFromFile("resources/graphics/foot_left_walk4.png");
    Leg_R_Walk1.loadFromFile("resources/graphics/foot_right_walk1.png");
    Leg_R_Walk2.loadFromFile("resources/graphics/foot_right_walk2.png");
    Leg_R_Walk3.loadFromFile("resources/graphics/foot_right_walk3.png");
    Leg_R_Walk4.loadFromFile("resources/graphics/foot_right_walk4.png");

    Leg_L_Attack1.loadFromFile("resources/graphics/foot_left_attack1.png");
    Leg_L_Attack2.loadFromFile("resources/graphics/foot_left_attack2.png");
    Leg_L_Attack3.loadFromFile("resources/graphics/foot_left_attack3.png");
    Leg_L_Attack4.loadFromFile("resources/graphics/foot_left_attack4.png");
    Leg_L_Attack5.loadFromFile("resources/graphics/foot_left_attack5.png");

    Leg_R_Attack1.loadFromFile("resources/graphics/foot_right_attack1.png");
    Leg_R_Attack2.loadFromFile("resources/graphics/foot_right_attack2.png");
    Leg_R_Attack3.loadFromFile("resources/graphics/foot_right_attack3.png");
    Leg_R_Attack4.loadFromFile("resources/graphics/foot_right_attack4.png");
    Leg_R_Attack5.loadFromFile("resources/graphics/foot_right_attack5.png");

    Arm_L_Attack1.loadFromFile("resources/graphics/arm_left_attack1.png");
    Arm_L_Attack2.loadFromFile("resources/graphics/arm_left_attack2.png");
    Arm_L_Attack3.loadFromFile("resources/graphics/arm_left_attack3.png");
    Arm_L_Attack4.loadFromFile("resources/graphics/arm_left_attack4.png");
    Arm_L_Attack5.loadFromFile("resources/graphics/arm_left_attack5.png");

    Arm_R_Attack1.loadFromFile("resources/graphics/arm_right_attack1.png");
    Arm_R_Attack2.loadFromFile("resources/graphics/arm_right_attack2.png");
    Arm_R_Attack3.loadFromFile("resources/graphics/arm_right_attack3.png");
    Arm_R_Attack4.loadFromFile("resources/graphics/arm_right_attack4.png");
    Arm_R_Attack5.loadFromFile("resources/graphics/arm_right_attack5.png");

    Arm_L_Pata.loadFromFile("resources/graphics/arm_left_pata.png");
    Arm_R_Pata.loadFromFile("resources/graphics/arm_right_pata.png");
    Leg_L_Pata.loadFromFile("resources/graphics/foot_left_pata.png");
    Leg_R_Pata.loadFromFile("resources/graphics/foot_right_pata.png");

    Arm_L_Pon.loadFromFile("resources/graphics/arm_left_pon.png");
    Arm_R_Pon.loadFromFile("resources/graphics/arm_right_pon.png");
    Leg_L_Pon.loadFromFile("resources/graphics/foot_left_pon.png");
    Leg_R_Pon.loadFromFile("resources/graphics/foot_right_pon.png");

    Hatapon_Arm_L_Idle.loadFromFile("resources/graphics/hatapon_arm_left_idle.png");
    Hatapon_Arm_R_Idle.loadFromFile("resources/graphics/hatapon_arm_right_idle.png");

    Hatapon_Arm_L_Action.loadFromFile("resources/graphics/hatapon_arm_left_action.png");
    Hatapon_Arm_R_Action.loadFromFile("resources/graphics/hatapon_arm_right_action.png");

    cout << "loaded" << endl;
}

void PataponRes::LoadAllWeapons()
{
    for(int i=1; i<FetchWeaponType("hata"); i++)
    {
    ostringstream s;
    s << i;
    string tstr = s.str();
    string name = "hata_"+tstr+".dat";
    string foldername = "hata_"+tstr+"/";
    string path = "resources/equip/";
    string full = path+foldername+"texture.png";
    string xmlfile = path+"param.xml";

    UnzipWeaponFile(name);

    cout << "getting texture from " << full << endl;
    hatatex[i].loadFromFile(full.c_str());

    DeleteWeaponFile(name);
    }

    for(int i=1; i<FetchWeaponType("spear"); i++)
    {
    ostringstream s;
    s << i;
    string tstr = s.str();
    string name = "spear_"+tstr+".dat";
    string foldername = "spear_"+tstr+"/";
    string path = "resources/equip/";
    string full = path+foldername+"texture.png";
    string xmlfile = path+"param.xml";

    UnzipWeaponFile(name);

    cout << "getting texture from " << full << endl;
    speartex[i].loadFromFile(full.c_str());

    DeleteWeaponFile(name);
    }

    for(int i=1; i<FetchArmorType("hat"); i++)
    {
    ostringstream s;
    s << i;
    string tstr = s.str();
    string name = "hat_"+tstr+".dat";
    string foldername = "hat_"+tstr+"/";
    string path = "resources/equip/armor/";
    string full = path+foldername+"texture.png";
    string xmlfile = path+"param.xml";

    UnzipArmorFile(name);

    cout << "getting texture from " << full << endl;
    hattex[i].loadFromFile(full.c_str());

    DeleteArmorFile(name);
    }
}

OrganizationGraphics::OrganizationGraphics()
{
    Barracks_back.loadFromFile("resources/graphics/barracks/back.png");
    Barracks_ArmyGui.loadFromFile("resources/graphics/barracks/armygui.png");
    Barracks_ArmySelected.loadFromFile("resources/graphics/barracks/armyselected.png");
    Barracks_PataponSelected.loadFromFile("resources/graphics/barracks/pataponselected.png");
    Barracks_arrow.loadFromFile("resources/graphics/barracks/arrow.png");
    Barracks_EquipGui.loadFromFile("resources/graphics/barracks/equipgui.png");
    Barracks_PataponGui.loadFromFile("resources/graphics/barracks/patapongui.png");
    Barracks_PataponOptions.loadFromFile("resources/graphics/barracks/pataponoptions.png");
    emblem[1].loadFromFile("resources/graphics/barracks/spearicon.png");
    emblem[2].loadFromFile("resources/graphics/barracks/swordicon.png");
    emblem[3].loadFromFile("resources/graphics/barracks/bowicon.png");
    Barracks_EquipList.loadFromFile("resources/graphics/barracks/equiplist.png");
}
