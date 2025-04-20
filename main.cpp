#include <SFML/Graphics.hpp>
#include "constraint.h"
#include "particle.h"
#include "input.h"

unsigned int WIDTH = 300;
unsigned int HEIGHT = 300;

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Cloth Simulation");
    window.setFramerateLimit(60);

    std::vector<Particle> particles;
    std::vector<Constraint> constraints;

    window.display();
}