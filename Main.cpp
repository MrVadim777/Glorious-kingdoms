#include "Engine.h"

int main() {
    Engine engine;

    engine.initialization();
    engine.update();

    ImGui::SFML::Shutdown();

    return 0;
}
