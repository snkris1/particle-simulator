#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML/Graphics.hpp>
#include <random>

class Particle {
public:

    Particle() {
        setRadius(5.0f);
        setX(0.0f);
        setprevX(getX());
        setY(0.0f);
        setprevY(getY());
        setMass(1.0f);
        setColor(sf::Color::White);
        setAcceleration_X(0.0f);
        setAcceleration_Y(0.0f);
    }

    Particle(float windowWidth, float windowHeight) {
        std::vector<Particle> particles;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(0.0f, 1.0f);

        setRadius(3.125f);
        setX(dis(gen) * (windowWidth - 8.0f * getRadius() - 10.0f) + 20.0f);
        setprevX(getX());
        setY(dis(gen) * (windowHeight - 8.0f * getRadius() - 10.0f) + 20.0f);
        setprevY(getY());
        setMass(1.0f);
        setColor(sf::Color(dis(gen) * 255, dis(gen) * 255, dis(gen) * 255));
        setAcceleration_X(dis(gen) * 20.0f - 10.0f);
        setAcceleration_Y(dis(gen) * 50.0f);
    }

    Particle(float x, float y, sf::Color color, float radius, float mass)
    : position({x, y}), prevPosition({x, y}), color(color), radius(radius), mass(mass) {}

    sf::Vector2f getPos() const { return position;}
    void setPos(sf::Vector2f newPos) { position = newPos;}

    float getX() const { return position.x; }
    void setX(float newX) { position.x = newX; }

    float getY() const { return position.y; }
    void setY(float newY) { position.y = newY; }

    sf::Vector2f getPrevPos() const { return prevPosition;}
    void setPrevPos(sf::Vector2f newPrevPosition) { prevPosition = newPrevPosition;}

    float getprevX() const { return prevPosition.x; }
    void setprevX(float newprevX) { prevPosition.x = newprevX;}

    float getprevY() const { return prevPosition.y; }
    void setprevY(float newprevY) { prevPosition.y = newprevY;}

    sf::Color getColor() const { return color; }
    void setColor(sf::Color newColor) { color = newColor; }

    float getRadius() const { return radius; }
    void setRadius(float newRadius) { radius = newRadius; }

    float getMass() const { return mass; }
    void setMass(float newMass) { mass = newMass; }

    void update(float dt) {
        //Verlet Integration
        float last_move_x = position.x - prevPosition.x; 
        float last_move_y = position.y - prevPosition.y; 

        float prev_x = position.x;
        float prev_y = position.y;

        float velocity_damping = 50.0f; 
        float new_x =  position.x + last_move_x + (acceleration.x - last_move_x * velocity_damping) * (dt * dt);
        float new_y =  position.y + last_move_y + (acceleration.y - last_move_y * velocity_damping) * (dt * dt); 

        position.x = new_x;
        position.y = new_y;

        prevPosition.x = prev_x;
        prevPosition.y = prev_y;

        acceleration.x = 0.0f;
        acceleration.y = 0.0f;
    }

    void stopY(){ 
        prevPosition.y = position.y;
    }

    void stopX(){ 
        prevPosition.x = position.x;
    }

    void stop(){
        stopX();
        stopY();
    }

    void addVelocity(sf::Vector2f velocity, float dt){ 
        setprevX(getprevX() - velocity.x * dt);
        setprevY(getprevY() - velocity.y * dt);
    }

    /**
     * Slows down the particle by a given factor.
     * Requires: The factor cannot exceed 1.
     * Note: A factor of 1 will stop the particle.
     */
    void slowDown(float factor){
        slowDownX(factor);
        slowDownY(factor);
    }
    
    /**
     * Slows down the particle in the x direction by a given factor.
     * Requires: The factor cannot exceed 1.
     * Note: A factor of 1 will stop the particle.
     */
    void slowDownX(float factor){
        prevPosition.x = prevPosition.x + factor * (position.x - prevPosition.x);
    }

    /**
     * Slows down the particle in the y direction by a given factor.
     * Requires: The factor cannot exceed 1.
     * Note: A factor of 1 will stop the particle.
     */
    void slowDownY(float factor){
        prevPosition.y = prevPosition.y + factor * (position.y - prevPosition.y);
    }

    /**
     * Speeds up the particle by a given factor.
     * Requires: The factor cannot exceed 1.
     * Note: A factor of 1 will stop the particle.
     */
    void speedUp(float factor){
        setprevX(getprevX() - factor * (getX() - getprevX()));
        setprevY(getprevY() - factor * (getY() - getprevY()));
    }

    /**
     * Inverts the direction of the particle in the y direction.
     */
    void invertDirection_Y(){
        float y = position.y;
        position.y = prevPosition.y;
        prevPosition.y = y;
    }

    /**
     * Inverts the direction of the particle in the x direction.
     */
    void invertDirection_X(){
        float x = position.x;
        position.x = prevPosition.x;
        prevPosition.x = x;
    }

    /**
     * Sets the acceleration of the particle in the x direction.
     * Note: The affect of the acceleration will only be applied in a single sub step.
     */
    void setAcceleration_X(float x_in){
        acceleration.x = x_in;
    }

    /**
     * Sets the acceleration of the particle in the y direction.
     * Note: The affect of the acceleration will only be applied in a single sub step.
     */
    void setAcceleration_Y(float y_in){
        acceleration.y = y_in;
    }

    float getAcceleration_Y(){
        return acceleration.y;
    }

private:
    sf::Vector2f position;
    sf::Vector2f prevPosition;
    sf::Color color;
    float radius;
    float mass;
    sf::Vector2f acceleration;
};

#endif // PARTICLE_HPP