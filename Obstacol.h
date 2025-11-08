//
// Created by 27042 on 11/8/2025.
//

#ifndef OOP_OBSTACOL_H
#define OOP_OBSTACOL_H


#include <iostream>

enum class TipObstacol { MASINA, BUSTEAN };

class Obstacol {
private:
    int x, y, latime;
    int viteza;
    int directie; // -1 (stânga) sau 1 (dreapta)
    TipObstacol tip;

public:
    Obstacol(int x, int y, int latime, int viteza, int directie, TipObstacol tip);

    void actualizeaza(int limitaStanga, int limitaDreapta);
    bool verificaColiziune(int jucatorX, int jucatorY) const;

    // Getteri necesari pentru logica de joc
    int getX() const;
    int getY() const;
    int getViteza() const;
    int getDirectie() const;

    friend std::ostream& operator<<(std::ostream& os, const Obstacol& o);
};


#endif //OOP_OBSTACOL_H