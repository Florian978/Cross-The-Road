
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

    std::vector<Obstacol> obstacole;

public:

    Banda(TipBanda tip, int y, std::mt19937& generator);

    void actualizeazaBanda(int latimeLume);

    StatusBanda verificaColiziuniPeBanda(int jucatorX, int jucatorY) const;

    int getVitezaBusteanLa(int jucatorX, int jucatorY) const;

    int getY() const;
    TipBanda getTip() const;

    friend std::ostream& operator<<(std::ostream& os, const Banda& b);
};


#endif //OOP_BANDA_H