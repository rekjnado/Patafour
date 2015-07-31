#include <iostream>
#include "beatframe.h"
#include <SFML/Graphics.hpp>

using namespace std;

BeatFrame::BeatFrame()
{
    cout << "beatframe has begun" << endl;
    alpha = 255;
    Frame_1.setFillColor(sf::Color(0, 0, 0, 0));
    Frame_1.setOutlineThickness(1);
    Frame_1.setOutlineColor(sf::Color(255,255,255,alpha));
    Frame_1.setPosition(6,6);
    clock.restart();
}

void BeatFrame::Start()
{
    cout << "beatframe start!" << endl;
    clock.restart();
}

void BeatFrame::Restart()
{
    alpha=255;
    clock.restart();
}

void BeatFrame::Draw(sf::RenderWindow& window)
{
    if(clock.getElapsedTime().asMilliseconds()<=300) {
    alpha -= 15;
    if(alpha <= 0)
    alpha = 0; }

    ///4.05
    ///2.025
    ///1.0125
    ///0.50625

    if(clock.getElapsedTime().asMilliseconds()>=497) {
    alpha = 255;
    }

    if(clock.getElapsedTime().asMilliseconds()>=500) {
    clock.restart();
    }


    Frame_1.setOutlineColor(sf::Color(255,255,255,alpha));

    Frame_1.setSize(sf::Vector2f(window.getSize().x-12, window.getSize().y-12));
    window.draw(Frame_1);
}
