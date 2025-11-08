//
// Created by 27042 on 11/8/2025.
//

#ifndef OOP_BANDA_H
#define OOP_BANDA_H


#include "Obstacol.h"
#include <vector>
#include <random>

enum class TipBanda { SOSEA, RAU, IARBA_SIGURA };
enum class StatusBanda { OK, MORT, PE_BUSTEAN };

class Banda {
private:
    TipBanda tip;
    int y;

    // Compunere
    std::vector<Obstacol> obstacole;

public:
    // Constructorul va crea și obstacolele!
    Banda(TipBanda tip, int y, std::mt19937& generator);

    void actualizeazaBanda(int latimeLume);

    // Funcție "complexă" #1
    StatusBanda verificaColiziuniPeBanda(int jucatorX, int jucatorY) const;

    // Funcție ajutătoare pentru logica buștenilor
    int getVitezaBusteanLa(int jucatorX, int jucatorY) const;

    int getY() const;
    TipBanda getTip() const;

    friend std::ostream& operator<<(std::ostream& os, const Banda& b);
};


#endif //OOP_BANDA_H