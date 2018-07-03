//
// Created by nano on 29/06/18.
//

#ifndef P1_BIOQUIMICA_H
#define P1_BIOQUIMICA_H
#include "laboratorio.h"
#include <string>

using namespace std;

class Hematologia:public Laboratorio {
private:
    double acidoFolicoIntraeritrocitario;
    double acidoFolicoSerico;
    double anticoagulanteLupico;
    double antrombina;
    double ferritina;
    double fibrinogeno;
    double fragilidadCapilar;
    double fragilidadGlobular;
    double glucosaDehidrogenasa;
    double hemoglobinaHematocrito;
    double hierroSerico;
    double proteinaC;
    double proteinaS;
    double reticulocitos;
    double vitaminaB12;

public:
    //--- metodos de acceso
    Hematologia();

    Hematologia( int _dia,
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
                double _vitaminaB12);

    //--- setters
    void setAcidoFolicoIntraeritrocitario(double _acidoFolicoIntraeritrocitario) { acidoFolicoIntraeritrocitario = _acidoFolicoIntraeritrocitario;}
    void setAcidoFolicoSerico(double _acidoFolicoSerico) { acidoFolicoSerico = _acidoFolicoSerico;}
    void setAnticoagulanteLupico(double _anticoagulanteLupico) { anticoagulanteLupico = _anticoagulanteLupico;}
    void setAntrombina(double _antrombina) { antrombina = _antrombina ;}
    void setFerritina(double _ferritina) { ferritina = _ferritina;}
    void setFibrinogeno(double _fibrinogeno) { fibrinogeno = _fibrinogeno;}
    void setFragilidadCapilar(double _fragilidadCapilar) { fragilidadCapilar = _fragilidadCapilar;}
    void setFragilidadGlobular(double _fragilidadGlobular) { fragilidadGlobular = _fragilidadGlobular;}
    void setGlucosaDehidrogenasa(double _glucosaDehidrogenasa) { glucosaDehidrogenasa = _glucosaDehidrogenasa;}
    void setHemoglobinaHematocrito(double _hemoglobinaHematocrito) { hemoglobinaHematocrito = _hemoglobinaHematocrito;}
    void setHierroSerico(double _hierroSerico) { hierroSerico = _hierroSerico;}
    void setProteinaC(double _proteinaC) { proteinaC = _proteinaC;}
    void setProteinaS(double _proteinaS) { proteinaS = _proteinaS;}
    void setReticulocitos(double _reticulocitos) { reticulocitos = _reticulocitos;}
    void setVitaminaB12(double _vitaminaB12) { vitaminaB12 = _vitaminaB12;}

    //--getters
    double getAcidoFolicoIntraeritrocitario() { return acidoFolicoIntraeritrocitario;}
    double getAcidoFolicoSerico() { return acidoFolicoSerico;}
    double getAnticoagulanteLupico() { return anticoagulanteLupico;}
    double getAntrombina() { return antrombina;}
    double getFerritina() { return ferritina;}
    double getFibrinogeno() { return fibrinogeno;}
    double getFragilidadCapilar() { return fragilidadCapilar;}
    double getFragilidadGlobular() { return fragilidadGlobular;}
    double getGlucosaDehidrogenasa() { return glucosaDehidrogenasa;}
    double getHemoglobinaHematocrito() { return hemoglobinaHematocrito;}
    double getHierroSerico() { return hierroSerico;}
    double getProteinaC() { return proteinaC;}
    double getProteinaS() { return proteinaS;}
    double getReticulocitos() { return reticulocitos;}
    double getVitaminaB12() { return vitaminaB12;}

    void ImprimirHematologia();

};
