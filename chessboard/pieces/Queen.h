//
// Created by thijs on 18-02-21.
//

#ifndef THEEMBOT_QUEEN_H
#define THEEMBOT_QUEEN_H


#include "SlidePiece.h"

class Queen : public SlidePiece {
private:

public:
    explicit Queen(int pos, bool white)
        : SlidePiece(pos, white, {1, 7, 8, 9, -1, -7, -8, -9}) {};

    char getChar() const override {return white ? 'Q' : 'q';}

};


#endif //THEEMBOT_QUEEN_H
