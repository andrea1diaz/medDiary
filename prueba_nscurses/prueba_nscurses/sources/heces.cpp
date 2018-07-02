#include "../headers/heces.h"
#include "../headers/laboratorio.h"
#include <iostream>

using namespace std;

Heces::Heces() {}

Heces::Heces(int _dia,
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
                         double _testGraham):Laboratorio(_dia, _mes, _ano, _doctor, _diagnostico)
{
    coproParasitarioFuncional = _coproParasitarioFuncional;
    coprocultivo = _coprocultivo;
    leucocitos = _leucocitos;
    parasitologicoSimple = _parasitologicoSimple;
    parasitologicoSeriado = _parasitologicoSeriado;
    rotavirus = _rotavirus;
    sustReductoras = _sustReductoras;
    fragilidadGlobular = _fragilidadGlobular;
    thevenon = _thevenon;
    testGraham = _testGraham;

}

void Heces::ImprimirHeces()
{

    cout << "\n";
    cout << "TEST DE HECES\n";
    cout << "Coproparasitario Funcional   : " << coproParasitarioFuncional << "\n";
    cout << "Coprocultivo      : " << coprocultivo << "\n";
    cout << "Leucocitos: " << leucocitos << "\n";
    cout << "Parasitologico Simple    : " << parasitologicoSimple << "\n";
    cout << "parasitologico Seriado     : " << parasitologicoSeriado << "\n";
    cout << "Rotavirus   : " << rotavirus << "\n";
    cout << "Sustancias Reductoras     : " << sustReductoras << "\n";
    cout << "Thevenon   : " << thevenon << "\n";
    cout << "Test de Graham      : " << testGraham << "\n";

