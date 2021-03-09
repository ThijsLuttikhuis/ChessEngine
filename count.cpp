//
// Created by thijs on 09-03-21.
//

#include <iostream>

#include "chessboard/Board.h"
#include "chessboard/pieces/Piece.h"
#include "utilities/CountLegalMoves.h"

int main() {
    std::string fen = START_POSITION;
    std::cout << fen << std::endl;

    Board board;
    board.setBoard(fen);
    board.printBoard();

    int depthLimit = 5;

    for (int depth = 1; depth <= depthLimit; depth++) {
        int moveCount = CountLegalMoves::count(&board, depth);
        std::cout << "depth: " << depth << " -> moves: " << moveCount << std::endl;
    }

    return 0;
}