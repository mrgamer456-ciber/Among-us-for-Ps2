#include "game.hpp"

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    Tyra::EngineOptions options;
    options.writeLogsToFile = false;
    options.loadUsbDriver = false;

    Tyra::Engine engine(options);
    AmongUsGame game(&engine);

    engine.run(&game);
    return 0;
}
