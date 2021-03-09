//
// Created by thijs on 18-02-21.
//

#ifndef THEEMBOT_BISHOP_H
#define THEEMBOT_BISHOP_H


#include "SlidePiece.h"

class Bishop : public SlidePiece {
private:

public:
    explicit Bishop(int pos, bool white)
        : SlidePiece(pos, white, {7, 9, -7, -9}) { };

    char getChar() const override {return white ? 'B' : 'b';}

};



#endif //THEEMBOT_BISHOP_H
