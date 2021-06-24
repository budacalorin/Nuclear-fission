#ifndef PROTON_H
#define PROTON_H
#include <SFML/Graphics.hpp>

class proton
{
public:
    sf::CircleShape forma;
    sf::Vector2f viteza;

    proton();
    void set_position(sf::Vector2f pozitie);
};

#endif // PROTON_H
