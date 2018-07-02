//
// Created by nano on 29/06/18.
//

#ifndef P1_BIOQUIMICA_H
#define P1_BIOQUIMICA_H
#include "laboratorio.h"
#include <string>


using namespace std;


class Drogas:public Laboratorio {
private:
    double acetaminofen;
    double anfetaminas;
    double carbamazepina;
    double diazepan;
    double epamin;
    double litio;
    double toxicScreen;
    double metanfetaminas;
    double cocaina;
    double marihuana;
    double opiaceos;


public:
    //--- metodos de acceso
    Drogas();

    Drogas( int _dia,
                 int _mes,
                 int _ano,
                 string _doctor,
                 string _diagnostico,
                 double _acetaminofen,
                 double _anfetaminas,
                 double _carbamazepina,
                 double _diazepan,
                 double _epamin,
                 double _litio,
                 double _toxicScreen,
                 double _metanfetaminas,
                 double _cocaina,
                 double _marihuana,
                 double _opiaceos);


    //--- setters
    void setAcetaminofen(double _acetaminofen) { acetaminofen = _acetaminofen;}
    void setAnfetaminas(double _anfetaminas) { anfetaminas = _anfetaminas;}
    void setCarbamazepina(double _carbamazepina) { carbamazepina = _carbamazepina;}
    void setDiazepan(double _diazepan) { diazepan = _diazepan ;}
    void setEpamin(double _epamin) { epamin = _epamin;}
    void setLitio(double _litio) { litio = _litio;}
    void setToxicScreen(double _toxicScreen) { toxicScreen = _toxicScreen;}
    void setMetanfetaminas(double _metanfetaminas) { metanfetaminas = _metanfetaminas;}
    void setCocaina(double _cocaina) { cocaina = _cocaina;}
    void setMarihuana(double _marihuana) { marihuana = _marihuana;}
    void setOpiaceos(double _opiaceos) { opiaceos = _opiaceos;}


    //--getters
    double getAcetaminofen() { return acetaminofen;}
    double getAnfetaminas() { return anfetaminas;}
    double getCarbamazepina() { return carbamazepina;}
    double getDiazepan() { return diazepan;}
    double getEpamin() { return epamin;}
    double getLitio() { return litio;}
    double getToxicScreen() { return toxicScreen;}
    double getMetanfetaminas() { return metanfetaminas;}
    double getCocaina() { return cocaina;}
    double getMarihuana() { return marihuana;}
    double getOpiaceos() { return opiaceos;}


    void ImprimirDrogas();

};
