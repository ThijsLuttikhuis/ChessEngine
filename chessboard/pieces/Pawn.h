//
// Created by thijs on 18-02-21.
//

#ifndef THEEMBOT_PAWN_H
#define THEEMBOT_PAWN_H

#include "Piece.h"

class Pawn : public Piece {
private:
    int direction;
    int doubleRank;
public:
    explicit Pawn(int pos, bool white)
        : Piece(pos, white), direction(direction = white ? -1 : 1), doubleRank(white ? 7 : 2) {};

    char getChar() const override {return white ? 'P' : 'p';}

    std::vector<int> pseudoLegalMoves(const Board* board) const override;

    void setPos(int pos, Board* board) override;
};


#endif //THEEMBOT_PAWN_H
