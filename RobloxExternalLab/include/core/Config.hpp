#pragma once
#include <string>

struct Config {
    bool esp = true;
    bool radar = true;
    bool diagnostics = true;
    bool showNames = true;
    bool showDistance = true;
    float radarRange = 100.0f;
    float opacity = 0.92f;

    void load(const std::string& path);
    void save(const std::string& path) const;
};
