//
// Created by Andrea Diaz ♡ on 6/5/18.
//

#ifndef P1_BIOQUIMICA_H
#define P1_BIOQUIMICA_H
#include "laboratorio.h"
#include <string>
class Laboratorio;

using namespace std;


class Bioquimica:public Laboratorio {
private:
    double acidoUrico;
    double ADA;
    double glucosa;
    double urea;
    double creatinina;
    double bilirubinaTotal;
    double bilirubinaDirecta;
    double sodio;
    double potasio;
    double calcio;
    double cloro;
    double amilasa;
    double creatinaCinasa;
    double CKMB;
    double troponinaT;
    double lactatoDeshidrogenasa;
    double lipasa;
    double colinesterasa;
    double amonio;
    double lactato;
    double osmolaridad;
    double urato;
    double magnesio;
    double procalcitonina;
    double proteinasTotales;
    double proteinaCReactiva;
    double etanol;

public:
    //--- metodos de acceso
    Bioquimica();

    Bioquimica( int _dia,
                int _mes,
                int _ano,
                string _doctor,
                string _diagnostico,
                double _acidoUrico,
                double _ADA,
                double _glucosa,
                double _urea,
                double _creatinina,
                double _bilirubinaTotal,
                double _bilirubinaDirecta,
                double _sodio,
                double _potasio,
                double _calcio,
                double _cloro,
                double _amilasa,
                double _creatinaCinasa,
                double _CKMB,
                double _troponinaT,
                double _lactatoDeshidrogenasa,
                double _lipasa,
                double _colinesterasa,
                double _amonio,
                double _lactato,
                double _osmolaridad,
                double _urato,
                double _magnesio,
                double _procalcitonina,
                double _proteinasTotales,
                double _proteinaCReactiva,
                double _etanol);
    

    //--- setters
    void setAcidoUrico(double _acidoUrico) { acidoUrico =_acidoUrico; }
    void setADA(double)
    void setGlucosa(double _glucosa) { glucosa = _glucosa;}
    void setUrea(double _urea) { urea = _urea;}
    void setCreatinina(double _creatinina) { creatinina = _creatinina ;}
    void setBilirubinaTotal(double _bilirubinaTotal) { bilirubinaTotal = _bilirubinaTotal;}
    void setBilirubinaDirecta(double _bilirubinaDirecta) { bilirubinaDirecta = _bilirubinaDirecta;}
    void setSodio(double _sodio) { sodio = _sodio;}
    void setPotasio(double _potasio) { potasio = _potasio;}
    void setCalcio(double _calcio) { calcio = _calcio;}
    void setCloro(double _cloro) { cloro = _cloro;}
    void setAmilasa(double _amilasa) { amilasa = _amilasa;}
    void setCreatinaCinasa(double _creatinaCinasa) { creatinaCinasa = _creatinaCinasa;}
    void setCKMB(double _CKMB) { CKMB = _CKMB;}
    void setTroponinaT(double _troponinaT) { troponinaT = _troponinaT;}
    void setLactatoDeshidrogenasa(double _lactatoDeshidrogenasa) { lactatoDeshidrogenasa = _lactatoDeshidrogenasa;}
    void setLipasa(double _lipasa) { lipasa = _lipasa;}
    void setColinesterasa(double _colinesterasa) { colinesterasa = _colinesterasa;}
    void setAmonio(double _amonio) { amonio = _amonio;}
    void setLactato(double _lactato) { lactato = _lactato;}
    void setOsmolaridad(double _osmolaridad) { osmolaridad = _osmolaridad;}
    void setUrato(double _urato) { urato = _urato;}
    void setMagnesio(double _magnesio) { magnesio = _magnesio;}
    void setProcalcitonina(double _procalcitonina) { procalcitonina = _procalcitonina;}
    void setProteinasTotales(double _proteinasTotales) { proteinasTotales = _proteinasTotales; }
    void setProteinaCReactiva(double _proteinaCReactiva) { proteinaCReactiva = _proteinaCReactiva;}
    void setEtanol(double _etanol) { etanol = _etanol;}

    //--getters
    double getAcidoUrico() { return acidoUrico;}
    double getGlucosa() { return glucosa;}
    double getUrea() { return urea;}
    double getCreatinina() { return creatinina;}
    double getBilirubinaTotal() { return bilirubinaTotal;}
    double getBilirubinaDirecta() { return bilirubinaDirecta;}
    double getSodio() { return sodio;}
    double getPotasio() { return potasio;}
    double getCalcio() { return calcio;}
    double getCloro() { return cloro;}
    double getAmilasa() { return amilasa;}
    double getCreatinaCinasa() { return creatinaCinasa;}
    double getCKMB() { return CKMB;}
    double getTroponinaT() { return troponinaT;}
    double getLactatoDeshidrogenasa() { return lactatoDeshidrogenasa;}
    double getLipasa() { return lipasa;}
    double getColinesterasa() { return colinesterasa;}
    double getAmonio() { return amonio;}
    double getLactato() { return lactato;}
    double getOsmolaridad() { return osmolaridad;}
    double getUrato() { return urato;}
    double getMagnesio() { return magnesio;}
    double getProcalcitonina() { return procalcitonina;}
    double getProteinasTotales() { return proteinasTotales;}
    double getProteinaCReactiva() { return proteinaCReactiva;}
    double getEtanol() { return etanol;}

    void ImprimirBioquimica();

};


#endif //P1_BIOQUIMICA_H
*/
