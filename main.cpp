
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono> // Pentru pauză
#include <thread> // Pentru pauză
#include "Joc.h"

int main() {
    std::cout << "Start Joc Crossy Road (Simulare din fisier)!\n";

    // --- Creare Obiecte ---
    Joc joc("Gigel");

    // --- Testare "Regula celor 3" (cerință) ---
    std::cout << "\n--- Testare Regula celor 3 ---\n";
    Jucator jTest("Test");
    Jucator jCopie = jTest; // Test Constructor de Copiere
    Jucator jAtrib;
    jAtrib = jTest; // Test Operator=
    std::cout << "Testare Regula celor 3 OK.\n--- Incepe Simularea ---\n";

    // --- Citire din 'tastatura.txt' ---
    std::ifstream fisierInput("tastatura.txt");
    if (!fisierInput.is_open()) {
        std::cerr << "EROARE: Nu am putut deschide 'tastatura.txt'!" << std::endl;
        return 1;
    }

    std::string miscare;

    // Afișează starea inițială
    std::cout << joc;

    // Citește fiecare mișcare din fișier
    while (!joc.esteJoculTerminat() && fisierInput >> miscare) {
        std::cout << "\n>>> Comanda citita: " << miscare << "\n";

        // 1. Procesează inputul
        joc.proceseazaInput(miscare);

        // 2. Actualizează lumea (mașinile se mișcă, coliziunile se verifică)
        joc.actualizeaza();

        // 3. Afișează starea nouă
        std::cout << joc;

        // O mică pauză ca să poți citi ce se întâmplă
        // Comentează linia de mai jos dacă vrei viteză maximă
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    fisierInput.close();

    std::cout << "\n=== Simularea din 'tastatura.txt' s-a terminat ===\n";
    if (joc.esteJoculTerminat()) {
        std::cout << "Jucatorul a murit in timpul simularii.\n";
    } else {
        std::cout << "Jucatorul a supravietuit tuturor comenzilor.\n";
    }

    return 0;
}
