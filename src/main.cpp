#include "Game.hpp"
#include <iostream> 

int main() {
    try {
        Game game;
        game.Run();
    } 
    catch (const std::exception& e) {
        std::cerr << "\n!!! OH NOOO GAME CRASHED !!!\n" 
                  << "REASON: " << e.what() << "\n" << std::endl;
        
        std::cout << "Press Enter to close the window." << std::endl;
        std::cin.get(); 
        
        return 1;
    }

    return 0;
}