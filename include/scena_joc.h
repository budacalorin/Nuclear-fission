#ifndef SCENA_JOC
#define SCENA_JOC
#include "atom.h"
class scena_joc
{
public:

    atom atomi[500];
    int numar_atomi;
    struct neutron_liber
    {
        bool alive=0;
        neutron neutronul;
        int unghi;
        float indice_viteza=1;
    } neutroni_liberi[1000];
    int numar_neutroni_liberi;
    bool e_click_dreapta_apasat=0;
    struct explozie
    {
        int cooldown=0;
        sf::CircleShape forma;
        bool alive=0;
    }explozii[500];
    int numar_explozii;
    long long timp_precedent;
    int indice_neutron_selectat;



    void draw();
    void verificare_final();

    void update();
    void update_pozitii();
    void update_events();
    void draw_atomi();
    void draw_neutroni_liberi();
    void update_neutroni_liberi();
    void update_explozii();
    void draw_explozii();
    int new_atom();
    int new_neutron();
    int new_explozie();

    void reset(int x);
};


#endif
