#pragma once

#include <tyra>

class AmongUsGame : public Tyra::Game {
 public:
    explicit AmongUsGame(Tyra::Engine* t_engine);
    ~AmongUsGame();

    void init() override;
    void loop() override;

 private:
    static constexpr float SCREEN_WIDTH = 640.0f;
    static constexpr float SCREEN_HEIGHT = 448.0f;
    static constexpr float MAP_WIDTH = 2048.0f;
    static constexpr float MAP_HEIGHT = 1024.0f;
    static constexpr float PLAYER_WIDTH = 32.0f;
    static constexpr float PLAYER_HEIGHT = 48.0f;

    Tyra::Engine* engine = nullptr;
    Tyra::Timer timer;

    Tyra::Texture* mapTexture = nullptr;
    Tyra::Texture* playerTexture = nullptr;
    Tyra::Texture* minimapTexture = nullptr;

    Tyra::Sprite mapSprite;
    Tyra::Sprite playerSprite;
    Tyra::Sprite minimapSprite;

    float playerX = MAP_WIDTH * 0.5f;
    float playerY = MAP_HEIGHT * 0.5f;
    float camX = 0.0f;
    float camY = 0.0f;

    bool showMiniMap = false;
};
