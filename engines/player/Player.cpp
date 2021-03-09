//
// Created by thijs on 09-03-21.
//

#include <iostream>
#include "Player.h"

Move Player::move(Board* board) {
    std::string moveIn;
    std::getline(std::cin, moveIn);
    if (moveIn == "q") {
        return Move(-27, -27);  // exit
    }
    if (moveIn == "print") {
        board->printBoard();
        return move(board);
    }

    return Board::getMoveFromString(moveIn);
}
