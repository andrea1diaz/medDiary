//
// Created by Andrea Diaz ♡ on 6/8/18.
//

#ifndef P1_LABORATORIO_H
#define P1_LABORATORIO_H

#include <string>
#include <iostream>

using namespace std;

class Laboratorio {
protected:
    int dia;
    int mes;
    int ano;
    string doctor;
    string diagnostico;

public:
    Laboratorio();

    Laboratorio(int _dia,
                int _mes,
                int _ano,
                string _doctor,
                string _diagnostico);

    //--- setters
    void setDia(int _dia) { dia =_dia; }
    void setMes(int _mes) { mes = _mes; }
    void setAno(int _ano) { ano = _ano; }
    void setDoctor(string _doctor) { doctor = _doctor; }
    void setDiagnostico(string _diagnostico) { diagnostico = _diagnostico; }

    //--- getters
    int getDia() { return dia; }
    int getMes() { return mes; }
    int getAno() { return ano; }
    string getDoctor() { return doctor; }
    string getDiagnostico() { return diagnostico; }

    void ImprimirLaboratorio();

};


#endif //P1_LABORATORIO_H
