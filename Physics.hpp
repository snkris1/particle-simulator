#ifndef PHYSICS_HPP
#define PHYSICS_HPP
#include "Particle.hpp"
#include "Partitioning.hpp"

class Physics{
    public:
        Physics(const sf::Vector2f& window_in)
            : window(window_in), quadTree(sf::Vector2f(0, 0), sf::Vector2f(window.x, window.y), 4) {}

        void addParticles(Particle& particle){
            particles.push_back(particle);
        }
        
        void checkCollision(float dt, float restitution){
            quadTree = Quad(sf::Vector2f(0, 0), sf::Vector2f(window.x, window.y), 4); 
            for (auto &p : particles) {
                quadTree.insert(&p); 
            }
            for (auto &p : particles){
                float range = p.getRadius() * 2;
                sf::Vector2f rangeMin(ceil(p.getX() - range), ceil(p.getY() - range)); 
                sf::Vector2f rangeMax(ceil(p.getX() + range), ceil(p.getY() + range));

                std::vector<Particle*> nearbyParticles;
                //nearbyParticles.reserve(24);
                quadTree.queryRange(nearbyParticles, rangeMin, rangeMax);
                for (auto *p2 : nearbyParticles){
                    if(&p == p2){continue;}  
                    float dx = p2->getX() - p.getX(); // tangent vector from p2 to p in x
                    float dy = p2->getY() - p.getY();
                    float distance = std::sqrt(dx * dx + dy * dy);
                    float radiusSum = p.getRadius() + p2->getRadius();
                    //Checks for collision
                    if(distance < radiusSum && distance > 0.0001f){
                        // std::cout << "COLLISION!" << std::endl;
                        // std::cout << nearbyParticles.size() << std::endl;
                        // Calculate the unit normal and unit tangent vectors
                        float unitNormalX = dx / distance;
                        float unitNormalY = dy / distance;
                        float unitTangentX = -unitNormalY;
                        float unitTangentY = unitNormalX;
                        
                        //Relative velocity
                        float vxRel = (p.getX() - p.getprevX()) / dt - (p2->getX() - p2->getprevX()) / dt;
                        float vyRel = (p.getY() - p.getprevY()) / dt - (p2->getY() - p2->getprevY()) / dt;

                        //Relative velocity in terms of the normal direction
                        float vnRel = vxRel * unitNormalX + vyRel * unitNormalY;

                        //Impulse Scalar with loss of kinetic energy
                        float impulse = (1 + restitution) * vnRel / (1 / p.getMass() + 1 / p2->getMass());
                        if(impulse > 1.0f){impulse = 0.0f;}
                        if(impulse < -1.0f){impulse = 0.0f;}
                        
                        //Update positions
                        p.setX(p.getX() - impulse * p2->getMass() * unitNormalX * dt);
                        p.setY(p.getY() - impulse * p2->getMass() * unitNormalY * dt);
                        p2->setX(p2->getX() + impulse * p.getMass() * unitNormalX * dt);
                        p2->setY(p2->getY() + impulse * p.getMass() * unitNormalY * dt);

                        //Resolve overlap for accuracy
                        float overlap = 0.5f * (radiusSum - distance + 0.001f);  // add small value to prevent sticking
                        p.setX(p.getX() - overlap * unitNormalX);
                        p.setY(p.getY() - overlap * unitNormalY);
                        p2->setX(p2->getX() + overlap * unitNormalX);
                        p2->setY(p2->getY() + overlap * unitNormalY);

                    }
                }
            }
        }

        void updateParticles(const float dt){
            for(auto &p : particles) {
                //Border
                window_collision(p, dt);
                //gravity
                p.setAcceleration_Y(p.getAcceleration_Y() + 9.81f/10.0f);
                //Velocity threshold to prevent jitters
                velocityThreshold(p, 1.0f, dt);
                p.update(dt);
                checkCollision(dt, 0.01f);
            }
        }

        void updateParticles_substeps(const float dt, const int substeps){
            const float sub_dt = dt / float(substeps);
            for(int i = 0; i < substeps; ++i){
                updateParticles(sub_dt);
            }
        }

        void window_collision(Particle& p, float dt){
        float radius = p.getRadius();
        float diameter = 2 * radius;

        // Check collision with right window edge
        if(p.getX() + diameter > window.x) {
            float x = p.getX();
            p.invertDirection_X();
            p.slowDownX(0.3);
            if(std::fabs(p.getX() - p.getprevX()) / dt < 0.01f){
                p.stopX();
                p.setAcceleration_X(0.0f);
            }
        }
        // Check collision with left window edge
        else if(p.getX() - diameter < 0) {
            float x = p.getX();
            p.invertDirection_X();
            p.slowDownX(0.3);
            if(std::fabs(p.getX() - p.getprevX()) / dt < 0.01f){
                p.stopX();
                p.setAcceleration_X(0.0f);
            }
        }

        // Check collision with bottom window edge
        if(p.getY() + diameter > window.y) {
            p.invertDirection_Y();
            //p.speedUp(0.1);
            p.slowDownY(0.3f); //simulate loss of energy after bounce
            //p.slowDownX(0.1f); may need a condition so it only slows down up to a couple bounces
            //prevents infinite bouncing once stopped since
            if(std::fabs(p.getY() - p.getprevY()) / dt < 0.01f){
                //since this keeps the particle locked to the ground I can probably utilize this 
                //instance to simulate friction from rolling
                p.stopY();
                p.setAcceleration_Y(0.0f);
            }
        }
        // Check collision with top window edge
        else if(p.getY() - diameter < 0) {
            p.invertDirection_Y();
            p.slowDownY(0.3);
        }
    }

    void velocityThreshold(Particle p, float thres, float dt){
        if(std::fabs(p.getY() - p.getprevY()) / dt < thres){
            p.stopY();
            p.setAcceleration_Y(0.0f);
        }
        if(std::fabs(p.getX() - p.getprevX()) / dt < thres){
            p.stopX();
            p.setAcceleration_X(0.0f);
        }
    }

    void velocityupperThreshold(Particle p, float thres, float dt){
        if(std::fabs(p.getY() - p.getprevY())> thres){
            p.stopY();
            p.setAcceleration_Y(0.0f);
        }
        if(std::fabs(p.getX() - p.getprevX())> thres){
            p.stopX();
            p.setAcceleration_X(0.0f);
        }
    }

    const std::vector<Particle>& getParticles() const {
        return particles;
    }
    private:
        std::vector<Particle> particles;
        sf::Vector2f window;
        Quad quadTree;
};



#endif //PHYSICS_HPP