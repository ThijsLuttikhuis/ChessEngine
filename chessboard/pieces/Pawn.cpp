//
// Created by thijs on 18-02-21.
//

#include "Pawn.h"
#include "../Board.h"


std::vector<int> Pawn::pseudoLegalMoves(const Board* board) const {
    std::vector<int> moves;

    auto board_ = board->getBoard();
    int direction = white ? -1 : 1;
    int doubleRank = white ? 2 : 7;

    // move 1 or 2 space(s) forwards
    int oneForward = pos + 8 * direction;
    if (!board_[oneForward]) {
        moves.push_back(oneForward);

        int twoForward = pos + 16 * direction;
        if (Board::getRank(pos) == doubleRank && !board_[twoForward]) {
            moves.push_back(twoForward);
        }
    }

    // capture diagonally
    int diagonalLeft = pos + 9 * direction;
    int diagonalRight = pos + 7 * direction;
    if (std::abs(Board::getFile(diagonalLeft) - Board::getFile(pos)) == 1 && board_[diagonalLeft] &&
        board_[diagonalLeft]->isWhite() != white) {
        moves.push_back(diagonalLeft);
    }
    if (std::abs(Board::getFile(diagonalRight) - Board::getFile(pos)) == 1 && board_[diagonalRight] &&
        board_[diagonalRight]->isWhite() != white) {
        moves.push_back(diagonalRight);
    }

    // en passant
    int enPassant = board->getEnPassant();
    if ((enPassant == diagonalLeft && std::abs(Board::getFile(diagonalLeft) - Board::getFile(pos)) == 1) ||
        (enPassant == diagonalRight && std::abs(Board::getFile(diagonalRight) - Board::getFile(pos)) == 1)) {
        moves.push_back(enPassant);
    }


    return moves;
}

void Pawn::setPos(int pos_, Board* board) {
    int direction = white ? -1 : 1;
    if (pos_ == pos + 16 * direction) {
        board->setEnPassant(pos + 8 * direction);
    }
    else {
        board->setEnPassant(-1);
    }
    pos = pos_;
}
