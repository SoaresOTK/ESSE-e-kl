#include "core/Config.hpp"
#include "engine/Simulation.hpp"
#include "diagnostics/Diagnostics.hpp"
#include "overlay/OverlayUI.hpp"

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <iostream>

#ifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <windows.h>
#endif

static bool pressed(GLFWwindow* w, int key) {
    return glfwGetKey(w, key) == GLFW_PRESS;
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Falha ao inicializar GLFW\n";
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

    GLFWwindow* window = glfwCreateWindow(1100, 720, "RobloxExternalLab - Simulation", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

#ifdef _WIN32
    HWND hwnd = glfwGetWin32Window(window);
    SetWindowPos(hwnd, HWND_TOPMOST, 80, 80, 1100, 720, SWP_SHOWWINDOW);
#endif

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    Config cfg;
    cfg.load("config/settings.json");
    Simulation sim;
    Diagnostics diag;
    bool menuVisible = true, running = true;
    bool prevInsert=false, prevF1=false, prevF2=false, prevF3=false, prevF4=false, prevF5=false;

    while (!glfwWindowShouldClose(window) && running) {
        glfwPollEvents();
        const bool ins=pressed(window,GLFW_KEY_INSERT);
        const bool f1=pressed(window,GLFW_KEY_F1), f2=pressed(window,GLFW_KEY_F2);
        const bool f3=pressed(window,GLFW_KEY_F3), f4=pressed(window,GLFW_KEY_F4);
        const bool f5=pressed(window,GLFW_KEY_F5);
        if (ins && !prevInsert) menuVisible=!menuVisible;
        if (f1 && !prevF1) cfg.esp=!cfg.esp;
        if (f2 && !prevF2) cfg.radar=!cfg.radar;
        if (f3 && !prevF3) cfg.diagnostics=!cfg.diagnostics;
        if (f4 && !prevF4) cfg.showNames=!cfg.showNames;
        if (f5 && !prevF5) cfg.showDistance=!cfg.showDistance;
        prevInsert=ins; prevF1=f1; prevF2=f2; prevF3=f3; prevF4=f4; prevF5=f5;
        if (pressed(window,GLFW_KEY_END)) running=false;

        static double last=glfwGetTime();
        const double now=glfwGetTime();
        const float dt=float(now-last); last=now;
        sim.update(dt);
        diag.tick();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        DrawOverlayUI(cfg, sim, diag, menuVisible, running);
        ImGui::Render();

        int w,h;
        glfwGetFramebufferSize(window,&w,&h);
        glViewport(0,0,w,h);
        glClearColor(0.025f,0.035f,0.055f,0.18f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    cfg.save("config/settings.json");
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
