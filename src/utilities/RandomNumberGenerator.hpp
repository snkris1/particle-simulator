#ifndef RANDOM_NUMBER_GENERATOR_HPP
#define RANDOM_NUMBER_GENERATOR_HPP

#include <random>

class RNG{
    public:
        static float Generate(const float range_from_in, const float range_to_in) {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            static std::uniform_real_distribution<float> dis(range_from_in, range_to_in);

            return dis(gen);
        }
};

#endif // RANDOM_NUMBER_GENERATOR_HPP