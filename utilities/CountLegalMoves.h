//
// Created by thijs on 23-02-21.
//

#ifndef THEEMBOT_COUNTLEGALMOVES_H
#define THEEMBOT_COUNTLEGALMOVES_H


#include "../chessboard/Board.h"

class CountLegalMoves {
public:

    static int count(Board* board, int depth);
};


#endif //THEEMBOT_COUNTLEGALMOVES_H
