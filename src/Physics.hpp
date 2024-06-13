#ifndef PHYSICS_HPP
#define PHYSICS_HPP
#include "Particle.hpp"
#include "Partitioning.hpp"

class Physics{
    public:
        Physics(const sf::Vector2f& window_in)
            : window(window_in), quadTree(sf::Vector2f(0, 0), sf::Vector2f(window.x, window.y), 8) {gravity = 150.0f;}

        void addParticles(Particle& particle){
            particles.push_back(particle);
        }
        
        const std::vector<Particle>& getParticles() const {
            return particles;
        }

        int getParticleCount() const {
            return particles.size();
        }

        void addVelocity(Particle &p, sf::Vector2f velocity) {
            p.addVelocity(velocity, getStepDt());
        }

        void setGravity(float gravity_in){
            gravity = gravity_in;
        }

        void setSimulationUpdateRate(float rate){
            frame_dt = 1.0f / rate;
        }

        void setSubSteps(int steps_in){
            substeps = steps_in;
        }

        void updateSimulation(){
            float step_dt = getStepDt();
            for(int i = 0; i < substeps; ++i){
                Collision(step_dt);
                updateParticles(step_dt);
            }
        }

        const std::vector<std::pair<sf::Vector2f, sf::Vector2f>> getQuadTreeBounds() const {
            return quadTree.getAllBounds(); 
        } 

    private:
        sf::Vector2f window;
        float frame_dt;
        int substeps;
        std::vector<Particle> particles;
        Quad quadTree;
        float gravity;

        void Collision(float dt){
            // N.B. This means that the quadtree is rebuilt every substep
            quadTree = Quad(sf::Vector2f(0, 0), sf::Vector2f(window.x, window.y), 8); 
            for (auto &p : particles) {
                quadTree.insert(&p); 
            }
            for (auto &p : particles){
                float range = p.getRadius() * 2;
                sf::Vector2f rangeMin((p.getX() - range), (p.getY() - range)); 
                sf::Vector2f rangeMax((p.getX() + range), (p.getY() + range));
                std::vector<Particle*> nearbyParticles;
                quadTree.queryRange(nearbyParticles, rangeMin, rangeMax);

                for (auto *p2 : nearbyParticles){
                    if(&p == p2){continue;}  

                    sf::Vector2f pPos = p.getPos();
                    sf::Vector2f p2Pos = p2->getPos();

                    float dx = p2Pos.x - pPos.x;
                    float dy = p2Pos.y - pPos.y;
                    float distanceSquared = dx * dx + dy * dy;
                    float radiusSum = p.getRadius() + p2->getRadius();
                    float radiusSumSquared = radiusSum * radiusSum;

                    //Checks if particles are colliding
                    if(distanceSquared < radiusSumSquared && distanceSquared > 0.0001f){
                    // Resolve collision //
                        float distance = std::sqrt(distanceSquared);
                        float unitNormalX = dx / distance;
                        float unitNormalY = dy / distance;
                        float unitTangentX = -unitNormalY;
                        float unitTangentY = unitNormalX;

                        sf::Vector2f pPrevPos = p.getPrevPos();
                        sf::Vector2f p2PrevPos = p2->getPrevPos();

                        float pMass = p.getMass();
                        float p2Mass = p2->getMass();

                        //Relative velocity
                        float vxRel = (pPos.x - pPrevPos.x) / dt - (p2Pos.x - p2PrevPos.x) / dt;
                        float vyRel = (pPos.y - pPrevPos.y) / dt - (p2Pos.y - p2PrevPos.y) / dt;

                        //Relative velocity in terms of the normal direction
                        float vnRel = vxRel * unitNormalX + vyRel * unitNormalY;

                        //Impulse Scalar with loss of kinetic energy
                        float e = 0.01f; //Coefficient of restitution
                        float impulse = (1 + e) * vnRel / (1 / pMass + 1 / p2Mass);
                        if(impulse > 1.0f){impulse = 0.0f;}
                        if(impulse < -1.0f){impulse = 0.0f;}
                       
                        
                        //Update positions
                        p.setPos({pPos.x - impulse * p2Mass * unitNormalX * dt, pPos.y - 
                        impulse * p2Mass * unitNormalY * dt});
                        p2->setPos({p2Pos.x + impulse * pMass * unitNormalX * dt, p2Pos.y + 
                        impulse * pMass * unitNormalY * dt});

                        //Resolve overlap for accuracy
                        float overlap = 0.5f * (radiusSum - distance);
                        p.setPos(sf::Vector2f(pPos.x - overlap * unitNormalX, pPos.y - overlap * unitNormalY));
                        p2->setPos(sf::Vector2f(p2Pos.x + overlap * unitNormalX, p2Pos.y + overlap * unitNormalY));
                    }
                }
            }
        }

        void window_collision(Particle& p, float dt){
            float radius = p.getRadius();
            float diameter = 2 * radius;

            // Check collision with right window edge
            if(p.getX() + diameter > window.x) {
                float x = p.getX(); 
                p.invertDirection_X(); // simulate bounce
                p.slowDownX(0.3); // simulate loss of energy after bounce
            }

            // Check collision with left window edge
            else if(p.getX() - diameter < 0) {
                float x = p.getX();
                p.invertDirection_X();
                p.slowDownX(0.3);
            }

            // Check collision with bottom window edge
            if(p.getY() + diameter > window.y) {
                p.invertDirection_Y();
                p.slowDownY(0.3f); 
            }

            // Check collision with top window edge
            else if(p.getY() - diameter < 0) {
                p.invertDirection_Y();
                p.slowDownY(0.3);
            }
        }

        void updateParticles(const float dt){
            for(auto &p : particles){
                window_collision(p, dt); //collision with window
                p.setAcceleration_Y(p.getAcceleration_Y() + gravity); //gravity
                p.update(dt); //update position
            }
        }

        float getStepDt(){
            return frame_dt / float(substeps);
        }
};



#endif //PHYSICS_HPP