#include "game.hpp"

AmongUsGame::AmongUsGame(Tyra::Engine* t_engine)
    : engine(t_engine),
      mapTexture(nullptr),
      playerTexture(nullptr),
      minimapTexture(nullptr),
      playerX(MAP_WIDTH * 0.5f),
      playerY(MAP_HEIGHT * 0.5f),
      camX(0.0f),
      camY(0.0f),
      showMiniMap(false) {}

AmongUsGame::~AmongUsGame() {
    auto& textureRepo = engine->renderer.getTextureRepository();

    if (mapTexture != nullptr) {
        textureRepo.free(mapTexture);
        mapTexture = nullptr;
    }

    if (playerTexture != nullptr) {
        textureRepo.free(playerTexture);
        playerTexture = nullptr;
    }

    if (minimapTexture != nullptr) {
        textureRepo.free(minimapTexture);
        minimapTexture = nullptr;
    }
}

void AmongUsGame::init() {
    auto& textureRepo = engine->renderer.getTextureRepository();

    mapTexture = textureRepo.add(
        Tyra::FileUtils::fromCwd("assets/images/mapa.png"));
    playerTexture = textureRepo.add(
        Tyra::FileUtils::fromCwd("assets/images/player.png"));
    minimapTexture = textureRepo.add(
        Tyra::FileUtils::fromCwd("assets/images/minimapa.png"));

    mapTexture->addLink(mapSprite.id);
    playerTexture->addLink(playerSprite.id);
    minimapTexture->addLink(minimapSprite.id);

    mapSprite.mode = Tyra::SpriteMode::MODE_REPEAT;
    mapSprite.position.set(0.0f, 0.0f);
    mapSprite.size.set(SCREEN_WIDTH, SCREEN_HEIGHT);
    mapSprite.offset.set(0.0f, 0.0f);

    playerSprite.mode = Tyra::SpriteMode::MODE_STRETCH;
    playerSprite.size.set(PLAYER_WIDTH, PLAYER_HEIGHT);
    playerSprite.position.set(playerX, playerY);

    minimapSprite.mode = Tyra::SpriteMode::MODE_STRETCH;
    minimapSprite.size.set(SCREEN_WIDTH, 400.0f);
    minimapSprite.position.set(0.0f, 24.0f);

    engine->audio.song.inLoop = true;
    engine->audio.song.load(Tyra::FileUtils::fromCwd("assets/music/amongus.wav"));
    engine->audio.song.play();
}

void AmongUsGame::loop() {
    const float deltaSeconds = static_cast<float>(timer.getTimeDelta()) / 15625.0f;
    timer.prime();

    const float dt = (deltaSeconds > 0.0f) ? deltaSeconds : (1.0f / 60.0f);
    const float speed = 180.0f * dt;

    const auto& clicked = engine->pad.getClicked();
    const auto& pressed = engine->pad.getPressed();

    if (clicked.Square) {
        showMiniMap = !showMiniMap;
    }

    if (!showMiniMap) {
        if (pressed.DpadLeft) {
            playerX -= speed;
        }
        if (pressed.DpadRight) {
            playerX += speed;
        }
        if (pressed.DpadUp) {
            playerY -= speed;
        }
        if (pressed.DpadDown) {
            playerY += speed;
        }

        if (playerX < 0.0f) {
            playerX = 0.0f;
        }
        if (playerY < 0.0f) {
            playerY = 0.0f;
        }
        if (playerX > MAP_WIDTH - PLAYER_WIDTH) {
            playerX = MAP_WIDTH - PLAYER_WIDTH;
        }
        if (playerY > MAP_HEIGHT - PLAYER_HEIGHT) {
            playerY = MAP_HEIGHT - PLAYER_HEIGHT;
        }

        camX = playerX - (SCREEN_WIDTH * 0.5f);
        camY = playerY - (SCREEN_HEIGHT * 0.5f);

        if (camX < 0.0f) {
            camX = 0.0f;
        }
        if (camY < 0.0f) {
            camY = 0.0f;
        }
        if (camX > MAP_WIDTH - SCREEN_WIDTH) {
            camX = MAP_WIDTH - SCREEN_WIDTH;
        }
        if (camY > MAP_HEIGHT - SCREEN_HEIGHT) {
            camY = MAP_HEIGHT - SCREEN_HEIGHT;
        }
    }

    mapSprite.offset.set(camX, camY);
    playerSprite.position.set(playerX - camX, playerY - camY);

    engine->renderer.beginFrame();
    engine->renderer.renderer2D.render(&mapSprite);
    engine->renderer.renderer2D.render(&playerSprite);

    if (showMiniMap) {
        engine->renderer.renderer2D.render(&minimapSprite);
    }

    engine->renderer.endFrame();
}
