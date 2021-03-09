//
// Created by thijs on 18-02-21.
//

#ifndef THEEMBOT_KING_H
#define THEEMBOT_KING_H


#include "JumpPiece.h"

class King : public JumpPiece {
private:

public:
    explicit King(int pos, bool white)
        : JumpPiece(pos, white, {1, 7, 8, 9, -1, -7, -8, -9}) { };

    std::vector<int> pseudoLegalMoves(const Board* board) const override;

    char getChar() const override {return white ? 'K' : 'k';}

};



#endif //THEEMBOT_KING_H
