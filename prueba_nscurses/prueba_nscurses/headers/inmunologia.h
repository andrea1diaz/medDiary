//
// Created by nano on 29/06/18.
//

#ifndef P1_BIOQUIMICA_H
#define P1_BIOQUIMICA_H
#include "laboratorio.h"
#include <string>


using namespace std;


class Inmunologia:public Laboratorio {
private:
    double amebaHistolitica;
    double herpes;
    double micoplasmaPneumonial;
    double rubeola;
    double sarampion;
    double toxoplasma;
    double varicela;
    double antiCardioPilina;
    double epstein;
    double brucelosis;
    double helicobacter;
    double VIH;


public:
    //--- metodos de acceso
    Inmunologia();

    Inmunologia( int _dia,
                 int _mes,
                 int _ano,
                 string _doctor,
                 string _diagnostico,
                 double _amebaHistolitica,
                 double _herpes,
                 double _micoplasmaPneumonial,
                 double _rubeola,
                 double _sarampion,
                 double _toxoplasma,
                 double _varicela,
                 double _antiCardioPilina,
                 double _epstein,
                 double _brucelosis,
                 double _helicobacter,
                 double _VIH);


            //--- setters
            void setAmebaHistolitica(double _amebaHistolitica) { amebaHistolitica = _amebaHistolitica;}
    void setHerpes(double _herpes) { herpes = _herpes;}
    void setMicoplasmaPneumonial(double _micoplasmaPneumonial) { micoplasmaPneumonial = _micoplasmaPneumonial;}
    void setRubeola(double _rubeola) { rubeola = _rubeola ;}
    void setSarampion(double _sarampion) { sarampion = _sarampion;}
    void setToxoplasma(double _toxoplasma) { toxoplasma = _toxoplasma;}
    void setVaricela(double _varicela) { varicela = _varicela;}
    void setAntiCardioPilina(double _antiCardioPilina) { antiCardioPilina = _antiCardioPilina;}
    void setEpstein(double _epstein) { epstein = _epstein;}
    void setBrucelosis(double _brucelosis) { brucelosis = _brucelosis;}
    void setHelicobacter(double _helicobacter) { helicobacter = _helicobacter;}
    void setVIH(double _VIH) { VIH = _VIH;}


    //--getters
    double getAmebaHistolitica() { return amebaHistolitica;}
    double getHerpes() { return herpes;}
    double getMicoplasmaPneumonial() { return micoplasmaPneumonial;}
    double getRubeola() { return rubeola;}
    double getSarampion() { return sarampion;}
    double getToxoplasma() { return toxoplasma;}
    double getVaricela() { return varicela;}
    double getAntiCardioPilina() { return antiCardioPilina;}
    double getEpstein() { return epstein;}
    double getBrucelosis() { return brucelosis;}
    double getHelicobacter() { return helicobacter;}
    double getVIH() { return VIH;}


    void ImprimirInmunologia();

};
