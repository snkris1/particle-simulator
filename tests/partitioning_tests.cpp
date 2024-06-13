#include "unit_test_framework.hpp"
#include "Partitioning.hpp"
#include "Particle.hpp"

TEST(test_quad_insertion) {
    // arrange
    Quad quad(sf::Vector2f(0, 0), sf::Vector2f(100, 100), 1);
    Particle p;

    // act
    quad.insert(&p);

    // assert
    ASSERT_EQUAL(quad.getAllBounds().size(), 1);
}

TEST(test_quad_subdivision) {
    // arrange
    Quad quad(sf::Vector2f(0, 0), sf::Vector2f(800, 800), 1);

    // act
    for (int i = 0; i < 9; ++i){
        Particle p;
        quad.insert(&p);
    }

    // assert
    ASSERT_EQUAL(quad.getAllBounds().size(), 2);
}

TEST(test_quad_query_range) {
    // arrange
    Quad quad(sf::Vector2f(0, 0), sf::Vector2f(800, 800), 1);
    Particle p(500, 500, sf::Color(255, 255,255), 5, 1);
    Particle p1(600, 600, sf::Color(255, 255,255), 5, 1);

    // act
    quad.insert(&p);
    quad.insert(&p1);
    std::vector<Particle*> particlesInRange;
    float range = p.getRadius() * 2;
    sf::Vector2f rangeMin((p.getX() - range), (p.getY() - range)); 
    sf::Vector2f rangeMax((p.getX() + range), (p.getY() + range));
    quad.queryRange(particlesInRange, rangeMin, rangeMax);

    // assert
    ASSERT_EQUAL(particlesInRange.size(), 1);
    ASSERT_EQUAL(particlesInRange[0], &p1);
}

TEST_MAIN()