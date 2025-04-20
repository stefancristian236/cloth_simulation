#include <SFML/Graphics.hpp>
#include <vector>
#include "constraint.h"
#include "particle.h"
#include "input.h"  

const unsigned int WIDTH = 1080;
const unsigned int HEIGHT = 640;
const float PARTICLE_RADIUS = 10.0f;
const float GRAVITY = 10.0f;
const float TIME_STEP = 0.1f;

const int ROW = 10;
const int COL = 10;
const float REST_DISTANCE = 30.0f;

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Cloth Simulation");
    window.setFramerateLimit(60);

    std::vector<Particle> particles;
    std::vector<Constraint> constraints;

    for (int row = 0; row < ROW; ++row) {
        for (int col = 0; col < COL; ++col) {
            float x = col * REST_DISTANCE + WIDTH / 3;
            float y = row * REST_DISTANCE + HEIGHT / 3;
            bool pinned = (row == 0); 
            particles.emplace_back(x, y, pinned);
        }
    }


    for (int row = 0; row < ROW; ++row) {
        for (int col = 0; col < COL; ++col) {
            if (col < COL - 1) {
                constraints.emplace_back(&particles[row * COL + col], &particles[row * COL + (col + 1)]);
            }
            if (row < ROW - 1) {
                constraints.emplace_back(&particles[row * COL + col], &particles[(row + 1) * COL + col]);
            }
            
        }
    }
    
    auto isValid = [](const sf::Vector2f& pos) {
        return std::isfinite(pos.x) && std::isfinite(pos.y) &&
               pos.x >= 0 && pos.x <= WIDTH * 2 &&
               pos.y >= 0 && pos.y <= HEIGHT * 2;
    };
    
    for (const auto& constraint : constraints) {
        if (!constraint.active ||
            !isValid(constraint.P1->position) || !isValid(constraint.P2->position)) continue;
    
        sf::Vertex line[] = {
            sf::Vertex(constraint.P1->position, sf::Color::Green),
            sf::Vertex(constraint.P2->position, sf::Color::Green),
        };
        window.draw(line, 2, sf::Lines);
    }
    

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

           
            input::mouse_click(event, particles, constraints);
        }

   
        for (auto& particle : particles) {
            particle.apply_force(sf::Vector2f(0, GRAVITY));
            particle.update(TIME_STEP);
            particle.bounds(WIDTH, HEIGHT);
        }

   
        for (int i = 0; i < 5; ++i) {
            for (auto& constraint : constraints) {
                constraint.condition();
            }
        }

   
        window.clear(sf::Color::Black);

     
        for (const auto& particle : particles) {
            sf::Vertex point(particle.position, sf::Color::Green);
            window.draw(&point, 1, sf::Points);
        }

    
        for (const auto& constraint : constraints) {
            if (!constraint.active) continue;
            sf::Vertex line[] = {
                sf::Vertex(constraint.P1->position, sf::Color::Green),
                sf::Vertex(constraint.P2->position, sf::Color::Green),
            };
            window.draw(line, 2, sf::Lines);
        }

        window.display();
    }

    return 0;
}
