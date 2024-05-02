#pragma once
#include <cmath>
#include <random>

#include "point.hpp"
namespace kckn {
    class RandomParticle : public Point {
        float x_direction;
        float y_direction;
        float speed;
        std::random_device rd;
        std::mt19937 gen;
        std::uniform_int_distribution<int> speed_randomer;
        std::uniform_int_distribution<int> direction_randomer;

    public:
        RandomParticle(float x, float y);
        void move_randomly();
    };

} // namespace kckn
