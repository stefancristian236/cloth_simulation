#include <SFML/Graphics.hpp>

const double WIDTH = 100.0f;
const double HEIGHT = 300.0f;
const double PARTICLE_RADIUS = 50.0f;

int main () {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Radius");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        window.display();
    } 

}