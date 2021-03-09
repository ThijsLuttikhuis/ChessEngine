//
// Created by thijs on 18-02-21.
//

#include "Piece.h"
#include "../Board.h"

bool Piece::isWhite() const {
    return white;
}

int Piece::getPos() const {
    return pos;
}

void Piece::setPos(int pos_, Board* board) {
    pos = pos_;
    board->setEnPassant(-1);
}



