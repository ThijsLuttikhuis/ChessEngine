//
// Created by thijs on 18-02-21.
//

#ifndef THEEMBOT_KNIGHT_H
#define THEEMBOT_KNIGHT_H


#include "JumpPiece.h"

class Knight : public JumpPiece {
private:

public:
    Knight(int pos, bool white)
        : JumpPiece(pos, white, {6, 10, 15, 17, -6, -10, -15, -17}) { };

    char getChar() const override {return white ? 'N' : 'n';}

};


#endif //THEEMBOT_KNIGHT_H
