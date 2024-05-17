#include <iostream>
#include <SFML/Graphics.hpp> // You can also use SDL if you prefer
#include "Particle.hpp"
#include <random>

void window_collision(Particle &p, sf::RenderWindow &window){
    float radius = p.getRadius();
    float diameter = 2 * radius;

    // Check collision with right window edge
    if(p.getX() + diameter > window.getSize().x) {
        float x = p.getX();
        p.setX(p.getprevX());
        p.setprevX(x);
    }
    // Check collision with left window edge
    else if(p.getX() - diameter < 0) {
        float x = p.getX();
        p.setX(p.getprevX());
        p.setprevX(x);
    }

    // Check collision with bottom window edge
    if(p.getY() + diameter > window.getSize().y) {
        float y = p.getY();
        p.setY(p.getprevY());
        p.setprevY(y);
    }
    // Check collision with top window edge
    else if(p.getY() - diameter < 0) {
        float y = p.getY();
        p.setY(p.getprevY());
        p.setprevY(y);
    }
}

int main() {
    // 1. Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Particle Simulator");

    // Create some particles
    std::vector<Particle> particles;
    for(int i = 0; i < 10; ++i) {
        Particle p(window.getSize().x, window.getSize().y);
        particles.push_back(p);
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
        for(auto &p : particles) {
            
            float last_move_x = p.getX() - p.getprevX();
            float last_move_y = p.getY() - p.getprevY();

            float acceleration_y = 50.0f / p.getMass();
            float acceleration_x = 0.0f;

            float prev_x = p.getX();
            float prev_y = p.getY();

            float new_x =  p.getX() + last_move_x + (acceleration_x - last_move_x * 40) * (dt * dt);
            float new_y =  p.getY() + last_move_y + (acceleration_y - last_move_y * 40) * (dt * dt); 
            p.setX(new_x);
            p.setY(new_y);
            window_collision(p, window);

            p.setprevX(prev_x);
            p.setprevY(prev_y);

            // for(auto &p2 : particles) {
            //     if(&p == &p2){continue;}  
            //     float dx = p2.getPosition().x - p.getPosition().x;
            //     float dy = p2.getPosition().y - p.getPosition().y;
            //     float sqaureddistance = dx * dx + dy * dy;
            //     float squaredradius = (p.getRadius() + p2.getRadius()) * (p.getRadius() + p2.getRadius());
            //     if(sqaureddistance < squaredradius){
            //         double angle = atan2(dy, dx);
            //         double totalMass = p.getMass() + p2.getMass();
            //         double velocity1 = sqrt(p.getVelocity().x*p.getVelocity().x + p.getVelocity().y*p.getVelocity().y);
            //         double velocity2 = sqrt(p2.getVelocity().x*p2.getVelocity().x + p2.getVelocity().y*p2.getVelocity().y);
            //         double direction1 = atan2(p.getVelocity().y, p.getVelocity().x);
            //         double direction2 = atan2(p2.getVelocity().y, p2.getVelocity().x);
            //         double newVelocityX1 = velocity1 * cos(direction1 - angle) * (p.getMass() - p2.getMass()) + 2 * p2.getMass() * velocity2 * cos(direction2 - angle) / totalMass;
            //         double newVelocityY1 = velocity1 * sin(direction1 - angle);
            //         double newVelocityX2 = velocity2 * cos(direction2 - angle) * (p2.getMass() - p.getMass()) + 2 * p.getMass() * velocity1 * cos(direction1 - angle) / totalMass;
            //         double newVelocityY2 = velocity2 * sin(direction2 - angle);
            //         p.setVelocity(sf::Vector2f(cos(angle) * newVelocityX1 + cos(angle + M_PI/2) * newVelocityY1, sin(angle) * newVelocityX1 + sin(angle + M_PI/2) * newVelocityY1));
            //         p2.setVelocity(sf::Vector2f(cos(angle) * newVelocityX2 + cos(angle + M_PI/2) * newVelocityY2, sin(angle) * newVelocityX2 + sin(angle + M_PI/2) * newVelocityY2));
            //     }
            //}

            // p.setPosition(p.getPosition() + p.getVelocity() * dt);
        }
        // 2.3 Rendering
        window.clear();
        // Draw particles here (We'll add this later)
        for(const auto &p : particles){
            sf::CircleShape shape(p.getRadius());
            sf::Vector2f position(p.getX(), p.getY());
            shape.setPosition(position);
            shape.setFillColor(p.getColor());
            window.draw(shape);
        }
        window.display();
    }

    return 0;
}
