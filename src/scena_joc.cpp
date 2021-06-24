#include "../include/scena_joc.h"
#include "../include/init.h"
#include "../include/time.h"
#include <iostream>
using namespace std;

void scena_joc::update()
{

    update_events();
    update_pozitii();
    update_neutroni_liberi();
    update_explozii();

    draw();
}

void scena_joc::draw()
{
    window.clear();

    window.draw(background);
    draw_atomi();
    draw_neutroni_liberi();
    draw_explozii();


    window.display();
}


void scena_joc::verificare_final()
{

}

void scena_joc::reset(int x)
{
    numar_atomi=0;
    numar_neutroni_liberi=0;

}

void scena_joc::update_events()
{
    sf::Mouse mouse;
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type==sf::Event::Closed)
            game_on=0;
        if (event.type==sf::Event::KeyPressed&&event.key.code==sf::Keyboard::Escape)
            scena_curenta=1;
        if (event.type==sf::Event::MouseButtonPressed&&event.mouseButton.button==sf::Mouse::Left)
        {
            //cout << "da";
            int indice=new_atom();
            atomi[indice].alive=1;
            atomi[indice].stabil=0;
            atomi[indice].setup(numar_spawn_p,numar_spawn_n,0);
            atomi[indice].set_position(sf::Vector2f(mouse.getPosition(window).x,mouse.getPosition(window).y));
        }
        if (event.type==sf::Event::MouseButtonPressed&&event.mouseButton.button==sf::Mouse::Right)
        {
            e_click_dreapta_apasat=1;
            int indice=new_neutron();
            neutroni_liberi[indice].alive=1;
            neutroni_liberi[indice].neutronul.set_position(sf::Vector2f(mouse.getPosition(window).x,mouse.getPosition(window).y));
            neutroni_liberi[indice].neutronul.viteza.x=0;
            neutroni_liberi[indice].neutronul.viteza.y=0;
            indice_neutron_selectat=indice;
        }
        if (event.type==sf::Event::MouseButtonReleased&&event.mouseButton.button==sf::Mouse::Right)
        {
            e_click_dreapta_apasat=0;
            float PI=3.14159265;
            int unghi=atan2(neutroni_liberi[indice_neutron_selectat].neutronul.forma.getPosition().x-mouse.getPosition(window).x,neutroni_liberi[indice_neutron_selectat].neutronul.forma.getPosition().y-mouse.getPosition(window).y)*180/PI;

            if (unghi<0)
                unghi+=360;
            unghi+=90;
            unghi%=360;
            neutroni_liberi[indice_neutron_selectat].unghi=unghi;
            neutroni_liberi[indice_neutron_selectat].neutronul.viteza.x=cos(unghi*PI/180);
            neutroni_liberi[indice_neutron_selectat].neutronul.viteza.y=-sin(unghi*PI/180);

            sf::Vector2f pozitie=neutroni_liberi[indice_neutron_selectat].neutronul.forma.getPosition();
            double distanta=sqrt( (pozitie.x-mouse.getPosition(window).x)*(pozitie.x-mouse.getPosition(window).x) + (pozitie.y-mouse.getPosition(window).y)*(pozitie.y-mouse.getPosition(window).y) );
            neutroni_liberi[indice_neutron_selectat].indice_viteza=distanta/100;
            //cout << unghi <<"x:" << neutroni_liberi[indice_neutron_selectat].neutronul.viteza.x<< " y:" <<neutroni_liberi[indice_neutron_selectat].neutronul.viteza.y <<endl;
        }
        if (event.type==sf::Event::KeyPressed&&event.key.code==sf::Keyboard::R)
        {
            for (int i=1; i<=numar_atomi; i++)
            {
                atomi[i].alive=0;
            }
            numar_atomi=0;

            for (int i=1; i<=numar_neutroni_liberi; i++)
            {
                neutroni_liberi[i].alive=0;
                neutroni_liberi[i].neutronul.viteza.x=0;
                neutroni_liberi[i].neutronul.viteza.y=0;

            }
            numar_neutroni_liberi=0;
            e_click_dreapta_apasat=0;
        }


    }
}

void scena_joc::draw_atomi()
{
    for (int i=1; i<=numar_atomi; i++)
    {
        if (atomi[i].alive&&atomi[i].stabil==1)
        {

            int j=1;
            int k=1;
            int turn=1;
            while (j<=atomi[i].numar_neutroni&&k<=atomi[i].numar_protoni)
            {
                if (turn==1)
                {
                    window.draw(atomi[i].neutroni[j].forma);
                    j++;
                }
                else
                {
                    window.draw(atomi[i].protoni[k].forma);
                    k++;

                }
                turn=1-turn;
            }
            while (j<=atomi[i].numar_neutroni)
            {
                window.draw(atomi[i].neutroni[j].forma);
                j++;
            }
            while (k<=atomi[i].numar_protoni)
            {
                window.draw(atomi[i].protoni[k].forma);
                k++;
            }
        }
    }
    for (int i=1; i<=numar_atomi; i++)
    {
        if (atomi[i].alive&&atomi[i].stabil==0)
        {

            int j=1;
            int k=1;
            int turn=1;
            while (j<=atomi[i].numar_neutroni&&k<=atomi[i].numar_protoni)
            {
                if (turn==1)
                {
                    window.draw(atomi[i].neutroni[j].forma);
                    j++;
                }
                else
                {
                    window.draw(atomi[i].protoni[k].forma);
                    k++;
                }
                turn=1-turn;
            }
            while (j<=atomi[i].numar_neutroni)
            {
                window.draw(atomi[i].neutroni[j].forma);
                j++;
            }
            while (k<=atomi[i].numar_protoni)
            {
                window.draw(atomi[i].protoni[k].forma);
                k++;
            }
        }
    }
}

void scena_joc::draw_neutroni_liberi()
{
    for (int i=1; i<=numar_neutroni_liberi; i++)
        if (neutroni_liberi[i].alive)
            window.draw(neutroni_liberi[i].neutronul.forma);

    if (e_click_dreapta_apasat)
    {
        sf::Mouse mouse;
        sf::Vertex linie[]=
        {
            sf::Vertex(sf::Vector2f(mouse.getPosition(window).x,mouse.getPosition(window).y)),
            sf::Vertex(neutroni_liberi[indice_neutron_selectat].neutronul.forma.getPosition())
        };
        linie[0].color=sf::Color::Red;
        linie[1].color=culoare_neutroni;
        window.draw(linie,2,sf::Lines);
    }
}

void scena_joc::update_pozitii()
{
    for (int i=1; i<=numar_neutroni_liberi; i++)
    {
        if (neutroni_liberi[i].alive)
        {
            neutroni_liberi[i].neutronul.viteza.x*=indice_frecare;
            neutroni_liberi[i].neutronul.viteza.y*=indice_frecare;
            if (neutroni_liberi[i].neutronul.viteza.x<0.01&&neutroni_liberi[i].neutronul.viteza.x>-0.01)
                neutroni_liberi[i].neutronul.viteza.x=0;
            if (neutroni_liberi[i].neutronul.viteza.y<0.01&&neutroni_liberi[i].neutronul.viteza.y>-0.01)
                neutroni_liberi[i].neutronul.viteza.y=0;
            sf::Vector2f viteza=neutroni_liberi[i].neutronul.viteza;
            neutroni_liberi[i].neutronul.forma.move(sf::Vector2f(viteza.x*indice_viteza*neutroni_liberi[i].indice_viteza,viteza.y*indice_viteza*neutroni_liberi[i].indice_viteza));
        }
    }
}

void scena_joc::update_neutroni_liberi()
{
    for (int i=1; i<=numar_neutroni_liberi; i++)
        if (neutroni_liberi[i].alive)
        {
            sf::Vector2f pozitie=neutroni_liberi[i].neutronul.forma.getPosition();
            if (pozitie.x>width+100||pozitie.x<-10||pozitie.y>hight+100||pozitie.y<-10)
                neutroni_liberi[i].alive=0;

        }
    for (int i=1; i<=numar_neutroni_liberi; i++)
    {
        if (neutroni_liberi[i].alive)
        {
            for (int j=1; j<=numar_atomi; j++)
            {
                if (atomi[j].stabil==0&&atomi[j].alive)
                {
                    if (atomi[j].coliziune(neutroni_liberi[i].neutronul.forma))
                    {
                        int indice=new_atom();
                        atomi[indice].setup(atomi[j].numar_protoni/2,atomi[j].numar_neutroni/2,1);
                        atomi[indice].set_position(sf::Vector2f(atomi[j].pozitie.x+rand()%(raza_aparitie_atomi_noi*2)-raza_aparitie_atomi_noi,atomi[j].pozitie.y+rand()%(raza_aparitie_atomi_noi*2)-raza_aparitie_atomi_noi));

                        int indice2=new_atom();
                        atomi[indice2].setup(atomi[j].numar_protoni/2,atomi[j].numar_neutroni/2,1);
                        atomi[indice2].set_position(sf::Vector2f(atomi[j].pozitie.x+rand()%(raza_aparitie_atomi_noi*2)-raza_aparitie_atomi_noi,atomi[j].pozitie.y+rand()%(raza_aparitie_atomi_noi*2)-raza_aparitie_atomi_noi));

                        sf::Vector2f a1=atomi[indice].pozitie;
                        sf::Vector2f a2=atomi[indice2].pozitie;


                        sf::Vector2f poz=sf::Vector2f((a1.x+a2.x)/2,(a1.y+a2.y)/2);
                        double d1=sqrt( (poz.x-a1.x)*(poz.x-a1.x) + (poz.y-a1.y)*(poz.y-a1.y) );
                        double d2=sqrt( (poz.x-a2.x)*(poz.x-a2.x) + (poz.y-a2.y)*(poz.y-a2.y) );
                        double raza=max(d1,d2);
                        float PI=3.14159265;
                        indice=new_neutron();
                        int unghi=rand()%360;
                        neutroni_liberi[indice].alive=1;
                        neutroni_liberi[indice].unghi=unghi;
                        neutroni_liberi[indice].neutronul.set_position(atomi[j].pozitie);
                        neutroni_liberi[indice].neutronul.viteza.x=cos(unghi*PI/180);
                        neutroni_liberi[indice].neutronul.viteza.y=-sin(unghi*PI/180);
                        neutroni_liberi[indice].indice_viteza=neutroni_liberi[i].indice_viteza;

                        indice=new_neutron();
                        unghi=rand()%360;
                        neutroni_liberi[indice].alive=1;
                        neutroni_liberi[indice].unghi=unghi;
                        neutroni_liberi[indice].neutronul.set_position(atomi[j].pozitie);
                        neutroni_liberi[indice].neutronul.viteza.x=cos(unghi*PI/180);
                        neutroni_liberi[indice].neutronul.viteza.y=-sin(unghi*PI/180);
                        neutroni_liberi[indice].indice_viteza=neutroni_liberi[i].indice_viteza;

                        raza+=raza_atomului;
                        indice=new_explozie();
                        explozii[indice].alive=1;
                        explozii[indice].cooldown=cooldown_explozii;
                        explozii[indice].forma.setOrigin(sf::Vector2f(raza,raza));
                        explozii[indice].forma.setPosition(sf::Vector2f((a1.x+a2.x)/2,(a1.y+a2.y)/2));
                        explozii[indice].forma.setRadius(raza);
                        explozii[indice].forma.setFillColor(sf::Color(255,106,0));


                        neutroni_liberi[i].alive=0;
                        atomi[j].alive=0;


                        break;
                    }
                }

            }
        }
    }
}

void scena_joc::update_explozii()
{
    for (int i=1; i<=numar_explozii; i++)
    {
        if (explozii[i].alive==1)
        {
            explozii[i].cooldown-=1000000/120;
            explozii[i].forma.setFillColor(sf::Color(explozii[i].forma.getFillColor().r,explozii[i].forma.getFillColor().g,explozii[i].forma.getFillColor().b,explozii[i].forma.getFillColor().a-255/120));
            if (explozii[i].cooldown<0)
                explozii[i].alive=0;
        }
    }
}

void scena_joc::draw_explozii()
{
    for (int i=1; i<=numar_explozii; i++)
    {
        if (explozii[i].alive)
        {
            window.draw(explozii[i].forma);
        }
    }
}

int scena_joc::new_atom()
{
    if (numar_atomi==499)
    {
        for (int i=1; i<=numar_atomi; i++)
        {
            if (atomi[i].stabil==1)
                return i;
        }
        cout << "E:prea multi atom\n";
        return rand()%numar_atomi+1;
    }
    for (int i=1; i<=numar_atomi; i++)
    {
        if (atomi[i].alive==0)
            return i;
    }
    numar_atomi++;
    return numar_atomi;
}
int scena_joc::new_neutron()
{
    for (int i=1; i<=numar_neutroni_liberi; i++)
    {
        if (neutroni_liberi[i].alive==0)
            return i;
    }
    numar_neutroni_liberi++;
    return numar_neutroni_liberi;
}
int scena_joc::new_explozie()
{
    for (int i=1; i<=numar_explozii; i++)
    {
        if (explozii[i].alive==0)
            return i;
    }
    numar_explozii++;
    return numar_explozii;
}



