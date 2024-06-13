#ifndef PARTITIONING_HPP
#define PARTITIONING_HPP

#include <cmath>
#include <SFML/Graphics.hpp>
#include "Particle.hpp"

// Quad Tree for spatial partitioning
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
    
    Quad(const sf::Vector2f min_in, const sf::Vector2f max_in, const int capacity_in){
        min = min_in;
        max = max_in;
        particles.clear();
        capacity = capacity_in;
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
    
    void insert(Particle* particle){
        if(particle == nullptr){
            return;
        }

        if(!contains(particle->getX(), particle->getY())){
            return;
        }

        if(max.x - min.x < particle->getRadius() * 2 || max.y - min.y < particle->getRadius() * 2){
            return;
        }

        // Only recursively insert when cell is at capacity
        if (particles.size() == capacity){
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
        
        if(particles.capacity() == 0){
            return;
        }
        
        //Check if the entire quad is within the query range.
        if (rangeMin.x <= min.x && rangeMax.x >= max.x && 
        rangeMin.y <= min.y && rangeMax.y >= max.y) {
            // Directly add all particles in this quad.
            particlesInRange.insert(particlesInRange.end(), particles.begin(), particles.end());
            return; //safe to return since the only time an entire quad is in the range is when it is a leaf node
        }

        // Check each particle in quad which is partially intersecting the query range
        for (Particle* p : particles) {
            sf::Vector2f pos = p->getPos();
            if (pos.x >= rangeMin.x && pos.x <= rangeMax.x &&
                pos.y >= rangeMin.y && pos.y <= rangeMax.y) {
                particlesInRange.push_back(p);
            }
        }
            

        // Recursively check child quads
        if (topLeft != nullptr) {topLeft->queryRange(particlesInRange, rangeMin, rangeMax);}
        if (topRight != nullptr) {topRight->queryRange(particlesInRange, rangeMin, rangeMax);}
        if (bottomLeft != nullptr) {bottomLeft->queryRange(particlesInRange, rangeMin, rangeMax);}
        if (bottomRight != nullptr) {bottomRight->queryRange(particlesInRange, rangeMin, rangeMax);}
    }

    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> getAllBounds() const {
        std::vector<std::pair<sf::Vector2f, sf::Vector2f>> bounds;

        // Add the bounds of this quad
        bounds.push_back({min, max});

        // Recursively add the bounds of the child quads
        if (topLeft != nullptr) {
            auto topLeftBounds = topLeft->getAllBounds();
            bounds.insert(bounds.end(), topLeftBounds.begin(), topLeftBounds.end());
        }
        if (topRight != nullptr) {
            auto topRightBounds = topRight->getAllBounds();
            bounds.insert(bounds.end(), topRightBounds.begin(), topRightBounds.end());
        }
        if (bottomLeft != nullptr) {
            auto bottomLeftBounds = bottomLeft->getAllBounds();
            bounds.insert(bounds.end(), bottomLeftBounds.begin(), bottomLeftBounds.end());
        }
        if (bottomRight != nullptr) {
            auto bottomRightBounds = bottomRight->getAllBounds();
            bounds.insert(bounds.end(), bottomRightBounds.begin(), bottomRightBounds.end());
        }

        return bounds;
    }

private: 
    // Boundary for object
    sf::Vector2f min;
    sf::Vector2f max;

    // Quad Capacity
    int capacity;

    std::vector<Particle*> particles; // Store particle pointers in this quad

    // Children Quads
    Quad* topLeft;
    Quad* topRight;
    Quad* bottomLeft;
    Quad* bottomRight;

    bool contains(const float x, const float y){
        return (x >= min.x && x <= max.x 
             && y >= min.y && y <= max.y);
    }
};

#endif //PARTITIONING_HPP