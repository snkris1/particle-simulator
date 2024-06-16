#include "unit_test_framework.hpp"
#include "/home/snkris/ParticleSystem/src/Particle.hpp"
#include "/home/snkris/ParticleSystem/src/Physics.hpp"

TEST(test_particle_count) {
    // arrange
    Physics solver(sf::Vector2f(800, 800));
    float frame_rate = 60.0f;
    solver.setSimulationUpdateRate(frame_rate);
    solver.setSubSteps(8);
    for (int i = 0; i < 8000; i++){
        Particle p;
        solver.addParticles(p);
    }

    // act
    int count = solver.getParticleCount();

    // assert
    ASSERT_EQUAL(count, 8000);
}

TEST(test_add_velocity) {
    // arrange
    Physics solver(sf::Vector2f(800, 800));
    float frame_rate = 60.0f;
    int substeps = 8;
    float frame_dt = 1.0f / frame_rate;
    float stepDt = frame_dt / float(substeps);
    solver.setSimulationUpdateRate(frame_rate);
    solver.setSubSteps(substeps);
    Particle p;
    sf::Vector2f velocity = {1000.0f, 0.0f};

    // act
    solver.addVelocity(p, velocity);

    // assert
    float velocity_X = (p.getX() - p.getprevX()) / stepDt;
    float velocity_Y = (p.getY() - p.getprevY()) / stepDt;
    ASSERT_EQUAL(velocity_X, 1000.0f);
    ASSERT_EQUAL(velocity_Y, 0.0f);
}

TEST(test_add_velocity1) {
    // arrange
    Physics solver(sf::Vector2f(800, 800));
    float frame_rate = 120.0f;
    int substeps = 8;
    float frame_dt = 1.0f / frame_rate;
    float stepDt = frame_dt / float(substeps);
    solver.setSimulationUpdateRate(frame_rate);
    solver.setSubSteps(substeps);
    Particle p;
    sf::Vector2f velocity = {1000.0f, 0.0f};

    // act
    solver.addVelocity(p, velocity);

    // assert
    float velocity_X = (p.getX() - p.getprevX()) / stepDt;
    float velocity_Y = (p.getY() - p.getprevY()) / stepDt;
    ASSERT_EQUAL(velocity_X, 1000.0f);
    ASSERT_EQUAL(velocity_Y, 0.0f);
}

TEST_MAIN()