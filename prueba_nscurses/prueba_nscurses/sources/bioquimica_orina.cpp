//
// Created by Andrea Diaz ♡ on 6/8/18.
//

#include "bioquimica_orina.h"
#include " laboratorio.h"
#include <iostream>

using namespace std;

BioquimicaOrina::BioquimicaOrina() {}

BioquimicaOrina::BioquimicaOrina(int _dia,
                                 int _mes,
                                 int _ano,
                                 string _doctor,
                                 string _diagnostico,
                                 double _glucosaOrina,
                                 double _ureaOrina,
                                 double _creatininaOrina
                                 /*double _amilsaOrina,
                                 double _sodioOrina,
                                 double _potasioOrina,
                                 double _cloroOrina,
                                 double _calcioOrina*/):Laboratorio(_dia, _mes, _ano, _doctor, _diagnostico)
{
    glucosaOrina = _glucosaOrina;
    ureaOrina = _ureaOrina;
    creatininaOrina = _creatininaOrina;
    /*amilsaOrina = _amilsaOrina;
    sodioOrina = _sodioOrina;
    potasioOrina = _potasioOrina;
    cloroOrina = _cloroOrina;
    calcioOrina = _calcioOrina;*/
}

void BioquimicaOrina::ImprimirBioquimicaOrina()
{

    cout << "\n";
    cout << "BIOQUIMICA EN LA ORINA\n";
    cout << "Glucosa   : " << glucosaOrina << "\n";
    cout << "Urea      : " << ureaOrina << "\n";
    cout << "Creatinina: " << creatininaOrina << "\n";
    /*cout << "Amilsa    : " << amilsaOrina << "\n";
    cout << "Sodio     : " << sodioOrina << "\n";
    cout << "Potasio   : " << potasioOrina << "\n";
    cout << "Cloro     : " << cloroOrina << "\n";
    cout << "Calcio    : " << calcioOrina << "\n";*/
}
