#include "../include/Game.hpp"

int main() {
    Game game;

    game.gM().setPlayerPosition("Mayor", "camp");;
    game.gM().setPlayerPosition("Archaeologist", "cave");
    game.gM().setPlayerPosition("Dracula", "dungeon");
    game.gM().setPlayerPosition("InvisibleMan", "abbey");        

    game.run();
    return 0;
}
