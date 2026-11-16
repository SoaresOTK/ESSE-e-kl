#pragma once
#include "core/Config.hpp"
#include "engine/Simulation.hpp"
#include "diagnostics/Diagnostics.hpp"

void DrawOverlayUI(Config& cfg, const Simulation& sim, const Diagnostics& diag,
                   bool& menuVisible, bool& running);
