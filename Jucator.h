//
// Created by 27042 on 11/8/2025.
//

#ifndef OOP_JUCATOR_H
#define OOP_JUCATOR_H


#include <iostream>

class Jucator {
private:
    char* nume;
    int x, y;
    int scor;
    bool esteMort;

    void copieazaNume(const char* altNume);

public:
    Jucator(const char* nume = "Jucator1", int xStart = 0, int yStart = 0);

    // --- Regula celor 3 ---
    ~Jucator();
    Jucator(const Jucator& altul);
    Jucator& operator=(const Jucator& altul);
    // --- Sfârșit Regula celor 3 ---

    // Acțiuni
    void muta(int deltaX, int deltaY, int limitaStanga, int limitaDreapta);
    void deplaseazaFortat(int deltaX); // Mișcare pasivă (pe buștean)
    void moare();
    void reseteaza();

    // Getteri const
    int getScor() const;
    int getX() const;
    int getY() const;
    bool eMort() const;

    friend std::ostream& operator<<(std::ostream& os, const Jucator& j);
};


#endif //OOP_JUCATOR_H