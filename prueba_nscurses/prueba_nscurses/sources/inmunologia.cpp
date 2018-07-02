#include "../headers/inmunologia.h"
#include "../headers/laboratorio.h"
#include <iostream>

using namespace std;

Inmunologia::Inmunologia() {}

Inmunologia::Inmunologia(int _dia,
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
                         double _VIH):Laboratorio(_dia, _mes, _ano, _doctor, _diagnostico)
{
    amebaHistolitica = _amebaHistolitica;
    herpes = _herpes;
    micoplasmaPneumonial = _micoplasmaPneumonial;
    rubeola = _rubeola;
    sarampion = _sarampion;
    toxoplasma = _toxoplasma;
    varicela = _varicela;
    antiCardioPilina = _antiCardioPilina;
    epstein = _epstein;
    brucelosis = _brucelosis;
    helicobacter = _helicobacter;
    VIH = _VIH;
}

void Inmunologia::ImprimirInmunologia()
{

    cout << "\n";
    cout << "INMUNOLOGIA\n";
    cout << "Ameba Histolitica   : " << amebaHistolitica << "\n";
    cout << "Herpes      : " << herpes << "\n";
    cout << "Micoplasma Pneumonial: " << micoplasmaPneumonial << "\n";
    cout << "Rubeola    : " << rubeola << "\n";
    cout << "Sarampion     : " << sarampion << "\n";
    cout << "Toxoplasma   : " << toxoplasma << "\n";
    cout << "Varicela     : " << varicela << "\n";
    cout << "Anti-Cardio Pilina    : " << antiCardioPilina << "\n";
    cout << "Epstein   : " << epstein << "\n";
    cout << "Brucelosis      : " << brucelosis << "\n";
    cout << "Helicobacter: " << helicobacter << "\n";
    cout << "VIH    : " << VIH << "\n";
}
