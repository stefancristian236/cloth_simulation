#ifndef CONSTRAINT
#define CONSTRAINT

#include "particle.h"
#include <cmath>
#include <limits>

class Constraint {
    public:
        Particle *P1, *P2;
        double initial_length;
        bool active;

        Constraint(Particle *p1, Particle *p2) : P1(p1), P2(p2) {
            initial_length = std::hypot(p2->position.x - p1->position.x,
                                        p2->position.y - p1->position.y);    
            active = true;
        }

        void condition() {
            if (!active) return;

            sf::Vector2f delta = P2->position - P1->position;
            double length = std::hypot(delta.x, delta.y);

            if (length == 0.0) return;

            double diff = (length - initial_length) / length;
            sf::Vector2f correct = delta * 0.5f * static_cast<float>(diff);

            if (!P1->pin) P1->position += correct;
            if (!P2->pin) P2->position -= correct;  
        }

        void deactivate() {
            active = false;
        }
};

#endif
