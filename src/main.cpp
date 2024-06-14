#include <SFML/Graphics.hpp> 
#include "Particle.hpp"
#include "Physics.hpp"
#include "Render.hpp"
#include "utilities/RandomNumberGenerator.hpp"
#include "utilities/ParticleColors.hpp"

int main() {
    // Create window and set frame rate
    sf::RenderWindow window(sf::VideoMode(800, 800), "Particle Simulator");
    float frame_rate = 60.0f;
    window.setFramerateLimit(frame_rate);

    //Initialize physics solver and renderer
    Physics solver(sf::Vector2f(window.getSize().x, window.getSize().y));
    solver.setSubSteps(8);
    solver.setSimulationUpdateRate(frame_rate);
    Renderer renderer(solver, window);
    bool renderPartitioning = false; // Set to true to render the partitioning. N.B. This will slow down the simulation.

    //Simulation parameters
    float overallNumParticles = 8000.0f;
    float numParticlesPerSpawn = 20.0f;
    sf::Vector2f particleVelocity = {1000.0f, 0.0f};
    float particleRadius = 3.0f;
    float particleMass = 1.0f;
    float particleSpawnDelay = 0.02f;
    solver.setGravity(150.0f); 


    // Game loop
    sf::Clock clock;
    while (window.isOpen()) {
        // Event handling
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        // Add particles periodically 
        if(solver.getParticleCount() < overallNumParticles && clock.getElapsedTime().asSeconds() > particleSpawnDelay){
            clock.restart();
            sf::Color color = ColorUtilities::getRainbow();
            for (int i = 0; i < numParticlesPerSpawn; i++){
                // N.B. Simulation has not been optimized for particles of varying radii
                Particle p(20, 40 + i * 10, color, particleRadius, particleMass);
                solver.addVelocity(p , particleVelocity);
                solver.addParticles(p);
            }
        }

        // Update particle positions, collisions, etc.
        solver.updateSimulation();

        // 2.3 Rendering
        renderer.render(renderPartitioning);
    }

    return 0;
}
