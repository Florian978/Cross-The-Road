
#ifndef OOP_JOC_H
#define OOP_JOC_H


#include "Jucator.h"
#include "Banda.h"
#include <vector>
#include <string>
#include <random>

class Joc {
private:
    Jucator jucator;
    std::vector<Banda> harti;
    int scorMaxim;
    int latimeLume;
    int limitaStanga;

    std::mt19937 generatorRandom;

    void genereazaBandaNoua();

public:
    Joc(const char* numeJucator);

    // Funcția "cea mai complexă"
    void actualizeaza();

    void proceseazaInput(const std::string& miscare);

    bool esteJoculTerminat() const;

    friend std::ostream& operator<<(std::ostream& os, const Joc& j);
};


#endif //OOP_JOC_H