#ifndef PARTICLE_COLORS_HPP
#define PARTICLE_COLORS_HPP

#include <SFML/Graphics.hpp> 
#include "RandomNumberGenerator.hpp"

class ColorUtilities{
    public:
        static sf::Color getRainbow() {
            // Random hue between 0 and 1
            float hue = RNG::Generate(0.0f, 1.0f); 

            // Convert hue to RGB
            int hi = std::floor(hue * 6);
            float f = hue * 6 - hi;
            float p = 0;
            float q = 1 - f;
            float t = f;

            switch (hi % 6) {
                case 0: return sf::Color(255, t * 255, p * 255);
                case 1: return sf::Color(q * 255, 255, p * 255);
                case 2: return sf::Color(p * 255, 255, t * 255);
                case 3: return sf::Color(p * 255, q * 255, 255);
                case 4: return sf::Color(t * 255, p * 255, 255);
                case 5: return sf::Color(255, p * 255, q * 255);
            }

            return sf::Color::Black;  // Should never reach here
        }
};

#endif // PARTICLE_COLORS_HPP