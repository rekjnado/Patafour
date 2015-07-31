#ifndef SERVER_H
#define SERVER_H

#include <cstdio>
#include <cstdlib>

#include <winsock2.h>
#include <SFML/Graphics.hpp>

#include "patapon.h"
#include "resources.h"
#include "mission.h"

class Server
{
    public:
    WSADATA wsaData;
    SOCKET mainSocket;
    sockaddr_in service;
    SOCKET acceptSocket;

    int x;
    int y;

    PataponRes res;
    Patapon player1,player2;

    std::string myname;

    sf::Font font;
    sf::Text text1,text2;

    sf::View multiview;

    Server();
    int Connect(const char* ip);
    void Multiplayer();
    void Draw(sf::RenderWindow& window, Mission& mission);
};

#endif // SERVER_H
