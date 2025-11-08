//
// Created by 27042 on 11/8/2025.
//

#include "Obstacol.h"

Obstacol::Obstacol(int x, int y, int latime, int viteza, int directie, TipObstacol tip)
    : x(x), y(y), latime(latime), viteza(viteza), directie(directie), tip(tip) {}

// Funcție "non-trivială" #1 (completată)
void Obstacol::actualizeaza(int limitaStanga, int limitaDreapta) {
    // 1. Mișcă obstacolul
    this->x += this->viteza * this->directie;

    // 2. Implementează "wrap-around" (mașinile re-apar)
    if (this->directie == 1 && this->x > limitaDreapta + 1) {
        this->x = limitaStanga - this->latime;
    }
    else if (this->directie == -1 && this->x + this->latime < limitaStanga - 1) {
        this->x = limitaDreapta;
    }
}

// Funcție "non-trivială" #2 (detecție coliziune)
bool Obstacol::verificaColiziune(int jucatorX, int jucatorY) const {
    if (jucatorY != this->y) {
        return false; // Nu sunt pe aceeași bandă
    }

    // Verificare coliziune AABB
    return (jucatorX >= this->x) && (jucatorX < (this->x + this->latime));
}

int Obstacol::getX() const { return x; }
int Obstacol::getY() const { return y; }
int Obstacol::getViteza() const { return viteza; }
int Obstacol::getDirectie() const { return directie; }

std::ostream& operator<<(std::ostream& os, const Obstacol& o) {
    os << "  Obstacol (" << (o.tip == TipObstacol::MASINA ? "Masina" : "Bustean")
       << ") la x=" << o.x << " [latime " << o.latime << ", viteza " << (o.viteza * o.directie) << "]";
    return os;
}