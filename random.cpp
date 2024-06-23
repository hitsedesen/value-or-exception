#include "random.hpp"

#include <random>

float roll_probability()
{
    static std::random_device random_device;
    static std::mt19937 engine(random_device());
    static std::uniform_real_distribution<float> distribution(0, 1);
    return distribution(engine);
}
