#include "proton.h"
#include "init.h"

proton::proton()
{
    forma.setFillColor(culoare_protoni);
    forma.setRadius(raza_protoni);
    forma.setOrigin(sf::Vector2f(raza_protoni,raza_protoni));
}
void proton::set_position(sf::Vector2f pozitie)
{
    forma.setPosition(pozitie);
}


