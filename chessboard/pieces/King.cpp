//
// Created by thijs on 18-02-21.
//

#include "King.h"
#include "../Board.h"

std::vector<int> King::pseudoLegalMoves(const Board* board) const {
    std::vector<int> moves = JumpPiece::pseudoLegalMoves(board);

    //TODO: implement castling
    return moves;
}
