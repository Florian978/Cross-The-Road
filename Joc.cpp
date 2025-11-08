#include "Joc.h"
#include <iostream>
#include <algorithm> // Pentru std::max/min

Joc::Joc(const char* numeJucator)
    : jucator(numeJucator, 15, 0),
      scorMaxim(0),
      latimeLume(30),
      limitaStanga(0),
      generatorRandom(std::random_device{}())
{
    // Inițializează lumea cu 5 benzi sigure
    for (int i = 0; i < 5; ++i) {
        harti.push_back(Banda(TipBanda::IARBA_SIGURA, i, generatorRandom));
    }
    scorMaxim = 4;
    genereazaBandaNoua();
}

void Joc::genereazaBandaNoua() {
    std::uniform_int_distribution<> distTip(0, 2);
    int yNou = harti.back().getY() + 1;

    TipBanda tipNou;
    int tipIndex = distTip(generatorRandom);

    switch (tipIndex) {
        case 0: tipNou = TipBanda::SOSEA; break;
        case 1: tipNou = TipBanda::RAU; break;
        default: tipNou = TipBanda::IARBA_SIGURA; break;
    }

    if (tipNou == TipBanda::RAU && harti.size() >= 2) {
        if (harti[harti.size()-1].getTip() == TipBanda::RAU &&
            harti[harti.size()-2].getTip() == TipBanda::RAU) {
            tipNou = TipBanda::IARBA_SIGURA;
        }
    }

    harti.push_back(Banda(tipNou, yNou, generatorRandom));
}

void Joc::actualizeaza() {
    if (jucator.eMort()) return;

    // --- 1. Logica Buștenilor (Mișcarea pasivă) ---
    int yJucator = jucator.getY();
    if (yJucator >= 0 && yJucator < (int)harti.size()) { // FIX: (int)
        Banda& bandaCurenta = harti[yJucator];

        if (bandaCurenta.getTip() == TipBanda::RAU) {
            int vitezaBustean = bandaCurenta.getVitezaBusteanLa(jucator.getX(), yJucator);
            if (vitezaBustean != 0) {
                jucator.deplaseazaFortat(vitezaBustean);
            }
        }
    }

    // --- 2. Mișcarea Lumii (Obstacolele) ---
    for (auto& banda : harti) {
        banda.actualizeazaBanda(latimeLume);
    }

    // --- 3. Verificarea Coliziunilor (După mișcare) ---
    yJucator = jucator.getY();
    int xJucator = jucator.getX();

    // Verifică ieșirea din lume
    if (yJucator < 0 || yJucator >= (int)harti.size() || // FIX: (int)
        xJucator < limitaStanga - 2 || xJucator > latimeLume + 2) {
        std::cout << "Jucatorul a iesit din lume!\n";
        jucator.moare();
        return;
    }

    Banda& bandaFinala = harti[yJucator];
    StatusBanda status = bandaFinala.verificaColiziuniPeBanda(xJucator, yJucator);

    if (status == StatusBanda::MORT) {
        jucator.moare();
    }

    // --- 4. Generarea Hărții ---
    while (jucator.getScor() + 5 > (int)harti.size()) { // FIX: (int)
        genereazaBandaNoua();
    }
}

// cppcheck-suppress unusedFunction
void Joc::proceseazaInput(const std::string& miscare) {
    if (jucator.eMort()) return;

    if (miscare == "SUS") {
        jucator.muta(0, 1, limitaStanga, latimeLume);
    } else if (miscare == "JOS") {
        jucator.muta(0, -1, limitaStanga, latimeLume);
    } else if (miscare == "STANGA") {
        jucator.muta(-1, 0, limitaStanga, latimeLume);
    } else if (miscare == "DREAPTA") {
        jucator.muta(1, 0, limitaStanga, latimeLume);
    } else if (miscare == "ASTEAPTA") {
        // Nu face nimic, doar lasă lumea să se miște (în noul main)
    }
}

// cppcheck-suppress unusedFunction
bool Joc::esteJoculTerminat() const {
    return jucator.eMort();
}

std::ostream& operator<<(std::ostream& os, const Joc& j) {
    os << "\n=================== Stare Joc ===================\n";
    os << j.jucator << "\n";
    os << "--------------------- Harta ---------------------\n";

    int yStart = std::max(0, j.jucator.getY() - 3);
    int yEnd = std::min((int)j.harti.size(), j.jucator.getY() + 8); // FIX: (int)

    for (int i = yStart; i < yEnd; ++i) {
        os << ((i == j.jucator.getY()) ? ">> " : "   ");
        os << j.harti[i];
    }
    os << "=================================================\n";
    return os;
}