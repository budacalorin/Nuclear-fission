#ifndef INITIALIZARI_H_INCLUDED
#define INITIALIZARI_H_INCLUDED

#include "init.h"
int raza_protoni=10;
int raza_neutroni=10;
/*sf::Color culoare_protoni(200,0,0);
sf::Color culoare_neutroni(128,128,128);     // Rosu cu gri
sf::Color culoare_protoni_stabili( 200,0,0,150);
sf::Color culoare_neutroni_stabili(128,128,128,150);*/

sf::Color culoare_protoni(255,89,0);
sf::Color culoare_neutroni(0,131,255);     // Albastru cu protocaliu
sf::Color culoare_protoni_stabili(255,89,0,150);
sf::Color culoare_neutroni_stabili(0,131,255,150);

int hight=768;
int width=1366;
bool game_on=1;
int scena_curenta=1;
float indice_viteza=2.5;
int cooldown_explozii=1000000;
int numar_spawn_p=4;
int numar_spawn_n=4;
int raza_aparitie_atomi_noi=100;
int raza_atomului=20;
float indice_frecare=1;



#endif // INITIALIZARI_H_INCLUDED
