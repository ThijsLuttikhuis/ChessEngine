//
// Created by thijs on 09-03-21.
//

#include "RandomEngine.h"
#include "../../chessboard/pieces/Piece.h"

Move RandomEngine::move(Board* board) {

    auto &pieces = white ? board->getWhitePieces() : board->getBlackPieces();

    std::vector<int> moves;
    const Piece* piece;
    do {
        int p = rng.randri(pieces.size());
        piece = pieces[p];
        moves = piece->pseudoLegalMoves(board);
    }
    while (moves.empty());

    int q = rng.randri(moves.size());
    auto to = moves[q];
    auto from = piece->getPos();

    return Move(from, to);
}
