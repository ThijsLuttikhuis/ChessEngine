//
// Created by thijs on 09-03-21.
//

#ifndef CHESSENGINE_ENGINE_H
#define CHESSENGINE_ENGINE_H


#include <utility>
#include "../chessboard/Board.h"

class Engine {
protected:
    bool white;

    double timeOnClock = 9e99;         // time left on the clock
    double timeIncrement = 9e99;       // increment per move in seconds
public:
    explicit Engine(bool white) : white(white) {};
    virtual ~Engine() = default;

    virtual Move move(Board* board) = 0;
};


#endif //CHESSENGINE_ENGINE_H
