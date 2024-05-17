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
    }

    Particle(float windowWidth, float windowHeight) {
        std::vector<Particle> particles;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(0.0f, 1.0f);

        setRadius(10.0f);
        setX(dis(gen) * (windowWidth - 2 * getRadius()));
        setprevX(getX());
        setY(dis(gen) * (windowHeight - 2* getRadius()));
        setprevY(getY());
        setMass(dis(gen) * 1.0f);
        setColor(sf::Color(dis(gen) * 255, dis(gen) * 255, dis(gen) * 255));
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

private:
    float x;
    float y;
    float prev_x;
    float prev_y;
    sf::Color color;
    float radius;
    float mass;
};

#endif // PARTICLE_HPP