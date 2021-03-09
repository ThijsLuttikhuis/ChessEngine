//
// Created by thijs on 26-02-21.
//

#include <vector>
#include "JumpPiece.h"
#include "../Board.h"


std::vector<int> JumpPiece::pseudoLegalMoves(const Board* board) const {
    std::vector<int> moves;

    auto board_ = board->getBoard();

    for (auto &dir : dirs) {
        int newPos = pos + dir;

        if (std::abs(Board::getRank(newPos) - Board::getRank(pos)) > 2 ||
            std::abs(Board::getFile(newPos) - Board::getFile(pos)) > 2) {
            continue;
        }

        if (board_[newPos]) {
            if ((board_[newPos]->isWhite() && !white) || (!board_[newPos]->isWhite() && white)) {
                moves.push_back(newPos);
            }
        } else {
            moves.push_back(newPos);
        }
    }

    return moves;
}
