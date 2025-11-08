
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Joc.h"

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Crossy Road - Tema 1");
    window.setFramerateLimit(60); // Rulează la 60 FPS

    Joc joc("Gaina");

    sf::Clock gameClock;
    const sf::Time timpPePas = sf::seconds(0.5f);
    sf::Time timpAcumulat = sf::Time::Zero;

    std::cout << "--- START ---" << std::endl;
    std::cout << "Foloseste sagetile pentru a te misca. Inchide fereastra pentru a iesi." << std::endl;
    std::cout << joc;


    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {

                if (joc.esteJoculTerminat()) continue;

                if (event.key.code == sf::Keyboard::Up) {
                    joc.proceseazaInput("SUS");
                    joc.actualizeaza();
                    std::cout << joc;
                } else if (event.key.code == sf::Keyboard::Down) {
                    joc.proceseazaInput("JOS");
                    joc.actualizeaza();
                    std::cout << joc;
                } else if (event.key.code == sf::Keyboard::Left) {
                    joc.proceseazaInput("STANGA");
                    joc.actualizeaza();
                    std::cout << joc;
                } else if (event.key.code == sf::Keyboard::Right) {
                    joc.proceseazaInput("DREAPTA");
                    joc.actualizeaza();
                    std::cout << joc;
                }
            }
        }


        timpAcumulat += gameClock.restart();

        if (timpAcumulat >= timpPePas) {
            if (!joc.esteJoculTerminat()) {
                std::cout << "\n>>> (Tick-ul lumii - masinile se misca)\n";

                joc.actualizeaza();
                std::cout << joc;
            }

            timpAcumulat -= timpPePas;
        }

        window.clear(sf::Color::Black);

        window.display();
    }

    std::cout << "=== Jocul s-a terminat ===\n";
    return 0;
}
