#include "random_particle.hpp"
using namespace kckn;
RandomParticle::RandomParticle(float x, float y)
    : Point(x, y),
      gen(rd()),
      speed_randomer(-10, 10),
      direction_randomer(-10, 10) {

    x_direction = direction_randomer(gen) / 10.0f;
    y_direction = direction_randomer(gen) / 10.0f;

    speed = speed_randomer(gen) / 10.0f;
    // blue is slow, red is fast
    set_color(0 + speed, 0.4f, 1 - speed, 1.0f);
}
void RandomParticle::move_randomly() {
    auto random_x   = x_direction + speed_randomer(gen) / 10.f;
    auto random_y   = y_direction + speed_randomer(gen) / 10.f;
    auto normalizer = sqrt(random_x * random_x + random_y * random_y);
    random_x /= normalizer;
    random_y /= normalizer;
    Point::move(random_x * speed, random_y * speed);
}
