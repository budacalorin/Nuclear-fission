#ifndef ATOM_H
#define ATOM_H
#include "neutron.h"
#include "proton.h"

class atom
{
public:
    neutron neutroni[50];
    proton protoni[200];
    int numar_protoni;
    int numar_neutroni;
    bool alive;
    bool stabil;
    sf::Vector2f pozitie;


    void setup(int numar_protoni,int numar_neutroni,bool stabilitate);
    void set_position(sf::Vector2f pozitie);
    bool coliziune(sf::CircleShape collider);

};

#endif // ATOM_H
