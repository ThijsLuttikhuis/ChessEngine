//
// Created by thijs on 26-02-21.
//

#ifndef THEEMBOT_JUMPPIECE_H
#define THEEMBOT_JUMPPIECE_H


#include "../Board.h"
#include "Piece.h"

class JumpPiece : public Piece {
protected:
    std::vector<int> dirs;

    std::vector<int> pseudoLegalMoves(const Board* board) const override;

public:
    JumpPiece(int pos, bool white, std::vector<int> dirs)
          : Piece(pos, white), dirs(std::move(dirs)) {};
};


#endif //THEEMBOT_JUMPPIECE_H
