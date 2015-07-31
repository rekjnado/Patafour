#include <iostream>
#include <SFML/Graphics.hpp>

#include "enemy.h"

#include <fstream>
#include <sstream>

int stoi(string s)
{
     int tmp = 0, i = 0;
     bool m = false;
     if(s[0] == '-') {
      m = true;
      i++;
     }
     for(; i < s.size(); i++)
      tmp = 10 * tmp + s[i] - 48;
     return m ? -tmp : tmp;
}

double stof(string s)
{
    return atof(s.c_str());
}

inline bool fexists (const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

template <typename T>
std::string ttos(T value)
    {
    std::ostringstream os;
    os << value;
    return os.str();
    }

int Enemy::GetObjectID(string name)
{
int id;
for(int i=0; i<=49; i++)
{
if(objectname[i]==name)
id=i;
}

return id;
}

void Enemy::NewObject(string& filename, string name, float x, float y)
{
if(animationcount>=1)
{
cout << "loading textures" << endl;
texturename[objectamount]=name;
if(texture[texturename[objectamount]].loadFromFile(filename.c_str()))
{
texture[texturename[objectamount]].loadFromFile(filename.c_str());

cout << "setting things" << endl;
cout << "first " << objectamount << " " << filename << endl;
objecttexpath[objectamount] = filename;
cout << "second" << endl;
unsigned found = filename.find_last_of("/\\");
cout << "third" << endl;
objecttexfile[objectamount]=filename.substr(found+1);

cout << "main" << endl;
objectname[objectamount]=name;
object[objectname[objectamount]].setTexture(texture[texturename[objectamount]]);
support[objectamount].setTexture(texture[texturename[objectamount]]);
object[objectname[objectamount]].setTexture(texture[texturename[objectamount]]);
object[objectname[objectamount]].setPosition(x,y);
object[objectname[objectamount]].setOrigin(texture[texturename[objectamount]].getSize().x/2,texture[texturename[objectamount]].getSize().y/2);
grind.setRotation(0);
objectamount += 1;
}}
else
cout << "Error 1: Nie mozna stworzyc obiektu. (Nie zaznaczono animacji)" << endl;

}

void Enemy::NewAnimation(string tname, int flimit)
{
string name=tname;
string limit=ttos(flimit);
framelimit[animationcount] = stoi(limit);
animation[animationcount] = name;
animationcount += 1;
currentAnimationID = animationcount;
currentframe=0;
}

int Enemy::ReadAnimationFile(string path)
{
ifstream file(path.c_str());
string line;
bool checkheader=false;
bool configload=false;
bool objectload=false;
bool animationload=false;
bool animationread=false;
int animationid=0;

string folderpath=path.substr(0,path.find_last_of("/\\")+1);

cout << folderpath+"param.dat" << endl;
if(fexists(folderpath+"param.dat"))
{
    ifstream file2(string(folderpath+"param.dat").c_str());
    string line2;

    if(file2.is_open()) {
    while(getline(file2,line2)) {

    if(line2.substr(0,line2.find_first_of(":"))=="collides")
    {
        if(line2.substr(line2.find_first_of(":")+1)=="no")
        collide = false;

        if(line2.substr(line2.find_first_of(":")+1)=="yes")
        collide = true;
    }

    if(line2.substr(0,line2.find_first_of(":"))=="onPassEvent")
    {
        if(line2.substr(line2.find_first_of(":")+1)=="completeMission")
        completeafterwalk = true;
    }

    }
    file2.close();
    }
}

cout << "COLLIDES: " << collide << endl;
cout << "COMPLETE AFTER WALK THROUGH: " << completeafterwalk << endl;

if(file.is_open()) {
while(getline(file,line)) {

///Check if file header is ok
if(checkheader==false)
{
if(line=="Patafour Enemy File")
{
cout << "Sygnatura pliku poprawna" << endl;
checkheader=true;
} else {
cout << "Niewlasciwa sygnatura pliku" << endl;
return 3;
}}
///Reading start
if(line=="[Config]")
configload=true;

if(configload==true)
{
if(line.substr(0,line.find_first_of(":"))=="Name")
projectname=line.substr(line.find_first_of(":")+1);
if(line.substr(0,line.find_first_of(":"))=="Center")
projectcenter=line.substr(line.find_first_of(":")+1);
if(line.substr(0,line.find_first_of(":"))=="Strength") {
projectstrength=line.substr(line.find_first_of(":")+1);
configload=false;
}}

if(animationload==true)
{
string tname,frames;
frames=line.substr(line.find_first_of(":")+1);
tname=line.substr(0,line.find_first_of(":"));

if(line!="")
NewAnimation(tname,stoi(frames));
else
animationload=false;
}

if(line=="[Animations]")
animationload=true;

if(objectload==true)
{
string tdir,tname;
tdir=folderpath+line.substr(line.find_first_of(":")+1);
tname=line.substr(0,line.find_first_of(":"));

if(line!="") {
NewObject(tdir,tname,0,0);
} else {
objectload=false;
}}

if(line=="[Objects]")
objectload=true;

if(animationread==true)
{
string temp,frame,name;
int iname;
temp=line.substr(0,line.find_first_of("]"));
frame=temp.substr(temp.find_first_of("[")+1);
name=line.substr(0,line.find_first_of("["));
iname=GetObjectID(name);
if(line!="") {
cout << line << endl;
objects[iname][animationid][atoi(frame.c_str())]=line.substr(line.find_first_of(":")+1);
cout << objects[iname][animationid][atoi(frame.c_str())] << endl;
cout << iname << " " << animationid << " " << frame << endl;
} else {
animationread=false;
ShowFrame(animationid,0); }
}

if(line.substr(0,11)=="[Animation:")
{
animationid+=1;
animationread=true;
}

///Read end
}
file.close();
}
return 0;
}

Enemy::Enemy(string name, int xposition, int objh)
{
    objectamount = 0;
    currentAnimationID = 0;
    animationcount = 0;

    play = true;
    repeat = true;
    visible = true;
    collide = true;
    completeafterwalk = false;

    objectx = xposition;
    objectheight = objh;

    char cudzyslow=0x22;
    string fileload = "resources/entities/"+name+".enm";
    string folderpath = "resources/entities/"+name+"/";
    string a="pack e ",b=" -o";
    string c="rmdir ",d=" /s /q";
    string command=a+cudzyslow+fileload+cudzyslow+b+cudzyslow+folderpath+cudzyslow;
    string rcommand=c+cudzyslow+folderpath+cudzyslow+d;

    system(command.c_str());
    ///Reading here
    string filename="resources/entities/"+name+"/"+name+".anim";

    ReadAnimationFile(filename);

    system(rcommand.c_str());
}

void Enemy::ShowFrame(int animationid, int frame)
{
    for(int i=0; i<objectamount; i++)
    {
    string x,y,angle;
    string temp;
    unsigned found=objects[i][animationid][frame].find_first_of(",");
    x=objects[i][animationid][frame].substr(0,found);
    temp=objects[i][animationid][frame].substr(found+1);
    unsigned found2=temp.find_first_of(",");
    y=temp.substr(0,found2);
    string temp2=temp.substr(found2+1);
    angle=temp2.substr(0,temp2.find_first_of(","));
    string temp3=temp2.substr(temp2.find_first_of(",")+1);
    string scalex,scaley;
    scalex=temp3.substr(0,temp3.find_first_of(","));
    scaley=temp3.substr(temp3.find_first_of(",")+1);
    if(scalex==angle)
    scalex="1";
    if(scaley==angle)
    scaley="1";

    object[objectname[i]].setTexture(texture[texturename[i]]);
    object[objectname[i]].setPosition(objectx+stof(x),objecty+stof(y));
    object[objectname[i]].setRotation(stof(angle));
    object[objectname[i]].setScale(stof(scalex),stof(scaley));
    }
}

void Enemy::DrawObjects(sf::RenderWindow& window)
{
objecty = window.getSize().y-objectheight;

if(repeat==true)
{
if(currentframe >= framelimit[currentAnimationID])
{
    currentframe = 0;
}}

if(play==true)
{
currentframe += 1;
ShowFrame(currentAnimationID,currentframe);
}

if(visible==true)
{
for(int i=0; i<=objectamount; i++)
{
window.draw(object[objectname[i]]);
}}}

void Enemy::Move(float x, float y)
{
    objectx += x;
    objecty += y;
}

sf::Vector2f Enemy::GetObjectLocation()
{
    return sf::Vector2f(objectx,objecty);
}

sf::FloatRect Enemy::GetObjectSize()
{
    return sf::FloatRect(10,10,100,100);
}
