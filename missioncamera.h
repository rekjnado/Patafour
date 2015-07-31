#ifndef MISSIONCAMERA_H
#define MISSIONCAMERA_H

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class MissionCamera
{
    public:
    sf::View cameraview;
    float x;

    MissionCamera();
    void ViewScreen(sf::RenderWindow& window);
};

#endif // MISSIONCAMERA_H
