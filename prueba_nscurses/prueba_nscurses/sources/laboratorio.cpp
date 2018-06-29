//
// Created by Andrea Diaz ♡ on 6/8/18.
//

#include "/Users/andreadiaz/projects/medDiary/prueba_nscurses/prueba_nscurses/headers/laboratorio.h"
#include <iostream>

using namespace std;

Laboratorio::Laboratorio() {}


Laboratorio::Laboratorio(int _dia,
                         int _mes,
                         int _ano,
                         string _doctor,
                         string _diagnostico)
{
    dia = _dia;
    mes= _mes;
    ano = _ano;
    doctor = _doctor;
    diagnostico = _diagnostico;

}

void Laboratorio::ImprimirLaboratorio()
{
    cout <<"LABORATORIO" << "\n";
    cout << "Fecha      : " << dia << "/" << mes << "/" << ano << "\n";
    cout << "Doctor     : " << doctor << "\n";
    cout << "Diagnostico: " << diagnostico << "\n";

}
