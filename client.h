#ifndef CLIENT_H
#define CLIENT_H

#include <cstdio>
#include <cstdlib>

#include <winsock2.h>
#include <SFML/Graphics.hpp>

#include "patapon.h"
#include "resources.h"
#include "mission.h"

class Client
{
    public:
    WSADATA wsaData;
    SOCKET mainSocket;
    sockaddr_in service;

    int x;
    int y;

    PataponRes res;
    Patapon player1,player2;
    sf::Font font;
    sf::View multiview;

    std::string myname;

    sf::Text text1,text2;

    Client();
    int Connect(const char* ip);
    void Multiplayer();
    void Draw(sf::RenderWindow& window, Mission& mission);
};

#endif // CLIENT_H
