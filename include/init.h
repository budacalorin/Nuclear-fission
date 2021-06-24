#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED
#include <SFML/Graphics.hpp>

extern int raza_protoni;
extern int raza_neutroni;
extern sf::Color culoare_protoni;
extern sf::Color culoare_neutroni;
extern sf::Color culoare_protoni_stabili;
extern sf::Color culoare_neutroni_stabili;
extern sf::RenderWindow window;
extern int hight;
extern int width;
extern bool game_on;
extern int scena_curenta;
extern sf::RectangleShape background;
extern float indice_viteza;
extern int cooldown_explozii;
extern int numar_spawn_p,numar_spawn_n;
extern int raza_aparitie_atomi_noi;
extern int raza_atomului;
extern float indice_frecare;

#endif // INIT_H_INCLUDED
