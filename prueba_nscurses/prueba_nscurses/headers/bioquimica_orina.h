//
// Created by Andrea Diaz ♡ on 6/8/18.
//

#ifndef P1_BIOQUIMICA_ORINA_H
#define P1_BIOQUIMICA_ORINA_H

#include "laboratorio.h"

using namespace std;


class BioquimicaOrina:public Laboratorio {
private:
    double glucosaOrina;
    double ureaOrina;
    double creatininaOrina;
    double amilsaOrina;
    double sodioOrina;
    double potasioOrina;
    double cloroOrina;
    double calcioOrina;

public:
    BioquimicaOrina();

    BioquimicaOrina(
            int _dia,
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
            double _calcioOrina*/);

    //--- setters
    void setGlucosaOrina(double _glucosaOrina) { glucosaOrina = _glucosaOrina; }
    void setUreaOrina(double _ureaOrina) { ureaOrina = _ureaOrina; }
    void setCreatininaOrina(double _creatininaOrina) { creatininaOrina = _creatininaOrina; }
    /*void setAmilsaOrina(double _amilsaOrina) { amilsaOrina = _amilsaOrina; }
    void setSodioOrina(double _sodioOrina) { sodioOrina = _sodioOrina; }
    void setPotasioOrina(double _potasioOrina) { potasioOrina = _potasioOrina; }
    void setCloroOrina(double _cloroOrina) { cloroOrina = _cloroOrina; }
    void setCalcioOrina(double _calcioOrina) { calcioOrina = _calcioOrina; }*/

    //--- getters
    double getGlucosaOrina() { return glucosaOrina; }
    double getUreaOrina() { return ureaOrina; }
    double getCreatininaOrina() { return creatininaOrina; }
    /*double getAmilsaOrina() { return amilsaOrina; }
    double getSodioOrina() { return sodioOrina; }
    double getPotasioOrina() { return potasioOrina; }
    double getCloroOrina() { return cloroOrina; }
    double getCalcioOrina() { return calcioOrina; }*/

    void ImprimirBioquimicaOrina();

};


#endif //P1_BIOQUIMICA_ORINA_H
