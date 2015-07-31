#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class LoginDialog
{
    public:
    string login,pass;

    LoginDialog();
    void Draw(sf::RenderWindow& window);
};
