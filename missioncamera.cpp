#include <iostream>
#include <SFML/Graphics.hpp>

#include "missioncamera.h"

MissionCamera::MissionCamera()
{
x = 100;
}

void MissionCamera::ViewScreen(sf::RenderWindow& window)
{
    window.setView(cameraview);
    cameraview.setCenter(sf::Vector2f(x, window.getSize().y/2));
    cameraview.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
}
