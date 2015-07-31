#include <iostream>
#include <SFML/Graphics.hpp>
#include "mission.h"
#include <fstream>
#include "enemy.h"
#include <sstream>
#include "mission.h"
#include <SFML/Audio.hpp>
#include <SFML/Audio/SoundSource.hpp>
#include "commandsystem.h"
#include "cutscene.h"
#include "sutra.h"

using namespace std;

int to_int(string str)
{
int i;
istringstream iss(str);
iss >> i;
return i;
}

template <typename T>
std::string to_string(T value)
    {
    std::ostringstream os;
    os << value;
    return os.str();
    }

std::string toLowercase(string str)
{
    for(int i=0; i<=to_int(to_string(str.length())); i++)
    str[i] = tolower(str[i]);
    return str;
}

Mission::Mission()
{
cout << "constructor of mission" << endl;
loaded = false;
beatframeNotStarted = false;
combo = 0;
timeout = 1;
kolej=1;
cameramove = false;

sutra.Load("sutra_1.stf");
sutra.played = false;
}

void Mission::Load(string missionfile,sf::RenderWindow& window)
{
    cout << "LOADING MISSION " << missionfile << endl;
    cout << "LOADING MISSION " << missionfile << endl;
    cout << "LOADING MISSION " << missionfile << endl;
    cout << "LOADING MISSION " << missionfile << endl;
    cout << "LOADING MISSION " << missionfile << endl;

    entities.clear();
    cutscenes.clear();

    beatframeNotStarted = false;

    backgroundcount = 0;

    char cs=0x22;
    string p1="pack e ";
    string p2=p1+cs+"resources/mission/"+missionfile+cs+" -o"+cs+"resources/mission/"+missionfile.substr(0,missionfile.find_first_of("."))+"/"+cs;

    system(p2.c_str());

    string mfl="resources/mission/"+missionfile.substr(0,missionfile.find_first_of("."))+"/"+missionfile.substr(0,missionfile.find_first_of("."))+".mfl";

    /// pack e "resources/mission/mission_1/back.bg" -o"resources/mission/mission_1/back"
    string p3=p1+cs+"resources/mission/"+missionfile.substr(0,missionfile.find_first_of("."))+"/back.bg"+cs+" -o"+cs+"resources/mission/"+missionfile.substr(0,missionfile.find_first_of("."))+"/back"+cs;

    system(p3.c_str());

    ifstream file(mfl.c_str());
    string line;
    /// ///////////////////// ///
    ///       file loop       ///
    /// ///////////////////// ///
    while(getline(file,line))
    {
    if(line.substr(0,line.find_first_of(":"))=="CreateObject")
    {
    string a=line.substr(line.find_first_of(":")+1);
    string b=a.substr(0,a.find_first_of(","));
    string c=a.substr(a.find_first_of(",")+1);
    string d=c.substr(0,c.find_first_of(","));
    string e=c.substr(c.find_first_of(",")+1);
    Enemy enemy(b,atoi(d.c_str()),atoi(e.c_str()));
    enemy.play = true;
    entities.push_back(enemy);
    cout << "SIZE: " << entities.size() << endl;
    }

    if(line.substr(0,line.find_first_of(":"))=="LoadCutscene")
    {
    string cfile = line.substr(line.find_first_of(":")+1);
    cutscenes.push_back(Cutscene(cfile));
    ///cutscenes[cutscenes.size()-1].Play(); ~ currently not playing because got crashing
    }

    if(line.substr(0,line.find_first_of(":"))=="LoadTheme")
    {
    string a=line.substr(line.find_first_of(":")+1);
    string b=a.substr(0,a.find_first_of(","));

    currentbgm=toLowercase(b);

    for(int i=0; i<=9; i++)
    {
    string file="resources/music/"+currentbgm+"/"+"bgm_"+to_string(i+1)+".ogg";
    bgm[i+1].openFromFile(file);
    }

    for(int i=0; i<=15; i++)
    {
    string file="resources/music/"+currentbgm+"/"+"bgm_fever"+to_string((i+1))+".ogg";
    bgm[10+(i+1)].openFromFile(file);
    }

    string bgmstart="resources/music/"+currentbgm+"/"+"bgm_start.ogg";
    string bgmfeverstart="resources/music/"+currentbgm+"/"+"bgm_feverstart.ogg";

    for(int i=1; i<=4; i++)
    {
    string file="resources/music/"+currentbgm+"/"+"bgm_patapata"+to_string(i)+".ogg";
    shouts_patapata[i].openFromFile(file);
    }

    for(int i=1; i<=4; i++)
    {
    string file="resources/music/"+currentbgm+"/"+"bgm_ponpon"+to_string(i)+".ogg";
    shouts_ponpon[i].openFromFile(file);
    }

    for(int i=1; i<=4; i++)
    {
    string file="resources/music/"+currentbgm+"/"+"bgm_chakachaka"+to_string(i)+".ogg";
    shouts_chakachaka[i].openFromFile(file);
    }

    for(int i=1; i<=3; i++)
    {
    string file="resources/music/"+currentbgm+"/"+"bgm_ponchaka"+to_string(i)+".ogg";
    shouts_ponchaka[i].openFromFile(file);
    }

    for(int i=1; i<=3; i++)
    {
    string file="resources/music/"+currentbgm+"/"+"bgm_donchaka"+to_string(i)+".ogg";
    shouts_donchaka[i].openFromFile(file);
    }

    for(int i=1; i<=3; i++)
    {
    string file="resources/music/"+currentbgm+"/"+"bgm_ponpata"+to_string(i)+".ogg";
    shouts_ponpata[i].openFromFile(file);
    }

    for(int i=1; i<=3; i++)
    {
    string file="resources/music/"+currentbgm+"/"+"bgm_dondon"+to_string(i)+".ogg";
    shouts_dondon[i].openFromFile(file);
    }

    bgm[27].openFromFile(bgmstart);
    bgm[28].openFromFile(bgmfeverstart);
    }

    if(line.substr(0,line.find_first_of(":"))=="MakeBackground")
    {
    string a=line.substr(line.find_first_of(":")+1);
    string arg1=a.substr(0,a.find_first_of(","));
    string b=a.substr(a.find_first_of(",")+1);
    string arg2=b.substr(0,b.find_first_of(","));
    string c=b.substr(b.find_first_of(",")+1);
    string arg3=c.substr(0,c.find_first_of(","));
    string d=c.substr(c.find_first_of(",")+1);
    string arg4=d.substr(0,d.find_first_of(","));
    string arg5=d.substr(d.find_first_of(",")+1);

    backMoveX[backgroundcount] = atof(arg5.c_str());

    string tex="resources/mission/"+missionfile.substr(0,missionfile.find_first_of("."))+"/back/"+arg3;
    tex_background[backgroundcount].loadFromFile(tex.c_str());

    if(arg2=="true")
    tex_background[backgroundcount].setRepeated(true);
    else
    tex_background[backgroundcount].setRepeated(false);


    background[backgroundcount].setTexture(tex_background[backgroundcount]);
    background[backgroundcount].setTextureRect(sf::IntRect(0,0,50000,to_int(to_string(tex_background[backgroundcount].getSize().y))));

    if(arg1=="windowY") {
    background[backgroundcount].setPosition(0,0);
    backSize[backgroundcount].x=0;
    backSize[backgroundcount].y=0;
    } else {
    background[backgroundcount].setPosition(0,window.getSize().y-to_int(arg1)-tex_background[backgroundcount].getSize().y);
    backSize[backgroundcount].x=0;
    backSize[backgroundcount].y=to_int(arg1)+tex_background[backgroundcount].getSize().y;
    }

    if(arg4=="byWindow")
    backResizeToWindow[backgroundcount] = true;
    else
    backResizeToWindow[backgroundcount] = false;

    backgroundcount+=1;

    }
    }
    file.close();

    string rp="rmdir ";
    string rp2=rp+cs+"resources\\mission\\"+missionfile.substr(0,missionfile.find_first_of("."))+"\\"+cs+" /s /q";
    system(rp2.c_str());

    fpscounter.restart();
    prefps = 10;

    loaded = true;
}

void Mission::Draw(sf::RenderWindow& window, std::string commandbuffer, Patafour* patafour)
{
    if(fpscounter.getElapsedTime().asSeconds()<=0.1)
    {
    prefps+=10;
    } else {
    fps=prefps+1;
    prefps=0;
    fpscounter.restart();
    }

    if(sutra.played == false)
    {

    commandsystem.command = commandbuffer;

    if(beatframeNotStarted==false) {
    themeClock.restart();
    commandClock.restart();
    failClock.restart();
    bgm[27].play();
    beatframe.Start();
    beatframeNotStarted = true;
    }

    if(kolej==3)
    kolej=1;

    if(themeClock.getElapsedTime().asSeconds()>=4)
    {
    if(combo==0)
    bgm[1].play();
    themeClock.restart();
    }

    if(commandClock.getElapsedTime().asSeconds()>=2)
    {
    beatframe.Restart();
    if(commandsystem.Play()=="PataPataPataPon") {

    combo+=1;
    failClock.restart();
    nextpressClock.restart();

    if(combo>26)
    combo=11;

    if(combo==1)
    bgm[1].stop();

    if(combo<5)
    shouts_patapata[1].play();

    if((combo>=5)&&(combo<=9))
    shouts_patapata[2].play();

    if(combo>10) {
    shouts_patapata[2+kolej].play();
    kolej+=1;
    }

    if(combo==10)
    bgm[28].play();

    if(combo<10) {
    bgm[combo+1].play();
    }

    if(combo>10) {
    bgm[combo].play();
    }

    commandsystem.Clear(patafour);
    }

    if(commandsystem.Play()=="PonPonPataPon") {
    combo+=1;
    failClock.restart();
    nextpressClock.restart();

    if(combo>26)
    combo=11;

    if(combo==1)
    bgm[1].stop();

    if(combo<5)
    shouts_ponpon[1].play();

    if((combo>=5)&&(combo<=9))
    shouts_ponpon[2].play();

    if(combo>10) {
    shouts_ponpon[2+kolej].play();
    kolej+=1;
    }

    if(combo==10)
    bgm[28].play();

    if(combo<10)
    bgm[combo+1].play();

    if(combo>10)
    bgm[combo].play();

    commandsystem.Clear(patafour);
    }

    if(commandsystem.Play()=="ChakaChakaPataPon") {
    combo+=1;
    failClock.restart();
    nextpressClock.restart();

    if(combo>26)
    combo=11;

    if(combo==1)
    bgm[1].stop();

    if(combo<5)
    shouts_chakachaka[1].play();

    if((combo>=5)&&(combo<=9))
    shouts_chakachaka[2].play();

    if(combo>10) {
    shouts_chakachaka[2+kolej].play();
    kolej+=1;
    }

    if(combo==10)
    bgm[28].play();

    if(combo<10)
    bgm[combo+1].play();

    if(combo>10)
    bgm[combo].play();

    commandsystem.Clear(patafour);
    }

    if(commandsystem.Play()=="PonPonChakaChaka") {
    combo+=1;
    failClock.restart();
    nextpressClock.restart();

    if(combo>26)
    combo=11;

    if(combo==1)
    bgm[1].stop();

    if(combo<5)
    shouts_ponchaka[1].play();

    if((combo>=5)&&(combo<=9))
    shouts_ponchaka[2].play();

    if(combo>10)
    shouts_ponchaka[3].play();

    if(combo==10)
    bgm[28].play();

    if(combo<10)
    bgm[combo+1].play();

    if(combo>10)
    bgm[combo].play();

    commandsystem.Clear(patafour);
    }

    if(commandsystem.Play()=="PonPataPonPata") {
    combo+=1;
    failClock.restart();
    nextpressClock.restart();

    if(combo>26)
    combo=11;

    if(combo==1)
    bgm[1].stop();

    if(combo<5)
    shouts_ponpata[1].play();

    if((combo>=5)&&(combo<=9))
    shouts_ponpata[2].play();

    if(combo>10)
    shouts_ponpata[3].play();

    if(combo==10)
    bgm[28].play();

    if(combo<10)
    bgm[combo+1].play();

    if(combo>10)
    bgm[combo].play();

    commandsystem.Clear(patafour);
    }

    if(commandsystem.Play()=="DonDonChakaChaka") {
    combo+=1;
    failClock.restart();
    nextpressClock.restart();

    if(combo>26)
    combo=11;

    if(combo==1)
    bgm[1].stop();

    if(combo<5)
    shouts_dondon[1].play();

    if((combo>=5)&&(combo<=9))
    shouts_dondon[2].play();

    if(combo>10)
    shouts_dondon[3].play();

    if(combo==10)
    bgm[28].play();

    if(combo<10)
    bgm[combo+1].play();

    if(combo>10)
    bgm[combo].play();

    commandsystem.Clear(patafour);
    }

    if(commandsystem.Play()=="PataPonDonChaka") {
    combo+=1;
    failClock.restart();
    nextpressClock.restart();

    if(combo>26)
    combo=11;

    if(combo==1)
    bgm[1].stop();

    if(combo<5) {
    shouts_donchaka[1].play();
    kolej = 1;
    }

    if((combo>=5)&&(combo<=9))
    shouts_donchaka[2].play();

    if(combo>10)
    shouts_donchaka[3].play();

    if(combo==10)
    bgm[28].play();

    if(combo<10)
    bgm[combo+1].play();

    if(combo>10)
    bgm[combo].play();

    commandsystem.Clear(patafour);
    }

    if(commandsystem.Play()=="DonDonDonDonDon") {
    if(combo>=10) ///if fever
    {
    sutra.Play(camera,window);
    combo = 0;
    kolej = 1;
    }

    combo = 0;
    commandsystem.Clear(patafour);
    }

    commandClock.restart();
    }

    if(commandClock.getElapsedTime().asSeconds()>=1.9)
    {
    if(commandsystem.Play()=="") {
    cameramove = false;
    }

    if(commandsystem.Play()!="PataPataPataPon") {
    cameramove = false;
    }

    }

    if(commandClock.getElapsedTime().asSeconds()>=1.95)
    {

    if(commandsystem.Play()=="PataPataPataPon")
    {
        cameramove = true;
    }

    }

    if(cancameramove == true)
    if(cameramove == true)
    camera.x += 1.5;

    timeout -= 0.05;

    if(nextpressClock.getElapsedTime().asSeconds()<=1.85)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            failClock.restart();
            commandsystem.Clear(patafour);
            if(combo<10)
            bgm[combo+1].stop();
            if(combo>10)
            bgm[combo].stop();
            themeClock.restart();
            commandClock.restart();
            bgm[1].play();
            combo = 0; }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            failClock.restart();
            commandsystem.Clear(patafour);
            if(combo<10)
            bgm[combo+1].stop();
            if(combo>10)
            bgm[combo].stop();
            themeClock.restart();
            commandClock.restart();
            bgm[1].play();
            combo = 0; }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            failClock.restart();
            commandsystem.Clear(patafour);
            if(combo<10)
            bgm[combo+1].stop();
            if(combo>10)
            bgm[combo].stop();
            themeClock.restart();
            commandClock.restart();
            bgm[1].play();
            combo = 0; }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            failClock.restart();
            commandsystem.Clear(patafour);
            if(combo<10)
            bgm[combo+1].stop();
            if(combo>10)
            bgm[combo].stop();
            themeClock.restart();
            commandClock.restart();
            bgm[1].play();
            combo = 0; }
    }


    if(timeout <= 0)
    {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    failClock.restart();
    beatframe.Restart();
    timeout = 1; }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    failClock.restart();
    beatframe.Restart();
    timeout = 1; }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    failClock.restart();
    beatframe.Restart();
    timeout = 1; }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    failClock.restart();
    beatframe.Restart();
    timeout = 1; }
    }

    if(combo==0)
    if(failClock.getElapsedTime().asSeconds() >= 1) {
    failClock.restart();
    commandsystem.Clear(patafour);
    }

    if(combo!=0)
    if(failClock.getElapsedTime().asSeconds() >= 2.5) {
    failClock.restart();
    commandsystem.Clear(patafour);
    if(combo<10)
    bgm[combo+1].stop();
    if(combo>10)
    bgm[combo].stop();
    themeClock.restart();
    commandClock.restart();
    bgm[1].play();
    combo = 0; }

    if(combo!=0)
    if(failClock.getElapsedTime().asSeconds() >= 1) {
    commandsystem.Clear(patafour);
    }

    for(int i=0; i<=backgroundcount; i++)
    {
    if(backResizeToWindow[i]==true)
    background[i].setScale((double)window.getSize().x/(double)tex_background[i].getSize().x,(double)window.getSize().y/(double)tex_background[i].getSize().y);

    if(backSize[i].y!=0)
    background[i].setPosition(backSize[i].x,window.getSize().y-backSize[i].y);
    else
    background[i].setPosition(backSize[i].x,backSize[i].y);

    window.draw(background[i]);
    }

    commandsystem.Play();
    beatframe.Draw(window);
    }

    camera.ViewScreen(window);

    if(sutra.played==true)
    {
        sutra.Draw(window,camera,fps,patafour);
        patafour->sutraplayed = true;
    }

    if(sutra.played==false)
    {
        patafour->sutraplayed = false;
    }

    if(entities.size()-1>=0) {
    for(int i=0; i<=entities.size()-1; i++) {
        entities[i].DrawObjects(window);
    }}

    ///for(int i=0; i<=cutscenes.size()-1; i++) {
    ///    cout << "cutscene work" << endl;
    ///    cutscenes[i].Draw(window);
    ///}
}

Mission::~Mission()
{
}
