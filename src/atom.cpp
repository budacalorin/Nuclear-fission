#include "atom.h"
#include "init.h"
void atom::setup(int numar_protoni,int numar_neutroni,bool stabilitate)
{
    this->numar_neutroni=numar_neutroni;
    this->numar_protoni=numar_protoni;
    alive=1;
    stabil=stabilitate;
    if (stabilitate==1)
    {
        for (int i=1;i<=numar_neutroni;i++)
            neutroni[i].forma.setFillColor(culoare_neutroni_stabili);
        for (int i=1;i<=numar_protoni;i++)
            protoni[i].forma.setFillColor(culoare_protoni_stabili);
    }
    if (stabilitate==0)
    {
        for (int i=1;i<=numar_neutroni;i++)
            neutroni[i].forma.setFillColor(culoare_neutroni);
        for (int i=1;i<=numar_protoni;i++)
            protoni[i].forma.setFillColor(culoare_protoni);
    }
}

void atom::set_position(sf::Vector2f pozitie)
{
    for (int i=1;i<=numar_protoni;i++)
    {
        protoni[i].set_position(sf::Vector2f(pozitie.x+rand()%(raza_atomului*2)-raza_atomului,pozitie.y+rand()%(raza_atomului*2)-raza_atomului));
    }
    for (int i=1;i<=numar_neutroni;i++)
    {
        neutroni[i].set_position(sf::Vector2f(pozitie.x+rand()%(raza_atomului*2)-raza_atomului,pozitie.y+rand()%(raza_atomului*2)-raza_atomului));
    }
    this->pozitie=pozitie;
}

bool atom::coliziune(sf::CircleShape collider)
{
    for (int i=1;i<=numar_neutroni;i++)
        if (collider.getGlobalBounds().intersects(neutroni[i].forma.getGlobalBounds()))
            return 1;
    for (int i=1;i<=numar_protoni;i++)
        if (collider.getGlobalBounds().intersects(protoni[i].forma.getGlobalBounds()))
            return 1;
    return 0;
}
