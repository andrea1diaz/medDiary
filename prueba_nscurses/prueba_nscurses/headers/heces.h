//
// Created by nano on 29/06/18.
//

#ifndef P1_BIOQUIMICA_H
#define P1_BIOQUIMICA_H
#include "laboratorio.h"
#include <string>


using namespace std;


class Heces:public Laboratorio {
private:
    double coproParasitarioFuncional;
    double coprocultivo;
    double leucocitos;
    double parasitologicoSimple;
    double parasitologicoSeriado;
    double rotavirus;
    double sustReductoras;
    double fragilidadGlobular;
    double thevenon;
    double testGraham;


public:
    //--- metodos de acceso
    Heces();

    Heces( int _dia,
                 int _mes,
                 int _ano,
                 string _doctor,
                 string _diagnostico,
                 double _coproParasitarioFuncional,
                 double _coprocultivo,
                 double _leucocitos,
                 double _parasitologicoSimple,
                 double _parasitologicoSeriado,
                 double _rotavirus,
                 double _sustReductoras,
                 double _fragilidadGlobular,
                 double _thevenon,
                 double _testGraham);



            //--- setters
             void setcoproParasitarioFuncional(double _coproParasitarioFuncional) { coproParasitarioFuncional = _coproParasitarioFuncional;}
    void setCoprocultivo(double _coprocultivo) { coprocultivo = _coprocultivo;}
    void setLeucocitos(double _leucocitos) { leucocitos = _leucocitos;}
    void setParasitologicoSimple(double _parasitologicoSimple) { parasitologicoSimple = _parasitologicoSimple ;}
    void setParasitologicoSeriado(double _parasitologicoSeriado) { parasitologicoSeriado = _parasitologicoSeriado;}
    void setRotavirus(double _rotavirus) { rotavirus = _rotavirus;}
    void setSustReductoras(double _sustReductoras) { sustReductoras = _sustReductoras;}
    void setThevenon(double _thevenon) { thevenon = _thevenon;}
    void setTestGraham(double _testGraham) { testGraham = _testGraham;}



    //--getters
    double getCoproParasitarioFuncional() { return coproParasitarioFuncional;}
    double getCoprocultivo() { return coprocultivo;}
    double getLeucocitos() { return leucocitos;}
    double getParasitologicoSimple() { return parasitologicoSimple;}
    double getParasitologicoSeriado() { return parasitologicoSeriado;}
    double getRotavirus() { return rotavirus;}
    double getSustReductoras() { return sustReductoras;}
    double getThevenon() { return thevenon;}
    double getTestGraham() { return testGraham;}



    void ImprimirHeces();

};