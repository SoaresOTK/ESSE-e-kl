#include "core/Config.hpp"
#include <fstream>
#include <string>

void Config::load(const std::string& path) {
    std::ifstream f(path);
    if (!f) return;
    std::string s((std::istreambuf_iterator<char>(f)), {});
    auto boolean = [&](const char* key, bool& out) {
        const std::string k = std::string("\"") + key + "\"";
        auto p = s.find(k); if (p == std::string::npos) return;
        p = s.find(':', p); if (p == std::string::npos) return;
        auto v = s.find_first_not_of(" \t\r\n", p + 1);
        if (v != std::string::npos) out = s.compare(v, 4, "true") == 0;
    };
    auto number = [&](const char* key, float& out) {
        const std::string k = std::string("\"") + key + "\"";
        auto p = s.find(k); if (p == std::string::npos) return;
        p = s.find(':', p); if (p == std::string::npos) return;
        try { out = std::stof(s.substr(p + 1)); } catch (...) {}
    };
    boolean("esp", esp); boolean("radar", radar);
    boolean("diagnostics", diagnostics); boolean("show_names", showNames);
    boolean("show_distance", showDistance);
    number("radar_range", radarRange); number("overlay_opacity", opacity);
}

void Config::save(const std::string& path) const {
    std::ofstream f(path);
    if (!f) return;
    f << "{\n"
      << "  \"esp\": " << (esp ? "true" : "false") << ",\n"
      << "  \"radar\": " << (radar ? "true" : "false") << ",\n"
      << "  \"diagnostics\": " << (diagnostics ? "true" : "false") << ",\n"
      << "  \"show_names\": " << (showNames ? "true" : "false") << ",\n"
      << "  \"show_distance\": " << (showDistance ? "true" : "false") << ",\n"
      << "  \"radar_range\": " << radarRange << ",\n"
      << "  \"overlay_opacity\": " << opacity << "\n}\n";
}
