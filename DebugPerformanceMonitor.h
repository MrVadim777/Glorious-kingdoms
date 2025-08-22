#pragma once

class DebugPerformanceMonitor {
  private:
    struct TPS {
        int   tickCount = 0;
        float tickTimer = 0.f;
        float tpsCount  = 0.f;
    };
    struct FPS {
        int   frameCount = 0;
        float frameTimer = 0.f;
        float fpsCount   = 0.f;
    };

    TPS tps;
    FPS fps;

  public:
    void updateTPS(const sf::Time& deltaTime) {
        tps.tickCount++;
        tps.tickTimer += deltaTime.asSeconds();

        if (tps.tickTimer >= 1.0f) {
            tps.tpsCount  = static_cast<float>(tps.tickCount);
            tps.tickCount = 0;
            tps.tickTimer -= 1.0f;
        }
    }

    void updateFPS(const sf::Time& deltaTime) {
        fps.frameCount++;
        fps.frameTimer += deltaTime.asSeconds();

        if (fps.frameTimer >= 1.0f) {
            fps.fpsCount   = static_cast<float>(fps.frameCount);
            fps.frameCount = 0;
            fps.frameTimer -= 1.0f;
        }
    }

    float getTPS() const {
        return tps.tpsCount;
    }

    float getFPS() const {
        return fps.fpsCount;
    }
};