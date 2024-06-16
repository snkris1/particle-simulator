#include "unit_test_framework.hpp"
#include "/home/snkris/ParticleSystem/src/Partitioning.hpp"
#include "/home/snkris/ParticleSystem/src/Particle.hpp"

TEST(test_quad_insertion) {
    // arrange
    int QUAD_CAPACITY = 1;
    Quad quad(sf::Vector2f(0, 0), sf::Vector2f(800, 800), QUAD_CAPACITY);
    Particle p;

    // act
    quad.insert(&p);

    // assert
    ASSERT_EQUAL(quad.getAllBounds().size(), 1);
}

TEST(test_quad_subdivision) {
    // arrange
    int QUAD_CAPACITY = 8;
    Quad quad(sf::Vector2f(0, 0), sf::Vector2f(800, 800), QUAD_CAPACITY);

    // act
    std::vector<Particle*> heapParticles;
    for (int i = 0; i < 9; ++i){
        Particle* p = new Particle;
        quad.insert(p);
    }

    // assert
    int NUMBER_OF_SUBDIVISIONS = 2;
    ASSERT_EQUAL(quad.getAllBounds().size(), NUMBER_OF_SUBDIVISIONS);

    // cleanup
    for (Particle* p : heapParticles) {
        delete p;
    }
}

TEST(test_quad_subdivision1) {
    // arrange
    int QUAD_CAPACITY = 8;
    Quad quad(sf::Vector2f(0, 0), sf::Vector2f(800, 800), QUAD_CAPACITY);

    // act
    std::vector<Particle*> heapParticles;
    for (int i = 0; i < 16; ++i){
        Particle* p = new Particle;
        quad.insert(p);
    }

    // assert
    int NUMBER_OF_SUBDIVISIONS = 2;
    ASSERT_EQUAL(quad.getAllBounds().size(), NUMBER_OF_SUBDIVISIONS);

    // cleanup
    for (Particle* p : heapParticles) {
        delete p;
    }
}

TEST(test_quad_subdivision2) {
    // arrange
    int QUAD_CAPACITY = 8;
    Quad quad(sf::Vector2f(0, 0), sf::Vector2f(800, 800), QUAD_CAPACITY);

    // act
    std::vector<Particle*> heapParticles;
    for (int i = 0; i < 17; ++i){
        Particle* p = new Particle;
        quad.insert(p);
    }

    // assert
    int NUMBER_OF_SUBDIVISIONS = 3;
    ASSERT_EQUAL(quad.getAllBounds().size(), NUMBER_OF_SUBDIVISIONS);

    // cleanup
    for (Particle* p : heapParticles) {
        delete p;
    }
}

TEST(test_quad_subdivision3) {
    // arrange
    int QUAD_CAPACITY = 8;
    Quad quad(sf::Vector2f(0, 0), sf::Vector2f(800, 800), QUAD_CAPACITY);

    // act
    std::vector<Particle*> heapParticles;
    for (int i = 0; i < 64; ++i){
        Particle* p = new Particle;
        quad.insert(p);
    }

    // assert
    int NUMBER_OF_SUBDIVISIONS = 8;
    ASSERT_EQUAL(quad.getAllBounds().size(), NUMBER_OF_SUBDIVISIONS);

    // cleanup
    for (Particle* p : heapParticles) {
        delete p;
    }
}

TEST(test_quad_subdivision4) {
    // arrange
    int QUAD_CAPACITY = 8;
    Quad quad(sf::Vector2f(0, 0), sf::Vector2f(800, 800), QUAD_CAPACITY);

    // act
    std::vector<Particle*> heapParticles;
    for (int i = 0; i < 65; ++i){
        Particle* p = new Particle;
        quad.insert(p);
    }

    // assert
    int NUMBER_OF_SUBDIVISIONS = 8;
    ASSERT_EQUAL(quad.getAllBounds().size(), NUMBER_OF_SUBDIVISIONS);

    // cleanup
    for (Particle* p : heapParticles) {
        delete p;
    }
}

TEST(test_quad_query_range) {
    // arrange
    int QUAD_CAPACITY = 1;
    Quad quad(sf::Vector2f(0, 0), sf::Vector2f(800, 800), QUAD_CAPACITY);
    Particle p(500, 500);
    Particle p1(600, 600);
    quad.insert(&p);
    quad.insert(&p1);
    std::vector<Particle*> particlesInRange;
    float range = p.getRadius() * 2;
    sf::Vector2f rangeMin((p.getX() - range), (p.getY() - range)); 
    sf::Vector2f rangeMax((p.getX() + range), (p.getY() + range));

    // act
    quad.queryRange(particlesInRange, rangeMin, rangeMax);

    // assert
    ASSERT_EQUAL(particlesInRange.size(), 1);
    ASSERT_EQUAL(particlesInRange[0], &p);
}

TEST(test_quad_query_range1) {
    // arrange
    int QUAD_CAPACITY = 1;
    Quad quad(sf::Vector2f(0, 0), sf::Vector2f(800, 800), QUAD_CAPACITY);
    Particle p(500, 500);
    Particle p1(503, 503);
    quad.insert(&p);
    quad.insert(&p1);
    std::vector<Particle*> particlesInRange;
    float range = p.getRadius() * 2;
    sf::Vector2f rangeMin((p.getX() - range), (p.getY() - range)); 
    sf::Vector2f rangeMax((p.getX() + range), (p.getY() + range));

    // act
    quad.queryRange(particlesInRange, rangeMin, rangeMax);

    // assert
    ASSERT_EQUAL(particlesInRange.size(), 2);
    ASSERT_EQUAL(particlesInRange[0], &p);
    ASSERT_EQUAL(particlesInRange[1], &p1);
}

TEST(test_quad_query_range2) {
    // arrange
    int QUAD_CAPACITY = 8;
    Quad quad(sf::Vector2f(0, 0), sf::Vector2f(800, 800), QUAD_CAPACITY);
    Particle p(500, 500);
    Particle p1(503, 503);
    quad.insert(&p);
    quad.insert(&p1);

    std::vector<Particle*> heapParticles;
    for (int i = 0; i < 8; ++i){
        Particle* p3 = new Particle(100, 100);
        Particle* p4 = new Particle(700, 100);
        Particle* p5 = new Particle(100, 700);
        quad.insert(p3);
        quad.insert(p4);
        quad.insert(p5);
        heapParticles.push_back(p3);
        heapParticles.push_back(p4);
        heapParticles.push_back(p5);
    }

    std::vector<Particle*> particlesInRange;
    float range = p.getRadius() * 2;
    sf::Vector2f rangeMin((p.getX() - range), (p.getY() - range)); 
    sf::Vector2f rangeMax((p.getX() + range), (p.getY() + range));

    // act
    quad.queryRange(particlesInRange, rangeMin, rangeMax);
    for(auto *p:particlesInRange){
        std::cout << p->getX() << " " << p->getY() << std::endl;
    }

    // assert
    ASSERT_EQUAL(particlesInRange.size(), 2);
    ASSERT_EQUAL(particlesInRange[0], &p);
    ASSERT_EQUAL(particlesInRange[1], &p1);

    // cleanup
    for (Particle* p : heapParticles) {
        delete p;
    }
}

TEST(test_quad_query_range3) {
    // arrange
    int QUAD_CAPACITY = 1;
    Quad quad(sf::Vector2f(0, 0), sf::Vector2f(800, 800), QUAD_CAPACITY);
    Particle p(500, 500);
    Particle p1(503, 503);
    Particle p2(700, 700);
    quad.insert(&p);
    quad.insert(&p1);
    quad.insert(&p2);
    
    std::vector<Particle*> heapParticles;
    for (int i = 0; i < 8; ++i){
        Particle* p3 = new Particle(100, 100);
        Particle* p4 = new Particle(700, 100);
        Particle* p5 = new Particle(100, 700);
        quad.insert(p3);
        quad.insert(p4);
        quad.insert(p5);
        heapParticles.push_back(p3);
        heapParticles.push_back(p4);
        heapParticles.push_back(p5);
    }

    std::vector<Particle*> particlesInRange;
    float range = p.getRadius() * 2;
    sf::Vector2f rangeMin((p.getX() - range), (p.getY() - range)); 
    sf::Vector2f rangeMax((p.getX() + range), (p.getY() + range));

    // act
    quad.queryRange(particlesInRange, rangeMin, rangeMax);

    // assert
    ASSERT_EQUAL(particlesInRange.size(), 2);
    ASSERT_EQUAL(particlesInRange[0], &p);
    ASSERT_EQUAL(particlesInRange[1], &p1);

    // cleanup
    for (Particle* p : heapParticles) {
        delete p;
    }
}

TEST_MAIN()