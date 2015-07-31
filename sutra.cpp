#include <SFML/Graphics.hpp>
#include "sutra.h"
#include <iostream>
#include <fstream>
#include <string>
#include "missioncamera.h"
#include "Patafour.h"

using namespace std;

Sutra::Sutra()
{
    cout << "say hi to hatty" << endl;
    tex_pata.loadFromFile("resources/graphics/sutra/pata.png");
    tex_pon.loadFromFile("resources/graphics/sutra/pon.png");
    tex_chaka.loadFromFile("resources/graphics/sutra/chaka.png");
    tex_don.loadFromFile("resources/graphics/sutra/don.png");
    tex_tick.loadFromFile("resources/graphics/sutra/tick.png");
    tex_beat.loadFromFile("resources/graphics/sutra/beat.png");
    tex_overlay.loadFromFile("resources/graphics/sutra/overlay.png");

    beat.setTexture(tex_beat);
    overlay.setTexture(tex_overlay);

    tex_pataslider.loadFromFile("resources/graphics/sutra/pataslider.png");
    tex_ponslider.loadFromFile("resources/graphics/sutra/ponslider.png");
    tex_chakaslider.loadFromFile("resources/graphics/sutra/chakaslider.png");
    tex_donslider.loadFromFile("resources/graphics/sutra/donslider.png");
    tex_patasliderend.loadFromFile("resources/graphics/sutra/patasliderend.png");
    tex_ponsliderend.loadFromFile("resources/graphics/sutra/ponsliderend.png");
    tex_chakasliderend.loadFromFile("resources/graphics/sutra/chakasliderend.png");
    tex_donsliderend.loadFromFile("resources/graphics/sutra/donsliderend.png");

    beatx = 0;
    beatspeed = 0;
    hitsoundoffset = 80;
    points = 0;
    press = false;
}

void Sutra::Load(string sutrafile)
{
    char cs=0x22;

    string rp="rmdir ";
    string rp2=rp+cs+"resources\\sutra\\"+sutrafile.substr(0,sutrafile.find_first_of("."))+"\\"+cs+" /s /q";

    system(rp2.c_str());

    string path = "resources/sutra/";
    string fullpath = path+sutrafile;

    string p1="pack e ";
    string p2=p1+cs+"resources/sutra/"+sutrafile+cs+" -o"+cs+"resources/sutra/"+sutrafile.substr(0,sutrafile.find_first_of("."))+"/"+cs;

    system(p2.c_str());

    string unpacked = "resources/sutra/"+sutrafile.substr(0,sutrafile.find_first_of("."))+"/";

    string pb1="pack e ";
    string pb2=pb1+cs+unpacked+"data.dat"+cs+" -o"+cs+unpacked+"data/"+cs;

    string datapath = unpacked + "data/";

    system(pb2.c_str());

    sutratune.openFromFile(datapath+"sutra.ogg");

    tex_sutrabackground.loadFromFile(datapath+"sutrabackground.png");
    tex_sutratotem.loadFromFile(datapath+"sutratotem.png");

    sutrabackground.setTexture(tex_sutrabackground);
    sutratotem.setTexture(tex_sutratotem);

    string timelinefile = unpacked+"timeline.dat";

    ifstream tline(timelinefile.c_str());
    string buffer;

    while(getline(tline,buffer))
    {

    if(buffer.find("SetBPM")<=7)
    {
    string pre = buffer.substr(buffer.find_first_of("(")+1);
    string sbpm = pre.substr(0,pre.size()-1);
    bpm = atof(sbpm.c_str());
    beatspeed = (bpm/60 * hitsoundoffset) / 60;
    cout << "bpm set " << sbpm << endl;
    }

    if(buffer.find("SpawnPataSlider")<=16)
    {
    string pre = buffer.substr(buffer.find_first_of("(")+1); ///6,4)
    string pre2 = pre.substr(0,pre.size()-1); ///6,4
    string first = pre2.substr(0,pre2.find_first_of(",")); ///6
    string second = pre2.substr(pre2.find_first_of(",")+1); ///4
    timeline[atoi(first.c_str())] = "PataSliderStart";
    sf::Sprite tempsliderstart;
    tempsliderstart.setTexture(tex_pata);
    pataslidersstarts.push_back(tempsliderstart);

    for(int i=1; i<atoi(second.c_str()); i++)
    {
    if(i<atoi(second.c_str())) {
    timeline[atoi(first.c_str())+i] = "PataSliderEnd";
    ticklength = atoi(first.c_str())+i;
    }
    if(i<atoi(second.c_str())-1)
    timeline[atoi(first.c_str())+i] = "PataSlider";
    }
    cout << "pata slider at " << first << " for " << second << " ticks spawned" << endl;
    cout << "debug data:" << endl;
    cout << timeline[atoi(first.c_str())] << " (" << atoi(first.c_str()) << ")" << endl;
    for(int i=1; i<atoi(second.c_str()); i++)
    {
        cout << timeline[atoi(first.c_str())+i] << " (" << atoi(first.c_str())+i << ")" << endl;
        if(timeline[atoi(first.c_str())+i]=="PataSlider")
        {
            sf::Sprite tempslider;
            tempslider.setTexture(tex_pataslider);
            patasliders.push_back(tempslider);
        }

        if(timeline[atoi(first.c_str())+i]=="PataSliderEnd")
        {
            sf::Sprite tempsliderend;
            tempsliderend.setTexture(tex_patasliderend);
            pataslidersends.push_back(tempsliderend);
        }
    }
    }

    if(buffer.find("SpawnPonSlider")<=16)
    {
    string pre = buffer.substr(buffer.find_first_of("(")+1); ///6,4)
    string pre2 = pre.substr(0,pre.size()-1); ///6,4
    string first = pre2.substr(0,pre2.find_first_of(",")); ///6
    string second = pre2.substr(pre2.find_first_of(",")+1); ///4
    timeline[atoi(first.c_str())] = "PonSliderStart";
    sf::Sprite tempsliderstart;
    tempsliderstart.setTexture(tex_pon);
    ponslidersstarts.push_back(tempsliderstart);

    for(int i=1; i<atoi(second.c_str()); i++)
    {
    if(i<atoi(second.c_str())) {
    timeline[atoi(first.c_str())+i] = "PonSliderEnd";
    ticklength = atoi(first.c_str())+i;
    }
    if(i<atoi(second.c_str())-1)
    timeline[atoi(first.c_str())+i] = "PonSlider";
    }
    cout << "pon slider at " << first << " for " << second << " ticks spawned" << endl;
    cout << "debug data:" << endl;
    cout << timeline[atoi(first.c_str())] << " (" << atoi(first.c_str()) << ")" << endl;
    for(int i=1; i<atoi(second.c_str()); i++)
    {
        cout << timeline[atoi(first.c_str())+i] << " (" << atoi(first.c_str())+i << ")" << endl;
        if(timeline[atoi(first.c_str())+i]=="PonSlider")
        {
            sf::Sprite tempslider;
            tempslider.setTexture(tex_ponslider);
            ponsliders.push_back(tempslider);
        }

        if(timeline[atoi(first.c_str())+i]=="PonSliderEnd")
        {
            sf::Sprite tempsliderend;
            tempsliderend.setTexture(tex_ponsliderend);
            ponslidersends.push_back(tempsliderend);
        }
    }
    }

    if(buffer.find("SpawnChakaSlider")<=16)
    {
    string pre = buffer.substr(buffer.find_first_of("(")+1); ///6,4)
    string pre2 = pre.substr(0,pre.size()-1); ///6,4
    string first = pre2.substr(0,pre2.find_first_of(",")); ///6
    string second = pre2.substr(pre2.find_first_of(",")+1); ///4
    timeline[atoi(first.c_str())] = "ChakaSliderStart";
    sf::Sprite tempsliderstart;
    tempsliderstart.setTexture(tex_chaka);
    chakaslidersstarts.push_back(tempsliderstart);

    for(int i=1; i<atoi(second.c_str()); i++)
    {
    if(i<atoi(second.c_str())) {
    timeline[atoi(first.c_str())+i] = "ChakaSliderEnd";
    ticklength = atoi(first.c_str())+i;
    }
    if(i<atoi(second.c_str())-1)
    timeline[atoi(first.c_str())+i] = "ChakaSlider";
    }
    cout << "chaka slider at " << first << " for " << second << " ticks spawned" << endl;
    cout << "debug data:" << endl;
    cout << timeline[atoi(first.c_str())] << " (" << atoi(first.c_str()) << ")" << endl;
    for(int i=1; i<atoi(second.c_str()); i++)
    {
        cout << timeline[atoi(first.c_str())+i] << " (" << atoi(first.c_str())+i << ")" << endl;
        if(timeline[atoi(first.c_str())+i]=="ChakaSlider")
        {
            sf::Sprite tempslider;
            tempslider.setTexture(tex_chakaslider);
            chakasliders.push_back(tempslider);
        }

        if(timeline[atoi(first.c_str())+i]=="ChakaSliderEnd")
        {
            sf::Sprite tempsliderend;
            tempsliderend.setTexture(tex_chakasliderend);
            chakaslidersends.push_back(tempsliderend);
        }
    }
    }

    if(buffer.find("SpawnDonSlider")<=16)
    {
    string pre = buffer.substr(buffer.find_first_of("(")+1); ///6,4)
    string pre2 = pre.substr(0,pre.size()-1); ///6,4
    string first = pre2.substr(0,pre2.find_first_of(",")); ///6
    string second = pre2.substr(pre2.find_first_of(",")+1); ///4
    timeline[atoi(first.c_str())] = "DonSliderStart";
    sf::Sprite tempsliderstart;
    tempsliderstart.setTexture(tex_don);
    donslidersstarts.push_back(tempsliderstart);

    for(int i=1; i<atoi(second.c_str()); i++)
    {
    if(i<atoi(second.c_str())) {
    timeline[atoi(first.c_str())+i] = "DonSliderEnd";
    ticklength = atoi(first.c_str())+i;
    }
    if(i<atoi(second.c_str())-1)
    timeline[atoi(first.c_str())+i] = "DonSlider";
    }
    cout << "don slider at " << first << " for " << second << " ticks spawned" << endl;
    cout << "debug data:" << endl;
    cout << timeline[atoi(first.c_str())] << " (" << atoi(first.c_str()) << ")" << endl;
    for(int i=1; i<atoi(second.c_str()); i++)
    {
        cout << timeline[atoi(first.c_str())+i] << " (" << atoi(first.c_str())+i << ")" << endl;
        if(timeline[atoi(first.c_str())+i]=="DonSlider")
        {
            sf::Sprite tempslider;
            tempslider.setTexture(tex_donslider);
            donsliders.push_back(tempslider);
        }

        if(timeline[atoi(first.c_str())+i]=="DonSliderEnd")
        {
            sf::Sprite tempsliderend;
            tempsliderend.setTexture(tex_donsliderend);
            donslidersends.push_back(tempsliderend);
        }
    }
    }

    if(buffer.find("SpawnPataHitCircle")<=19)
    {
        string pre = buffer.substr(buffer.find_first_of("(")+1);
        string pre2 = pre.substr(0,pre.size()-1);
        timeline[atoi(pre2.c_str())] = "PataHitCircle";

        sf::Sprite temphitcircle;
        temphitcircle.setTexture(tex_pata);
        patas.push_back(temphitcircle);

        ticklength = atoi(pre2.c_str());

        cout << "pata hitcircle at " << pre2 << " spawned" << endl;
    }

    if(buffer.find("SpawnPonHitCircle")<=19)
    {
        string pre = buffer.substr(buffer.find_first_of("(")+1);
        string pre2 = pre.substr(0,pre.size()-1);
        timeline[atoi(pre2.c_str())] = "PonHitCircle";

        sf::Sprite temphitcircle;
        temphitcircle.setTexture(tex_pon);
        pons.push_back(temphitcircle);

        ticklength = atoi(pre2.c_str());

        cout << "pon hitcircle at " << pre2 << " spawned" << endl;
    }

    if(buffer.find("SpawnChakaHitCircle")<=21)
    {
        string pre = buffer.substr(buffer.find_first_of("(")+1);
        string pre2 = pre.substr(0,pre.size()-1);
        timeline[atoi(pre2.c_str())] = "ChakaHitCircle";

        sf::Sprite temphitcircle;
        temphitcircle.setTexture(tex_chaka);
        chakas.push_back(temphitcircle);

        ticklength = atoi(pre2.c_str());

        cout << "chaka hitcircle at " << pre2 << " spawned" << endl;
    }

    if(buffer.find("SpawnDonHitCircle")<=19)
    {
        string pre = buffer.substr(buffer.find_first_of("(")+1);
        string pre2 = pre.substr(0,pre.size()-1);
        timeline[atoi(pre2.c_str())] = "DonHitCircle";

        sf::Sprite temphitcircle;
        temphitcircle.setTexture(tex_don);
        dons.push_back(temphitcircle);

        ticklength = atoi(pre2.c_str());

        cout << "don hitcircle at " << pre2 << " spawned" << endl;
    }

    }
    tline.close();

    cout << "Sutra full tick length: " << ticklength << endl;

    system(rp2.c_str());
}

void Sutra::Play(MissionCamera camera, sf::RenderWindow& window)
{
    for(int i=1; i<=ticklength; i++)
    {
        cout << timeline[i] << " (" << i << ")" << endl;

        if(timeline[i]=="PataHitCircle")
        {
            patas[patasamount].setPosition(150+hitsoundoffset*i+camera.x-window.getSize().x/2,130);
            patasamount += 1;
        }

        if(timeline[i]=="PonHitCircle")
        {
            pons[ponsamount].setPosition(150+hitsoundoffset*i+camera.x-window.getSize().x/2,130);
            ponsamount += 1;
        }

        if(timeline[i]=="DonHitCircle")
        {
            dons[donsamount].setPosition(150+hitsoundoffset*i+camera.x-window.getSize().x/2,130);
            donsamount += 1;
        }

        if(timeline[i]=="ChakaHitCircle")
        {
            chakas[chakasamount].setPosition(150+hitsoundoffset*i+camera.x-window.getSize().x/2,130);
            chakasamount += 1;
        }

        if(timeline[i]=="PataSliderStart")
        {
            pataslidersstarts[pataslidersstartsamount].setPosition(150+hitsoundoffset*i+camera.x-window.getSize().x/2,130);
            pataslidersstartsamount += 1;
        }

        if(timeline[i]=="PataSlider")
        {
            patasliders[pataslidersamount].setPosition(150+hitsoundoffset*i+camera.x-window.getSize().x/2-14,158);
            pataslidersamount += 1;
        }

        if(timeline[i]=="PataSliderEnd")
        {
            pataslidersends[pataslidersendsamount].setPosition(150+hitsoundoffset*i+camera.x-window.getSize().x/2,130);
            pataslidersendsamount += 1;
        }

        if(timeline[i]=="PonSliderStart")
        {
            ponslidersstarts[ponslidersstartsamount].setPosition(150+hitsoundoffset*i+camera.x-window.getSize().x/2,130);
            ponslidersstartsamount += 1;
        }

        if(timeline[i]=="PonSlider")
        {
            ponsliders[ponslidersamount].setPosition(150+hitsoundoffset*i+camera.x-window.getSize().x/2-14,158);
            ponslidersamount += 1;
        }

        if(timeline[i]=="PonSliderEnd")
        {
            ponslidersends[ponslidersendsamount].setPosition(150+hitsoundoffset*i+camera.x-window.getSize().x/2,130);
            ponslidersendsamount += 1;
        }

        if(timeline[i]=="DonSliderStart")
        {
            donslidersstarts[donslidersstartsamount].setPosition(150+hitsoundoffset*i+camera.x-window.getSize().x/2,130);
            donslidersstartsamount += 1;
        }

        if(timeline[i]=="DonSlider")
        {
            donsliders[donslidersamount].setPosition(150+hitsoundoffset*i+camera.x-window.getSize().x/2-14,158);
            donslidersamount += 1;
        }

        if(timeline[i]=="DonSliderEnd")
        {
            donslidersends[donslidersendsamount].setPosition(150+hitsoundoffset*i+camera.x-window.getSize().x/2,130);
            donslidersendsamount += 1;
        }

        if(timeline[i]=="ChakaSliderStart")
        {
            chakaslidersstarts[chakaslidersstartsamount].setPosition(150+hitsoundoffset*i+camera.x-window.getSize().x/2,130);
            chakaslidersstartsamount += 1;
        }

        if(timeline[i]=="ChakaSlider")
        {
            chakasliders[chakaslidersamount].setPosition(150+hitsoundoffset*i+camera.x-window.getSize().x/2-14,158);
            chakaslidersamount += 1;
        }

        if(timeline[i]=="ChakaSliderEnd")
        {
            chakaslidersends[chakaslidersendsamount].setPosition(150+hitsoundoffset*i+camera.x-window.getSize().x/2,130);
            chakaslidersendsamount += 1;
        }

    }

    clock.restart();
    sutratune.play();
    played = true;
}

void Sutra::Stop()
{
    pataslidersstartsamount = 0;
    ponslidersstartsamount = 0;
    chakaslidersstartsamount = 0;
    donslidersstartsamount = 0;
    pataslidersamount = 0;
    ponslidersamount = 0;
    chakaslidersamount = 0;
    donslidersamount = 0;
    pataslidersendsamount = 0;
    ponslidersendsamount = 0;
    chakaslidersendsamount = 0;
    donslidersendsamount = 0;
    patasamount = 0;
    ponsamount = 0;
    donsamount = 0;
    chakasamount = 0;
    played = false;
}

void Sutra::Draw(sf::RenderWindow& window, MissionCamera camera, float fps, Patafour* patafour)
{
    cout << patafour->sutrakeybuffer << endl;

    for(int i=0; i<patas.size(); i++)
    {
    cout << patapress[i] << " " << pataready[i] << " " << points << endl;

        ///Najechanie w pole beat linii
        if(patas[i].getPosition().x<=beat.getPosition().x)
        {

            if(patas[i].getPosition().x>=beat.getPosition().x-patas[i].getGlobalBounds().width)
            {
            patapress[i] = true;
            }
        }

        ///Nietrafienie
        if(patas[i].getPosition().x<=beat.getPosition().x)
        {
            if(patas[i].getPosition().x<=beat.getPosition().x-patas[i].getGlobalBounds().width)
            {
            patapress[i] = false;
            pataready[i] = false;
            }
        }

        ///Trafianie
        if(patas[i].getPosition().x<=beat.getPosition().x+8)
        {
            if(patafour->sutrakeybuffer.find("Pata")>=30)
            {
                pataready[i] = true;
            }
        }

        if(patapress[i] == true)
        {
            if(pataready[i] == true)
            {
                if(patafour->sutrakeybuffer.find("Pata")<=25)
                {
                    points += 30;
                    patas[i].move(-1000,0);
                    pataready[i] = false;
                    patapress[i] = false;
                }
            }
        }
    }

    for(int i=0; i<pons.size(); i++)
    {
    cout << ponpress[i] << " " << ponready[i] << " " << points << endl;

        ///Najechanie w pole beat linii
        if(pons[i].getPosition().x<=beat.getPosition().x)
        {

            if(pons[i].getPosition().x>=beat.getPosition().x-pons[i].getGlobalBounds().width)
            {
            ponpress[i] = true;
            }
        }

        ///Nietrafienie
        if(pons[i].getPosition().x<=beat.getPosition().x)
        {
            if(pons[i].getPosition().x<=beat.getPosition().x-pons[i].getGlobalBounds().width)
            {
            ponpress[i] = false;
            ponready[i] = false;
            }
        }

        ///Trafianie
        if(pons[i].getPosition().x<=beat.getPosition().x+8)
        {
            if(patafour->sutrakeybuffer.find("Pon")>=30)
            {
                ponready[i] = true;
            }
        }

        if(ponpress[i] == true)
        {
            if(ponready[i] == true)
            {
                if(patafour->sutrakeybuffer.find("Pon")<=25)
                {
                    points += 30;
                    pons[i].move(-1000,0);
                    ponready[i] = false;
                    ponpress[i] = false;
                }
            }
        }
    }

    for(int i=0; i<chakas.size(); i++)
    {
    cout << chakapress[i] << " " << chakaready[i] << " " << points << endl;

        ///Najechanie w pole beat linii
        if(chakas[i].getPosition().x<=beat.getPosition().x)
        {

            if(chakas[i].getPosition().x>=beat.getPosition().x-chakas[i].getGlobalBounds().width)
            {
            chakapress[i] = true;
            }
        }

        ///Nietrafienie
        if(chakas[i].getPosition().x<=beat.getPosition().x)
        {
            if(chakas[i].getPosition().x<=beat.getPosition().x-chakas[i].getGlobalBounds().width)
            {
            chakapress[i] = false;
            chakaready[i] = false;
            }
        }

        ///Trafianie
        if(chakas[i].getPosition().x<=beat.getPosition().x+8)
        {
            if(patafour->sutrakeybuffer.find("Chaka")>=30)
            {
                chakaready[i] = true;
            }
        }

        if(chakapress[i] == true)
        {
            if(chakaready[i] == true)
            {
                if(patafour->sutrakeybuffer.find("Chaka")<=25)
                {
                    points += 30;
                    chakas[i].move(-1000,0);
                    chakaready[i] = false;
                    chakapress[i] = false;
                }
            }
        }
    }

    for(int i=0; i<dons.size(); i++)
    {
    cout << donpress[i] << " " << donready[i] << " " << points << endl;

        ///Najechanie w pole beat linii
        if(dons[i].getPosition().x<=beat.getPosition().x)
        {

            if(dons[i].getPosition().x>=beat.getPosition().x-dons[i].getGlobalBounds().width)
            {
            donpress[i] = true;
            }
        }

        ///Nietrafienie
        if(dons[i].getPosition().x<=beat.getPosition().x)
        {
            if(dons[i].getPosition().x<=beat.getPosition().x-dons[i].getGlobalBounds().width)
            {
            donpress[i] = false;
            donready[i] = false;
            }
        }

        ///Trafianie
        if(dons[i].getPosition().x<=beat.getPosition().x+8)
        {
            if(patafour->sutrakeybuffer.find("Don")>=30)
            {
                donready[i] = true;
            }
        }

        if(donpress[i] == true)
        {
            if(donready[i] == true)
            {
                if(patafour->sutrakeybuffer.find("Don")<=25)
                {
                    points += 30;
                    dons[i].move(-1000,0);
                    donready[i] = false;
                    donpress[i] = false;
                }
            }
        }
    }

///
/// Slidery
///

    for(int i=0; i<pataslidersstarts.size(); i++)
    {
    cout << patasliderspress[i] << " " << pataslidersready[i] << " " << points << endl;

        ///Najechanie w pole beat linii
        if(pataslidersstarts[i].getPosition().x<=beat.getPosition().x)
        {

            if(pataslidersstarts[i].getPosition().x>=beat.getPosition().x-pataslidersstarts[i].getGlobalBounds().width)
            {
            patasliderspress[i] = true;
            }
        }

        ///Nietrafienie
        if(pataslidersends[i].getPosition().x<=beat.getPosition().x)
        {
            if(pataslidersends[i].getPosition().x<=beat.getPosition().x-pataslidersstarts[i].getGlobalBounds().width)
            {
            patasliderspress[i] = false;
            pataslidersready[i] = false;

            }
        }

        ///Trafianie
        if(pataslidersstarts[i].getPosition().x<=beat.getPosition().x-4)
        {
            if(patafour->sutrakeybuffer.find("Pata")>=30)
            {
                pataslidersready[i] = true;
            }
        }

        if(patasliderspress[i] == true)
        {
            if(pataslidersready[i] == true)
            {
                if(patafour->sutrakeybuffer.find("Pata")<=25)
                {
                    points += 1;
                }
            }
        }
    }

     for(int i=0; i<ponslidersstarts.size(); i++)
    {
    cout << ponsliderspress[i] << " " << ponslidersready[i] << " " << points << endl;

        ///Najechanie w pole beat linii
        if(ponslidersstarts[i].getPosition().x<=beat.getPosition().x)
        {

            if(ponslidersstarts[i].getPosition().x>=beat.getPosition().x-ponslidersstarts[i].getGlobalBounds().width)
            {
            ponsliderspress[i] = true;
            }
        }

        ///Nietrafienie
        if(ponslidersends[i].getPosition().x<=beat.getPosition().x)
        {
            if(ponslidersends[i].getPosition().x<=beat.getPosition().x-ponslidersstarts[i].getGlobalBounds().width)
            {
            ponsliderspress[i] = false;
            ponslidersready[i] = false;

            }
        }

        ///Trafianie
        if(ponslidersstarts[i].getPosition().x<=beat.getPosition().x-4)
        {
            if(patafour->sutrakeybuffer.find("Pon")>=30)
            {
                ponslidersready[i] = true;
            }
        }

        if(ponsliderspress[i] == true)
        {
            if(ponslidersready[i] == true)
            {
                if(patafour->sutrakeybuffer.find("Pon")<=25)
                {
                    points += 1;
                }
            }
        }
    }

     for(int i=0; i<chakaslidersstarts.size(); i++)
    {
    cout << chakasliderspress[i] << " " << chakaslidersready[i] << " " << points << endl;

        ///Najechanie w pole beat linii
        if(chakaslidersstarts[i].getPosition().x<=beat.getPosition().x)
        {

            if(chakaslidersstarts[i].getPosition().x>=beat.getPosition().x-chakaslidersstarts[i].getGlobalBounds().width)
            {
            chakasliderspress[i] = true;
            }
        }

        ///Nietrafienie
        if(chakaslidersends[i].getPosition().x<=beat.getPosition().x)
        {
            if(chakaslidersends[i].getPosition().x<=beat.getPosition().x-chakaslidersstarts[i].getGlobalBounds().width)
            {
            chakasliderspress[i] = false;
            chakaslidersready[i] = false;

            }
        }

        ///Trafianie
        if(chakaslidersstarts[i].getPosition().x<=beat.getPosition().x-4)
        {
            if(patafour->sutrakeybuffer.find("Chaka")>=30)
            {
                chakaslidersready[i] = true;
            }
        }

        if(chakasliderspress[i] == true)
        {
            if(chakaslidersready[i] == true)
            {
                if(patafour->sutrakeybuffer.find("Chaka")<=25)
                {
                    points += 1;
                }
            }
        }
    }

     for(int i=0; i<donslidersstarts.size(); i++)
    {
    cout << donsliderspress[i] << " " << donslidersready[i] << " " << points << endl;

        ///Najechanie w pole beat linii
        if(donslidersstarts[i].getPosition().x<=beat.getPosition().x)
        {

            if(donslidersstarts[i].getPosition().x>=beat.getPosition().x-donslidersstarts[i].getGlobalBounds().width)
            {
            donsliderspress[i] = true;
            }
        }

        ///Nietrafienie
        if(donslidersends[i].getPosition().x<=beat.getPosition().x)
        {
            if(donslidersends[i].getPosition().x<=beat.getPosition().x-donslidersstarts[i].getGlobalBounds().width)
            {
            donsliderspress[i] = false;
            donslidersready[i] = false;

            }
        }

        ///Trafianie
        if(donslidersstarts[i].getPosition().x<=beat.getPosition().x-4)
        {
            if(patafour->sutrakeybuffer.find("Don")>=30)
            {
                donslidersready[i] = true;
            }
        }

        if(donsliderspress[i] == true)
        {
            if(donslidersready[i] == true)
            {
                if(patafour->sutrakeybuffer.find("Don")<=25)
                {
                    points += 1;
                }
            }
        }
    }

    if(fps==0)
    fps = 60;

    beatspeed = (bpm/60 * hitsoundoffset) / fps-1;
    //cout << fps << endl;

    ///drawing the sutra things
    sutrabackground.setPosition(0+camera.x-window.getSize().x/2,0);
    sutrabackground.setScale(10,(float)window.getSize().y/600);
    overlay.setScale(10,1);
    overlay.setPosition(0+camera.x-window.getSize().x/2,130);
    beat.setPosition(150+camera.x-window.getSize().x/2,130);

    window.draw(sutrabackground);
    window.draw(overlay);

    for(int i=0; i<patas.size(); i++)
    {
       patas[i].move(-beatspeed,0);
       window.draw(patas[i]);
    }

    for(int i=0; i<pons.size(); i++)
    {
       pons[i].move(-beatspeed,0);
       window.draw(pons[i]);
    }

    for(int i=0; i<dons.size(); i++)
    {
       dons[i].move(-beatspeed,0);
       window.draw(dons[i]);
    }

    for(int i=0; i<chakas.size(); i++)
    {
       chakas[i].move(-beatspeed,0);
       window.draw(chakas[i]);
    }

    for(int i=0; i<pataslidersstarts.size(); i++)
    {
       pataslidersstarts[i].move(-beatspeed,0);
       window.draw(pataslidersstarts[i]);
    }

    for(int i=0; i<patasliders.size(); i++)
    {
       patasliders[i].move(-beatspeed,0);
       window.draw(patasliders[i]);
    }

    for(int i=0; i<pataslidersends.size(); i++)
    {
       pataslidersends[i].move(-beatspeed,0);
       window.draw(pataslidersends[i]);
    }

    for(int i=0; i<ponslidersstarts.size(); i++)
    {
       ponslidersstarts[i].move(-beatspeed,0);
       window.draw(ponslidersstarts[i]);
    }

    for(int i=0; i<ponsliders.size(); i++)
    {
       ponsliders[i].move(-beatspeed,0);
       window.draw(ponsliders[i]);
    }

    for(int i=0; i<ponslidersends.size(); i++)
    {
       ponslidersends[i].move(-beatspeed,0);
       window.draw(ponslidersends[i]);
    }

    for(int i=0; i<donslidersstarts.size(); i++)
    {
       donslidersstarts[i].move(-beatspeed,0);
       window.draw(donslidersstarts[i]);
    }

    for(int i=0; i<donsliders.size(); i++)
    {
       donsliders[i].move(-beatspeed,0);
       window.draw(donsliders[i]);
    }

    for(int i=0; i<donslidersends.size(); i++)
    {
       donslidersends[i].move(-beatspeed,0);
       window.draw(donslidersends[i]);
    }

    for(int i=0; i<chakaslidersstarts.size(); i++)
    {
       chakaslidersstarts[i].move(-beatspeed,0);
       window.draw(chakaslidersstarts[i]);
    }

    for(int i=0; i<chakasliders.size(); i++)
    {
       chakasliders[i].move(-beatspeed,0);
       window.draw(chakasliders[i]);
    }

    for(int i=0; i<chakaslidersends.size(); i++)
    {
       chakaslidersends[i].move(-beatspeed,0);
       window.draw(chakaslidersends[i]);
    }

    window.draw(beat);

    if(clock.getElapsedTime().asSeconds() >= sutratune.getDuration().asSeconds())
    {
        this->Stop();
    }
}
