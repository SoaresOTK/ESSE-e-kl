#include "overlay/OverlayUI.hpp"
#include <imgui.h>
#include <cmath>
#include <string>

static void DrawESP(const Simulation& sim, const Config& cfg) {
    ImDrawList* dl = ImGui::GetBackgroundDrawList();
    const ImVec2 display = ImGui::GetIO().DisplaySize;
    const ImVec2 center(display.x * 0.5f, display.y * 0.5f);
    const float scale = 5.0f;
    for (const auto& e : sim.entities()) {
        if (!e.active) continue;
        const float x = center.x + e.position.x * scale;
        const float y = center.y + e.position.z * scale * 0.55f;
        if (x < 10 || y < 10 || x > display.x - 10 || y > display.y - 10) continue;
        const ImVec2 a(x - 22, y - 34), b(x + 22, y + 34);
        dl->AddRect(a, b, IM_COL32(80, 220, 140, 230), 2.0f, 0, 2.0f);
        if (cfg.showNames)
            dl->AddText(ImVec2(x - 35, y - 50), IM_COL32(255,255,255,255), e.name.c_str());
        if (cfg.showDistance) {
            const float d = std::sqrt(e.position.x*e.position.x + e.position.z*e.position.z);
            const std::string label = std::to_string(int(d)) + " m";
            dl->AddText(ImVec2(x - 12, y + 38), IM_COL32(230,230,230,255), label.c_str());
        }
        const float health = e.health / 100.0f;
        dl->AddRectFilled(ImVec2(x - 25, y - 38), ImVec2(x - 21, y + 38),
                          IM_COL32(40,40,40,220));
        dl->AddRectFilled(ImVec2(x - 25, y + 38 - 76*health), ImVec2(x - 21, y + 38),
                          IM_COL32(80,220,100,240));
    }
}

static void DrawRadar(const Simulation& sim, float range) {
    const ImVec2 pos(24, 24);
    const float size = 190.0f, radius = size * 0.5f;
    ImDrawList* dl = ImGui::GetForegroundDrawList();
    dl->AddRectFilled(pos, ImVec2(pos.x+size,pos.y+size), IM_COL32(12,16,24,210), 8);
    dl->AddRect(pos, ImVec2(pos.x+size,pos.y+size), IM_COL32(100,120,150,220), 8);
    const ImVec2 c(pos.x+radius,pos.y+radius);
    dl->AddCircle(c, radius-8, IM_COL32(100,120,150,160));
    dl->AddLine(ImVec2(c.x, pos.y+8), ImVec2(c.x,pos.y+size-8), IM_COL32(80,90,110,130));
    dl->AddLine(ImVec2(pos.x+8,c.y), ImVec2(pos.x+size-8,c.y), IM_COL32(80,90,110,130));
    dl->AddCircleFilled(c, 4, IM_COL32(80,180,255,255));
    for (const auto& e : sim.entities()) {
        const float nx = e.position.x / range, nz = e.position.z / range;
        if (std::abs(nx) > 1 || std::abs(nz) > 1) continue;
        const ImVec2 p(c.x + nx*(radius-14), c.y + nz*(radius-14));
        dl->AddCircleFilled(p, 4, IM_COL32(255,110,100,255));
    }
    dl->AddText(ImVec2(pos.x+8,pos.y+size+4), IM_COL32(220,220,230,255), "RADAR - SIMULACAO");
}

void DrawOverlayUI(Config& cfg, const Simulation& sim, const Diagnostics& diag,
                   bool& menuVisible, bool& running) {
    if (cfg.esp) DrawESP(sim, cfg);
    if (cfg.radar) DrawRadar(sim, cfg.radarRange);

    if (menuVisible) {
        ImGui::SetNextWindowSize(ImVec2(360, 390), ImGuiCond_FirstUseEver);
        ImGui::Begin("RobloxExternalLab | Test Harness", &menuVisible);
        ImGui::Text("Ambiente local de simulacao");
        ImGui::Separator();
        ImGui::Checkbox("ESP demonstrativo", &cfg.esp);
        ImGui::Checkbox("Radar", &cfg.radar);
        ImGui::Checkbox("Diagnostico", &cfg.diagnostics);
        ImGui::Checkbox("Nomes", &cfg.showNames);
        ImGui::Checkbox("Distancias", &cfg.showDistance);
        ImGui::SliderFloat("Alcance do radar", &cfg.radarRange, 25.0f, 200.0f, "%.0f m");
        ImGui::SliderFloat("Opacidade (janela)", &cfg.opacity, 0.2f, 1.0f);
        if (cfg.diagnostics) {
            ImGui::Separator();
            ImGui::Text("FPS: %.1f", diag.fps());
            ImGui::Text("Frame: %.2f ms", diag.frameMs());
            ImGui::Text("Entidades simuladas: %zu", sim.entities().size());
        }
        if (ImGui::Button("Salvar configuracao")) cfg.save("config/settings.json");
        ImGui::SameLine();
        if (ImGui::Button("Fechar")) running = false;
        ImGui::TextWrapped("INSERT menu | F1 ESP | F2 radar | F3 diagnostico | END sair");
        ImGui::End();
    }
}
