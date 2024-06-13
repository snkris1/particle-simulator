#ifndef RENDER_HPP
#define RENDER_HPP
#include "Physics.hpp"

class Renderer{
    public:
        Renderer(Physics& solver_in, sf::RenderWindow& window_in)
            : solver(solver_in), window(window_in) {}
        
        void render(bool renderPartitioning) const{
            window.clear();

            // Draw quad tree bounds
            if(renderPartitioning){
                for(const auto &b : solver.getQuadTreeBounds()){
                    sf::RectangleShape shape(sf::Vector2f(b.second.x - b.first.x, b.second.y - b.first.y));
                    shape.setPosition(b.first);
                    shape.setFillColor(sf::Color::Transparent);
                    shape.setOutlineColor(sf::Color::White);
                    shape.setOutlineThickness(1.0f);
                    window.draw(shape);
                }
            }

            // Draw particles
            for(const auto &p : solver.getParticles()){
                sf::CircleShape shape(p.getRadius());
                sf::Vector2f position(p.getX(), p.getY());
                shape.setPosition(position);
                shape.setFillColor(p.getColor());
                window.draw(shape);
            }
            window.display();
        }

    private:
    Physics& solver;
    sf::RenderWindow& window;
};

#endif //RENDER_HPP