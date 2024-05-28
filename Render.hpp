#ifndef RENDER_HPP
#define RENDER_HPP
#include "Physics.hpp"

class Renderer{
    public:
        Renderer(Physics& solver_in, sf::RenderWindow& window_in)
            : solver(solver_in), window(window_in) {}
        
        void render() const{
            window.clear();
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