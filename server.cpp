#include <iostream>
#include "server.h"

#include <cstdio>
#include <cstdlib>
#include <sstream>

#include <winsock2.h>
#include <SFML/Graphics.hpp>

#include "patapon.h"
#include "resources.h"
#include "mission.h"

using namespace std;

Server::Server()
{
x=0;
y=0;
font.loadFromFile("resources/fonts/majalla.ttf");
player1.LoadResources(res);
player2.LoadResources(res);
text1.setColor(sf::Color::Green);
text2.setColor(sf::Color::Blue);
text1.setCharacterSize(24);
text2.setCharacterSize(24);
text1.setFont(font);
text2.setFont(font);

cout << "insert you name :)" << endl;
cin>>myname;

text1.setString(myname);
}

int Server::Connect(const char* ip)
{
    int result = WSAStartup( MAKEWORD( 2, 2 ), & wsaData );
    if( result != NO_ERROR )
    printf( "Initialization error.\n" );

    mainSocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
    if( mainSocket == INVALID_SOCKET )
    {
        printf( "Error creating socket: %d\n", WSAGetLastError() );
        WSACleanup();
        return 1;
    }

    memset( & service, 0, sizeof( service ) );
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr(ip);
    service.sin_port = htons( 27015 );

    if( bind( mainSocket,( SOCKADDR * ) & service, sizeof( service ) ) == SOCKET_ERROR )
    {
        printf( "bind() failed.\n" );
        closesocket( mainSocket );
        return 1;
    }

    if(listen( mainSocket, 1 ) == SOCKET_ERROR)
    printf("Error listening on socket.\n");

    acceptSocket = SOCKET_ERROR;
    printf( "Waiting for a client to connect...\n" );

    while( acceptSocket == SOCKET_ERROR )
    {
        acceptSocket = accept( mainSocket, NULL, NULL );
    }

    printf( "Client connected.\n" );
    mainSocket = acceptSocket;
    return 0;
}

void Server::Multiplayer()
{
    ostringstream a,b;
    a << player1.x;
    b << player1.y;
    string sx = a.str();
    string sy = b.str();
    string full = sx+","+sy+","+myname;
    char* cyka = new char[full.length() + 1];
    strcpy(cyka, full.c_str());

    int bytesSent;
    int bytesRecv = SOCKET_ERROR;
    char* sendbuf = cyka;
    char recvbuf[128] = "";

    bytesRecv = recv(mainSocket, recvbuf, sizeof(recvbuf), 0);

    string recvinfo(recvbuf);
    string x = recvinfo.substr(0,recvinfo.find_first_of(","));
    string pa = recvinfo.substr(recvinfo.find_first_of(",")+1);
    string y = pa.substr(0,pa.find_first_of(","));
    string name = pa.substr(pa.find_first_of(",")+1);
    int ix;
    int iy;
    istringstream ia(x);
    istringstream ib(y);
    ia >> ix;
    ib >> iy;
    player2.x = ix;
    text2.setString(name);

    bytesSent = send(mainSocket, sendbuf, strlen( sendbuf ), 0);
}

void Server::Draw(sf::RenderWindow& window, Mission& mission)
{
    window.setView(multiview);
    multiview.setCenter(sf::Vector2f(x, window.getSize().y/2));
    multiview.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        player1.move(-1,0);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        player1.move(1,0);
    }

    player1.y = window.getSize().y-50;
    player2.y = window.getSize().y-50;

    x = player1.x;
    y = player1.y;

    //player2.draw(window);
    //player1.draw(window);

    text1.setPosition(x-50,y-50);
    text2.setPosition(player2.x-50,player2.y-50);
    window.draw(text1);
    window.draw(text2);
}
