#ifndef PARTICLE
#define PARTICLE

#include <SFML/Graphics.hpp>
#include <cmath>

class Particle {
    public:
        sf::Vector2f position;
        sf::Vector2f past_position;
        sf::Vector2f acceleration;
        bool pin;
        

        Particle(double x, double y, bool pinned = false) : position(x, y), past_position(x, y), acceleration(x, y), pin(pinned) { }

        void apply_force (const sf::Vector2f& force) {
            if (!pin) {
                acceleration += force;
            }
        }

        void update(double step) {
            if (!pin) {
                sf::Vector2f velocity = position - past_position;
                past_position = position;
                position += velocity + acceleration * static_cast<float>(pow(step, 2));
                acceleration = sf::Vector2f(0, 0);
            }
        }

        void bounds (double width, double height) {
            if (position.x < 0) position.x = 0;
            if (position.x > width) position.x = width;
            if (position.y < 0) position.y = 0;
            if (position.y > width) position.y = width;
        }
    };
#endif 