#include <iostream>
#include <SFML/Graphics.hpp> 
#include "Particle.hpp"
#include "Physics.hpp"
#include "Render.hpp"
#include <random>

int main() {
    // 1. Create a window
    sf::RenderWindow window(sf::VideoMode(800, 800), "Particle Simulator");
    //Initialize physics solver and renderer
    Physics solver(sf::Vector2f(window.getSize().x, window.getSize().y));
    Renderer renderer(solver, window);

    // Create some particles
    for(int i = 0; i < 120; ++i) {
        Particle p(window.getSize().x, window.getSize().y);
        solver.addParticles(p);
    }
    // 2. Game loop
    sf::Clock clock;
    while (window.isOpen()) {
        // 2.1 Event handling
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        // 2.2 Update particle positions, collisions, etc. (We'll add this later)
        float dt = clock.restart().asSeconds();
        solver.updateParticles_substeps(dt, 8);
        // 2.3 Rendering
        renderer.render();
    }

    return 0;
}
