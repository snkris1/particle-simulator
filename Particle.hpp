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

        setRadius(4.0f);
        setX(dis(gen) * (windowWidth - 3.0f * getRadius()));
        setprevX(getX());
        setY(dis(gen) * (windowHeight - 3.0f * getRadius() - 10.0f) + 20.0f);
        setprevY(getY());
        setMass(1.0f);
        setColor(sf::Color(dis(gen) * 255, dis(gen) * 255, dis(gen) * 255));
        setAcceleration_X(dis(gen) * 20.0f - 10.0f);
        setAcceleration_Y(dis(gen) * 50.0f);
        //setAcceleration_X(0.0f);
    }

    Particle(float x, float y, sf::Color color, float radius, float mass)
    : x(x), y(y), prev_x(x), prev_y(y), color(color), radius(radius), mass(mass) {}

    float getX() const { return x; }
    void setX(float newX) { x = newX; }

    float getprevX() const { return prev_x; }
    void setprevX(float newprevX) { prev_x = newprevX;}

    float getY() const { return y; }
    void setY(float newY) { y = newY; }

    float getprevY() const { return prev_y; }
    void setprevY(float newprevY) { prev_y = newprevY;}

    sf::Color getColor() const { return color; }
    void setColor(sf::Color newColor) { color = newColor; }

    float getRadius() const { return radius; }
    void setRadius(float newRadius) { radius = newRadius; }

    float getMass() const { return mass; }
    void setMass(float newMass) { mass = newMass; }

    void update(float dt) {
        //Verlet Integration
        float last_move_x = getX() - getprevX(); //last velocity of x
        float last_move_y = getY() - getprevY(); //last velocity of y

        //velocity_threshold(0.10f); //to prevent 'infinity' low-velocity bouncing
        //add to physics file

        float prev_x = getX();
        float prev_y = getY();

        float velocity_damping = 50.0f; 
        float new_x =  getX() + last_move_x + (acceleration_x - last_move_x * velocity_damping) * (dt * dt);
        float new_y =  getY() + last_move_y + (acceleration_y - last_move_y * velocity_damping) * (dt * dt); 
        setX(new_x);
        setY(new_y);

        setprevX(prev_x);
        setprevY(prev_y);
    }

    void velocity_threshold(float threshold){
        if(std::fabs(getX() - getprevX()) < threshold){
            stopX();
        }
        if(std::fabs(getY() - getprevY()) < threshold){
            stopY();
        }
    }

    void stopY(){ //delete 
        setprevY(getY());
    }

    void stopX(){ //delete
        setprevX(getX());
    }

    void stop(){
        stopX();
        stopY();
    }

    void addVelocity(sf::Vector2f velocity){
        setprevX(getprevX() - velocity.x);
        setprevY(getprevY() - velocity.y);
    }

    void removeVelocity(sf::Vector2f velocity){
        //implement throw error if velocity is greater than current velocity
        setprevX(getprevX() + velocity.x);
        setprevY(getprevY() + velocity.y);
    }

    void slowDown(float factor){
        //throw error if factor is greater than 1
        setprevX(getprevX() + factor * (getX() - getprevX()));
        setprevY(getprevY() + factor * (getY() - getprevY()));
    }

    void slowDownX(float factor){
        //throw error if factor is greater than 1
        setprevX(getprevX() + factor * (getX() - getprevX()));
    }

    void slowDownY(float factor){
        //throw error if factor is greater than 1
        setprevY(getprevY() + factor * (getY() - getprevY()));
    }

    void speedUp(float factor){
        setprevX(getprevX() - factor * (getX() - getprevX()));
        setprevY(getprevY() - factor * (getY() - getprevY()));
    }

    void invertDirection_Y(){
        float y = getY();
        setY(getprevY());
        setprevY(y);
    }
    void invertDirection_X(){
        float x = getX();
        setX(getprevX());
        setprevX(x);
    }

    void setAcceleration_X(float x_in){
        acceleration_x = x_in;
    }

    void setAcceleration_Y(float y_in){
        acceleration_y = y_in;
    }

    float getAcceleration_Y(){
        return acceleration_y;
    }

private:
    float x;
    float y;
    float prev_x;
    float prev_y;
    sf::Color color;
    float radius;
    float mass;
    float acceleration_x;
    float acceleration_y;
};

#endif // PARTICLE_HPP