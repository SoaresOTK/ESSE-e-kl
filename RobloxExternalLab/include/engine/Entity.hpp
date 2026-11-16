#pragma once
#include <string>

struct Vec3 {
    float x = 0, y = 0, z = 0;
};

struct Entity {
    int id = 0;
    std::string name;
    Vec3 position;
    float health = 100.0f;
    bool active = true;
};
