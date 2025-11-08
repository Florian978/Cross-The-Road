#include "Jucator.h"
#include <cstring> // Pentru strlen și strcpy

// --- Implementare Funcție Privată ---
void Jucator::copieazaNume(const char* altNume) {
    delete[] this->nume;
    if (altNume) {
        this->nume = new char[std::strlen(altNume) + 1];
        std::strcpy(this->nume, altNume);
    } else {
        this->nume = nullptr;
    }
}

// --- Implementare Publică ---
Jucator::Jucator(const char* nume, int xStart, int yStart)
    : nume(nullptr), x(xStart), y(yStart), scor(0), esteMort(false) { // FIX: Reordonat
    copieazaNume(nume);
}

// 1. Destructor
Jucator::~Jucator() {
    delete[] this->nume;
}

// 2. Constructor de copiere
Jucator::Jucator(const Jucator& altul)
    : nume(nullptr), x(altul.x), y(altul.y), scor(altul.scor), esteMort(altul.esteMort) { // FIX: Reordonat
    copieazaNume(altul.nume);
}

// 3. Operator de atribuire
Jucator& Jucator::operator=(const Jucator& altul) {
    if (this != &altul) {
        this->x = altul.x;
        this->y = altul.y;
        this->scor = altul.scor;
        this->esteMort = altul.esteMort;
        copieazaNume(altul.nume);
    }
    return *this;
}

// --- Acțiuni ---
void Jucator::muta(int deltaX, int deltaY, int limitaStanga, int limitaDreapta) {
    if (esteMort) return;

    int xNou = this->x + deltaX;
    int yNou = this->y + deltaY;

    // Verifică limitele laterale
    if (xNou < limitaStanga || xNou > limitaDreapta) {
        return; // Nu se mișcă
    }

    this->x = xNou;
    this->y = yNou;

    // Actualizează scorul doar la mișcarea "SUS"
    if (deltaY > 0 && this->y > this->scor) {
        this->scor = this->y;
    }
    std::cout << "Jucatorul s-a mutat la (" << this->x << ", " << this->y << ")\n";
}

void Jucator::deplaseazaFortat(int deltaX) {
    if (esteMort) return;
    this->x += deltaX;
}

void Jucator::moare() {
    if (esteMort) return; // Să nu moară de două ori
    std::cout << "-------------------------------------------\n";
    std::cout << "Jucatorul " << (nume ? nume : "") << " a murit! Scor final: " << scor << "\n";
    std::cout << "-------------------------------------------\n";
    this->esteMort = true;
}

// cppcheck-suppress unusedFunction
void Jucator::reseteaza() {
    this->x = 0;
    this->y = 0;
    this->scor = 0;
    this->esteMort = false;
}

// --- Getteri ---
int Jucator::getScor() const { return scor; }
int Jucator::getX() const { return x; }
int Jucator::getY() const { return y; }
bool Jucator::eMort() const { return esteMort; }

// --- Operator de afișare ---
std::ostream& operator<<(std::ostream& os, const Jucator& j) {
    os << "Jucator '" << (j.nume ? j.nume : "N/A") << "' la pozitia (" << j.x << ", " << j.y << ") | Scor: " << j.scor;
    if (j.esteMort) {
        os << " [MORT]";
    }
    return os;
}