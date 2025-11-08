//
// Created by 27042 on 11/8/2025.
//

#include "Banda.h"

Banda::Banda(TipBanda tip, int y, std::mt19937& generator) : tip(tip), y(y) {

    std::uniform_int_distribution<> distViteza(1, 3);
    std::uniform_int_distribution<> distLatimeMasina(2, 4);
    std::uniform_int_distribution<> distLatimeBustean(3, 6);
    std::uniform_int_distribution<> distNumar(2, 4);
    std::uniform_int_distribution<> distDirectie(0, 1);
    std::uniform_int_distribution<> distPoz(0, 20);

    int directie = (distDirectie(generator) == 0) ? -1 : 1;
    int viteza = distViteza(generator);
    int nrObstacole = distNumar(generator);
    int pozCurenta = 0;

    for (int i = 0; i < nrObstacole; ++i) {
        pozCurenta += distPoz(generator) + 5; // Spațiu între
        if (tip == TipBanda::SOSEA) {
            obstacole.push_back(Obstacol(pozCurenta, y, distLatimeMasina(generator), viteza, directie, TipObstacol::MASINA));
        } else if (tip == TipBanda::RAU) {
            obstacole.push_back(Obstacol(pozCurenta, y, distLatimeBustean(generator), viteza, directie, TipObstacol::BUSTEAN));
        }
    }
}

void Banda::actualizeazaBanda(int latimeLume) {
    for (auto& obs : obstacole) {
        obs.actualizeaza(-10, latimeLume + 10); // Limite extinse pentru wrap-around
    }
}


StatusBanda Banda::verificaColiziuniPeBanda(int jucatorX, int jucatorY) const {
    if (jucatorY != this->y) return StatusBanda::OK;

    switch (this->tip) {
        case TipBanda::IARBA_SIGURA:
            return StatusBanda::OK;

        case TipBanda::SOSEA:
            for (const auto& obs : obstacole) {
                if (obs.verificaColiziune(jucatorX, jucatorY)) {
                    return StatusBanda::MORT; // Lovit de mașină
                }
            }
            return StatusBanda::OK; // Pe șosea, dar în siguranță

        case TipBanda::RAU:
            for (const auto& obs : obstacole) {
                if (obs.verificaColiziune(jucatorX, jucatorY)) {
                    return StatusBanda::PE_BUSTEAN; // Pe buștean
                }
            }
            return StatusBanda::MORT; // Căzut în apă
    }
    return StatusBanda::OK;
}

int Banda::getVitezaBusteanLa(int jucatorX, int jucatorY) const {
    if (this->tip != TipBanda::RAU || jucatorY != this->y) {
        return 0;
    }
    for (const auto& obs : obstacole) {
        if (obs.verificaColiziune(jucatorX, jucatorY)) {
            return obs.getViteza() * obs.getDirectie();
        }
    }
    return 0;
}

int Banda::getY() const { return y; }
TipBanda Banda::getTip() const { return tip; }

std::ostream& operator<<(std::ostream& os, const Banda& b) {
    const char* numeTip;
    switch (b.tip) {
        case TipBanda::SOSEA: numeTip = "Sosea"; break;
        case TipBanda::RAU: numeTip = "Rau  "; break;
        case TipBanda::IARBA_SIGURA: numeTip = "Iarba"; break;
    }

    os << "Banda Y=" << b.y << " [" << numeTip << "]";

    if (b.obstacole.empty()) {
        os << " (goala)\n";
    } else {
        os << "\n";
        for (const auto& obs : b.obstacole) {
            os << "\t" << obs << "\n";
        }
    }
    return os;
}