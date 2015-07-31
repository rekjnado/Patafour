#ifndef MATERTREESUBMENU_H
#define MATERTREESUBMENU_H

#include <SFML/Graphics.hpp>
#include "savecontainer.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class MaterTreeSubmenu
{
    public:
    sf::Texture tex_overlay;
    sf::Texture tex_overlay_dark;

    sf::Texture tex_rarepon_default;
    sf::Texture tex_rarepon_default_big;
    sf::Texture tex_rarepon_blank;
    sf::Texture tex_rarepon_blank_big;
    sf::Texture tex_arrow,tex_background;
    sf::Texture tex_icon[10];

    sf::Texture tex_popup_question;
    sf::Texture tex_popup_selected;
    sf::Texture tex_popup_notavailable;

    sf::Sprite overlay[9];
    sf::Sprite overlay_dark[9];

    sf::Sprite rarepon_default[50];
    sf::Sprite rarepon_default_big[50];
    sf::Sprite rarepon_blank[50];
    sf::Sprite rarepon_blank_big[50];
    sf::Sprite arrow,background;

    sf::Sprite popup_question;
    sf::Sprite popup_selected;
    sf::Sprite popup_notavailable;

    sf::Sprite icon[10];

    sf::Font komika;
    sf::Font comicsans;

    sf::Text patatext[10];
    sf::Text question,item[3],yes,no,close,cannotbuy;

    bool opened;
    bool buypatapon;
    bool showcannotbuy;
    int maxonscreen;
    int selected;
    int selectedonscreen;
    float timeout;
    bool visible[9];
    int horselected;
    bool buyoption;

    bool materorbsareplayed;

    int amountoftries;

    vector<string> toMake;

    std::string tobuy;

    XMLDocument doc;

    MaterTreeSubmenu();
    void Draw(sf::RenderWindow& window, SaveContainer& savecontainer);
    void Open();
    void Close();
};

#endif // MATERTREESUBMENU_H
