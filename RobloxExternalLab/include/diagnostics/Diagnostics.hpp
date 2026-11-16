#pragma once
#include <chrono>

class Diagnostics {
public:
    void tick();
    float fps() const { return fps_; }
    float frameMs() const { return frameMs_; }
private:
    using Clock = std::chrono::steady_clock;
    Clock::time_point previous_ = Clock::now();
    float fps_ = 0.0f;
    float frameMs_ = 0.0f;
};
