#include "diagnostics/Diagnostics.hpp"
#include <algorithm>

void Diagnostics::tick() {
    const auto now = Clock::now();
    const float ms = std::chrono::duration<float, std::milli>(now - previous_).count();
    previous_ = now;
    frameMs_ = ms;
    fps_ = ms > 0.01f ? 1000.0f / ms : 0.0f;
}
