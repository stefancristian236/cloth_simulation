#ifndef INPUT
#define INPUT

#include <SFML/Graphics.hpp>
#include <vector>
#include "constraint.h"
#include "particle.h"

const float CLICK_SENS = 5.0f;

class input {
    private:
        static float point_to_seg_dis(double Px, double Py, double X1, double Y1, double X2, double Y2) {
            double ABx = X2 - X1;
            double ABy = Y2 - Y1;

            double APx = Px - X1;
            double APy = Py - Y1;
            
            double BPx = Px - X2;
            double BPy = Py - Y2;

            double AB_AP = ABx * APx + ABy * APy;
            double AB_AB = ABx * ABx + ABy * ABy;
            double t = AB_AP / AB_AB;
        
            if (t < 0.0f) {
                return std::sqrt(APx * APx + APy * APy);
            }else if (t > 1.0f) {
                return std::sqrt(BPx * BPx + BPy * BPy);
            }else {
                double p_x = X1 + t * ABx;
                double p_y = Y1 + t * ABy;
                return std::sqrt((Px - p_x) * (Px - p_x) + (Py - p_y) * (Py - p_y));
            }

        }


    public:

        static Constraint* find_nearest_link (double mouse_x, double mouse_y, const std::vector<Constraint>& constraints) {
            Constraint *near_const = nullptr;
            double minimum_distance = CLICK_SENS;
            
            for (const auto& constraint : constraints) {
                double distance = point_to_seg_dis(mouse_x, mouse_y, constraint.P1->position.x, constraint.P1->position.y, constraint.P2->position.x, constraint.P2->position.y);
                if (distance < minimum_distance) {
                    minimum_distance = distance;
                    near_const = const_cast<Constraint*>(&constraint);
                }
            }
            return nullptr;
        }

        static void tear_cloth (double mouse_x, double mouse_y, const std::vector<Particle>& particles, std::vector<Constraint>& constraints){
            Constraint* nearLink = find_nearest_link(mouse_x, mouse_y, constraints);
            if (nearLink) {
                nearLink->deactivate();
            }
        }


        static void mouse_click (const sf::Event& event, std::vector<Particle>& particles, std::vector<Constraint>& constraints) {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                double mouse_x = static_cast<double>(event.mouseButton.x);
                double mouse_y = static_cast<double>(event.mouseButton.y);   
                tear_cloth(mouse_x, mouse_y, particles, constraints);
            }
        }
};

#endif