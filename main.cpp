#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "init.h"
#include "include/scena_joc.h"
#include "include/scena_meniu.h"
#include "initializari.h"
#define PI 3.14159265
using namespace std;


scena_meniu meniu_principal;
scena_joc joc_principal;
sf::Texture background_texture;
sf::Texture *p_background_texture;
sf::RectangleShape background;
sf::RenderWindow window;

sf::Clock ceas_general;
char s[256];
int main()
{
    cout << "Left Click: Deployes unstable atom.\nRight Click: Deployes neutron.\nHold right click to aim it.\n";
    cout << "Press enter to continue!\n";
    bool ok=0;
    do
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            ok=1;
    }while(ok==0);
    srand(time(0));
    window.create(sf::VideoMode(width,hight),"",sf::Style::None);
    background_texture.loadFromFile("img/background.png");
    p_background_texture=&background_texture;
    background.setTexture(p_background_texture);
    background.setSize(sf::Vector2f(width,hight));
    meniu_principal.adaugare_optiune("PLAY");
    meniu_principal.adaugare_optiune("EXIT");

    sf::Clock ceas;
    sf::Clock c;
    int fps=0;
    int timp_per_frame=1000000/120;
    while (game_on)
    {
        fps++;
        if (c.getElapsedTime().asSeconds()>=1)
        {
            c.restart();
            //cout << fps << endl;
            fps=0;
        }
        int timp=ceas.getElapsedTime().asMicroseconds();

        if (scena_curenta==1)
        {
            meniu_principal.update();
        }
        if (scena_curenta==2)
        {
            joc_principal.update();
        }


        if (ceas.getElapsedTime().asMicroseconds()-timp<timp_per_frame)
            sf::sleep(sf::microseconds(timp_per_frame-(ceas.getElapsedTime().asMicroseconds()-timp)));
    }

    return 0;
}
