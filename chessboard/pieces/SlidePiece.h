//
// Created by thijs on 26-02-21.
//

#ifndef THEEMBOT_SLIDEPIECE_H
#define THEEMBOT_SLIDEPIECE_H


#include <vector>
#include "Piece.h"

class SlidePiece : public Piece {
protected:
    std::vector<int> dirs;
    std::vector<int> pseudoLegalMoves(const Board* board) const override;

public:
    SlidePiece(int pos, bool white, std::vector<int> dirs)
          : Piece(pos, white), dirs(std::move(dirs)) {};
};

#endif //THEEMBOT_SLIDEPIECE_H
