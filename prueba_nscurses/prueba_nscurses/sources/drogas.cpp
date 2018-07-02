#include "../headers/drogas.h"
#include "../headers/laboratorio.h"
#include <iostream>

using namespace std;

Drogas::Drogas() {}

Drogas::Drogas(int _dia,
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
                         double _opiaceos):Laboratorio(_dia, _mes, _ano, _doctor, _diagnostico)
{
    acetaminofen = _acetaminofen;
    anfetaminas = _anfetaminas;
    carbamazepina = _carbamazepina;
    diazepan = _diazepan;
    epamin = _epamin;
    litio = _litio;
    toxicScreen = _toxicScreen;
    metanfetaminas = _metanfetaminas;
    cocaina = _cocaina;
    marihuana = _marihuana;
    opiaceos = _opiaceos;
}

void Drogas::ImprimirDrogas()
{

    cout << "\n";
    cout << "TEST DE DROGAS\n";
    cout << "Acetaminofen  : " << acetaminofen << "\n";
    cout << "Anfetaminas      : " << anfetaminas << "\n";
    cout << "Carbamazepina: " << carbamazepina << "\n";
    cout << "Diazepan    : " << diazepan << "\n";
    cout << "Epamin     : " << epamin << "\n";
    cout << "Litio   : " << litio << "\n";
    cout << "Toxic Screen (Resultados)    : " << toxicScreen << "\n";
    cout << "Metanfetaminas    : " << metanfetaminas << "\n";
    cout << "Cocaina   : " << cocaina << "\n";
    cout << "Marihuana      : " << marihuana << "\n";
    cout << "Opiaceos: " << opiaceos << "\n";
}
