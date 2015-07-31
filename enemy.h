#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

using namespace std;

class Enemy
{
    /**
    public:
    std::map<sf::Texture, string> objtextures;
    std::map<sf::Sprite, string> objsprites;
    std::map<string, int> objname;

    Enemy(string name);
    */

    public:
    int objectamount;
    int animationID;
    int objectID;
    int textureID;
    string projectname="Untitled";
    string objectname[50];
    string texturename[50];
    string animation[15];
    map<string,sf::Texture> texture;
    map<string,sf::Sprite> object;
    sf::Sprite support[50];
    bool selected[50];
    sf::Texture tex_grind;
    sf::Sprite grind;
    int selectedID;
    int animationcount;
    string objecttexfile[50];
    string objecttexpath[50];
    string projectcenter="0",projectstrength="100";
    int currentframe;
    int framelimit[15];
    int currentAnimationID;
    bool isframemodified[15][500][50];
    float objectx,objecty;
    int objectheight;

    bool play;
    bool repeat;
    bool visible;
    bool collide;
    bool completeafterwalk;

    string objects[50][15][500];
    sf::Texture null;

    Enemy(string name, int xposition, int objh);
    void ShowFrame(int animationid, int frame);
    int ReadAnimationFile(string path);
    int GetObjectID(string name);
    void NewObject(string& filename, string name, float x, float y);
    void NewAnimation(string tname, int flimit);
    void DrawObjects(sf::RenderWindow& window);
    void Move(float x, float y);
    sf::Vector2f GetObjectLocation();
    sf::FloatRect GetObjectSize();

};

#endif // ENEMY_H
