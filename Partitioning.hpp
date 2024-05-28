#ifndef PARTITIONING_HPP
#define PARTITIONING_HPP

#include <cmath>
#include <SFML/Graphics.hpp>
#include "Particle.hpp"

// Quad Tree for partitioning
class Quad { 
public:
    Quad() {
        min = sf::Vector2f(0, 0);
        max = sf::Vector2f(0, 0);
        particles.clear();
        topLeft = nullptr;
        topRight = nullptr;
        bottomLeft = nullptr;
        bottomRight = nullptr;
    }
    
    Quad(const sf::Vector2f min_in, const sf::Vector2f max_in, const int capacity){
        min = min_in;
        max = max_in;
        particles.clear();
        particles.reserve(capacity);
        topLeft = nullptr;
        topRight = nullptr;
        bottomLeft = nullptr;
        bottomRight = nullptr;
    }

    ~Quad(){ 
        delete topLeft;
        delete topRight;
        delete bottomLeft;
        delete bottomRight;
    }

    bool contains(const float x, const float y){
        return (x >= min.x && x <= max.x 
             && y >= min.y && y <= max.y);
    }

    void insert(Particle* particle){
        if(particle == nullptr){
            return;
        }

        if(!contains(particle->getX(), particle->getY())){
            return;
        }

        // If the cell is small enough, store the particle
        // if(std::fabs(min.x - max.x) == 25.0f && std::fabs(min.y - max.y) == 25.0f){ 
        //     particles.push_back(particle);
        //     return;
        // } 

        // Only recursively insert when cell is at capacity
        if (particles.size() > capacity){
            float bottom = (min.y + max.y) / 2; 
            float right = (min.x + max.x) / 2;
            // Recursively insert into the correct quadrant
            if(right >= particle->getX()){
                if(bottom >= particle->getY()){
                    if(topLeft == nullptr){
                        topLeft = new Quad(sf::Vector2f(min.x, min.y), sf::Vector2f(right, bottom), capacity);
                    }
                    topLeft->insert(particle); 
                }
                else{
                    if(bottomLeft == nullptr){
                        bottomLeft = new Quad(sf::Vector2f(min.x, bottom), sf::Vector2f(right, max.y), capacity);
                    }
                    bottomLeft->insert(particle);
                }
            }
            else {
                if(bottom >= particle->getY()){
                    if(topRight == nullptr){
                        topRight = new Quad(sf::Vector2f(right, min.y), sf::Vector2f(max.x, bottom), capacity);
                    }
                    topRight->insert(particle);
                }
                else{
                    if(bottomRight == nullptr){
                        bottomRight = new Quad(sf::Vector2f(right, bottom), sf::Vector2f(max.x, max.y), capacity);
                    }
                    bottomRight->insert(particle);
                } 

                //redistribute particles from current quad to children
                for(auto *p:particles){insert(p);}
                particles.clear();
            }
        }
        else {particles.push_back(particle);}
    }

    // Function to retrieve particles within a given range
    void queryRange(std::vector<Particle*>& particlesInRange, sf::Vector2f& rangeMin, sf::Vector2f& rangeMax) const{

        //If this quad doesn't intersect the query range, return
        if (max.x < rangeMin.x || min.x > rangeMax.x || max.y < rangeMin.y || min.y > rangeMax.y) {
            return;
        }
        
        if(particles.size() == 0){
            return;
        }
        
        // Check if the entire quad is within the range.
        if (rangeMin.x <= min.x && rangeMax.x >= max.x && 
        rangeMin.y <= min.y && rangeMax.y >= max.y) {
            // Directly add all particles in this quad.
            particlesInRange.insert(particlesInRange.end(), particles.begin(), particles.end());
            std::cout << "IN!" << std::endl;
            return;
        }

        // Add all particles in this quad that are within the range
        for (Particle* p : particles) {
            if (p->getX() >= rangeMin.x && p->getX() <= rangeMax.x &&
                p->getY() >= rangeMin.y && p->getY() <= rangeMax.y) {
                particlesInRange.push_back(p);
            }
        }

        // Recursively check child quads
        if (topLeft != nullptr) {topLeft->queryRange(particlesInRange, rangeMin, rangeMax);}
        if (topRight != nullptr) {topRight->queryRange(particlesInRange, rangeMin, rangeMax);}
        if (bottomLeft != nullptr) {bottomLeft->queryRange(particlesInRange, rangeMin, rangeMax);}
        if (bottomRight != nullptr) {bottomRight->queryRange(particlesInRange, rangeMin, rangeMax);}
    }

private: 
    // Boundary for object
    sf::Vector2f min;
    sf::Vector2f max;

    // Cell Capacity
    int capacity;

    std::vector<Particle*> particles; // Store particles in this quad

    // Children Quads
    Quad* topLeft;
    Quad* topRight;
    Quad* bottomLeft;
    Quad* bottomRight;
};

#endif //PARTITIONING_HPP