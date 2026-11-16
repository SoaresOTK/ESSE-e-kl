#include "engine/Simulation.hpp"
#include <cmath>

void Simulation::update(float dt) {
    elapsed_ += dt;
    if (entities_.empty()) {
        for (int i = 0; i < 12; ++i) {
            Entity e;
            e.id = i + 1;
            e.name = "TestPlayer_" + std::to_string(i + 1);
            e.position = {float((i % 4) * 18 - 27), 0.0f, float((i / 4) * 22 + 18)};
            e.health = float(55 + (i * 7) % 46);
            entities_.push_back(e);
        }
    }
    for (std::size_t i = 0; i < entities_.size(); ++i) {
        auto& e = entities_[i];
        const float phase = elapsed_ * 0.65f + float(i) * 0.7f;
        e.position.x += std::sin(phase) * dt * 1.8f;
        e.position.z += std::cos(phase * 0.8f) * dt * 1.2f;
        e.health = 55.0f + 45.0f * (0.5f + 0.5f * std::sin(elapsed_ * 0.3f + float(i)));
    }
}
