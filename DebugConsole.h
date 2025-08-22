#pragma once

#include <imgui-SFML.h>
#include <imgui.h>

#include <string>
#include <vector>

class DebugConsole {
  public:
    enum class MessageType { INFO, WARNING, ERROR };

  private:
    struct DebugMessage {
        std::string text;
        MessageType type;
    };

    inline static std::vector<DebugMessage> messages;
    inline static const size_t              maxMessages = 100;

    inline static const ImVec4 messageColors[] = {ImVec4(1.0f, 1.0f, 1.0f, 1.0f),  // INFO (белый)
                                                  ImVec4(1.0f, 1.0f, 0.0f, 1.0f),  // WARNING (жёлтый)
                                                  ImVec4(1.0f, 0.0f, 0.0f, 1.0f)}; // ERROR (красный)

  public:
    static void log(const std::string& msg, MessageType color = MessageType::INFO) {
        if (messages.size() >= maxMessages) {
            messages.erase(messages.begin());
        }

        messages.push_back({msg, color});
    }

    static void clear() {
        messages.clear();
    }

    static void render() {
        ImGui::SetNextWindowPos(ImVec2(0, 180.f), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(500.f, 200.f), ImGuiCond_FirstUseEver);

        ImGui::Begin("Console");

        if (ImGui::Button("Clear")) {
            clear();
        }

        ImGui::BeginChild("Scrolling", ImVec2(0, 0), true);

        for (auto& msg : messages) {
            ImGui::PushStyleColor(ImGuiCol_Text, messageColors[(int)msg.type]);
            ImGui::TextUnformatted(msg.text.c_str());
            ImGui::PopStyleColor();
        }

        ImGui::EndChild();
        ImGui::End();
    }
};
