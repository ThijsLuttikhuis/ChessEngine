//
// Created by thijs on 18-02-21.
//

#ifndef THEEMBOT_ROOK_H
#define THEEMBOT_ROOK_H


#include "SlidePiece.h"

class Rook : public SlidePiece {
private:
public:
    explicit Rook(int pos, bool white)
        : SlidePiece(pos, white, {1, 8, -1, -8}) { };

    char getChar() const override {return white ? 'R' : 'r';}

};



#endif //THEEMBOT_ROOK_H
