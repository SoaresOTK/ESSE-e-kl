#pragma once
#include "engine/Entity.hpp"
#include <vector>

class Simulation {
public:
    void update(float dt);
    const std::vector<Entity>& entities() const { return entities_; }
private:
    std::vector<Entity> entities_;
    float elapsed_ = 0.0f;
};
