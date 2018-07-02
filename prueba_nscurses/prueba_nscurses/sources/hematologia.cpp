#include "../headers/hematologia.h"
#include "../headers/laboratorio.h"
#include <iostream>

using namespace std;

Hematologia::Hematologia() {}

Hematologia::Hematologia(int _dia,
                         int _mes,
                         int _ano,
                         string _doctor,
                         string _diagnostico,
                         double _acidoFolicoIntraeritrocitario,
                         double _acidoFolicoSerico,
                         double _anticoagulanteLupico,
                         double _antrombina,
                         double _ferritina,
                         double _fibrinogeno,
                         double _fragilidadCapilar,
                         double _fragilidadGlobular,
                         double _glucosaDehidrogenasa,
                         double _hemoglobinaHematocrito,
                         double _hierroSerico,
                         double _proteinaC,
                         double _proteinaS,
                         double _reticulocitos,
                         double _vitaminaB12,):Laboratorio(_dia, _mes, _ano, _doctor, _diagnostico)
{
    acidoFolicoIntraeritrocitario = _acidoFolicoIntraeritrocitario;
    acidoFolicoSerico = _acidoFolicoSerico;
    anticoagulanteLupico = _anticoagulanteLupico;
    antrombina = _antrombina;
    ferritina = _ferritina;
    fibrinogeno = _fibrinogeno;
    fragilidadCapilar = _fragilidadCapilar;
    fragilidadGlobular = _fragilidadGlobular;
    glucosaDehidrogenasa = _glucosaDehidrogenasa;
    hemoglobinaHematocrito = _hemoglobinaHematocrito;
    hierroSerico = _hierroSerico;
    proteinaC = _proteinaC;
    proteinaS = _proteinaS;
    reticulocitos = _reticulocitos;
    vitaminaB12 = _vitaminaB12;
}

void Hematologia::ImprimirHematologia()
{

    cout << "\n";
    cout << "HEMATOLOGIA\n";
    cout << "Acido Folico Intraeritrocitario   : " << acidoFolicoIntraeritrocitario << "\n";
    cout << "Acido Folico Serico      : " << acidoFolicoSerico << "\n";
    cout << "Anti Coagulante Lupico: " << anticoagulanteLupico << "\n";
    cout << "Antrombina    : " << antrombina << "\n";
    cout << "Ferritina     : " << ferritina << "\n";
    cout << "Fibrinogeno   : " << fibrinogeno << "\n";
    cout << "Fragilidad Capilar     : " << fragilidadCapilar << "\n";
    cout << "Fragilidad Globular    : " << fragilidadGlobular << "\n";
    cout << "Glucosa Dehidrogenasa   : " << glucosaDehidrogenasa << "\n";
    cout << "Hematocrito de Hemoglobina      : " << hemoglobinaHematocrito << "\n";
    cout << "Hierro Serico: " << hierroSerico << "\n";
    cout << "Proteina C    : " << proteinaC << "\n";
    cout << "Proteina S     : " << proteinaS << "\n";
    cout << "Reticulocitos   : " << reticulocitos << "\n";
    cout << "Vitamina B12     : " << vitaminaB12 << "\n";
}
