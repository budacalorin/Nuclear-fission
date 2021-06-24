#ifndef NEUTRON_H
#define NEUTRON_H
#include <SFML/Graphics.hpp>

class neutron
{
public:
    sf::CircleShape forma;
    sf::Vector2f viteza;

    neutron();
    void set_position(sf::Vector2f pozitie);
};

#endif // NEUTRON_H
