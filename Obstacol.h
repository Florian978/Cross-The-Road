
#ifndef OOP_OBSTACOL_H
#define OOP_OBSTACOL_H


#include <iostream>

enum class TipObstacol { MASINA, BUSTEAN };

class Obstacol {
private:
    int x, y, latime;
    int viteza;
    int directie;
    TipObstacol tip;

public:
    Obstacol(int x, int y, int latime, int viteza, int directie, TipObstacol tip);

    void actualizeaza(int limitaStanga, int limitaDreapta);
    bool verificaColiziune(int jucatorX, int jucatorY) const;

    int getX() const;
    int getY() const;
    int getViteza() const;
    int getDirectie() const;

    friend std::ostream& operator<<(std::ostream& os, const Obstacol& o);
};


#endif //OOP_OBSTACOL_H