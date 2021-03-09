//
// Created by thijs on 26-02-21.
//

#include <cmath>
#include "SlidePiece.h"
#include "../Board.h"

std::vector<int> SlidePiece::pseudoLegalMoves(const Board* board) const {
    std::vector<int> moves;
    auto board_ = board->getBoard();

    for (auto &dir : dirs) {
        int newPos = pos;
        int file = Board::getFile(pos);
        int rank = Board::getRank(pos);

        while (true) {
            newPos += dir;

            int newFile = Board::getFile(newPos);
            int newRank = Board::getRank(newPos);

            if (std::abs(newFile - file) > 1 || std::abs(newRank - rank) > 1) {
                break;
            }
            if (board_[newPos]) {
                if ((board_[newPos]->isWhite() && !white) || (!board_[newPos]->isWhite() && white)) {
                    moves.push_back(newPos);
                }
                break;
            }

            file = newFile;
            rank = newRank;

            moves.push_back(newPos);
        }
    }
    return moves;

}