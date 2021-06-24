#include "neutron.h"
#include "init.h"

neutron::neutron()
{
    forma.setFillColor(culoare_neutroni);
    forma.setRadius(raza_neutroni);
    forma.setOrigin(sf::Vector2f(raza_neutroni,raza_neutroni));
}

void neutron::set_position(sf::Vector2f pozitie)
{
    forma.setPosition(pozitie);
}
