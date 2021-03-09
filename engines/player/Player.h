//
// Created by thijs on 09-03-21.
//

#ifndef CHESSENGINE_PLAYER_H
#define CHESSENGINE_PLAYER_H

#include "../Engine.h"

class Player : public Engine {
public:
    explicit Player(bool white) : Engine(white) {};

    Move move(Board* board) override;

};


#endif //CHESSENGINE_PLAYER_H
