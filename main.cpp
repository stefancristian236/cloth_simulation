#include <SFML/Graphics.hpp>
#include "constraint.h"
#include "particle.h"
#include "input.h"

unsigned int WIDTH = 1080;
unsigned int HEIGHT = 640;
const double radius = 10.0f;
const double gravitaitional__acceleration = 9.81f;
const double time_step = 0.1f;

unsigned int ROW = 20;
unsigned int COL = 20;
const double restD = 20.0f;

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Cloth Simulation");
    window.setFramerateLimit(60);

    std::vector<Particle> particles;
    std::vector<Constraint> constraints;

    for (int row = 0; row < ROW; ++row) {
        for (int col = 0; col < COL; ++col) {
            double x = col * restD * WIDTH/3;
            double y = row * restD * HEIGHT/3;
            bool pin = (row == 0);
            particles.emplace_back(x, y, pin);
        }
    }

    for (int row  = 0; row < ROW; ++row) {
        for (int col = 0; col < COL; ++col) {
            if (col < COL - 1) {
                constraints.emplace_back(&particles[row * COL + col], &particles[row * COL + col + 1]);
            }
            if (row < ROW - 1) {
                constraints.emplace_back(&particles[row * COL + col], &particles[(row + 1) * COL + col]);
            }
        }
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            window.close();
        }
        input::mouse_click(event, particles, constraints);
    }

    for (auto& particle: particles) {
        particle.apply_force(sf::Vector2f(0, gravitaitional__acceleration));
        particle.update(time_step);
        particle.bounds(WIDTH,HEIGHT);
    }

    for (size_t i = 0; i < 5; i++) {
        for (auto& constraint : constraints) {
            constraint.condition();
        }
    }
    window.clear(sf::Color::Black);

    for (const auto& particle : particles) {
        sf::Vertex point (particle.position, sf::Color::Green);
        window.draw(&point, 1, sf::Points);
    }

    for (const auto& constraint : constraints) {
        if (!constraint.active) {
            continue;
        }
        sf::Vertex line[] = {
            sf::Vertex(constraint.P1->position, sf::Color::White),
            sf::Vertex(constraint.P2->position, sf::Color::White),
        };
        window.draw(line, 2, sf::Lines);
    }
    window.display();

}