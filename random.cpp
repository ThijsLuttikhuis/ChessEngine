//
// Created by thijs on 09-03-21.
//

#include <iostream>

#include "chessboard/Board.h"
#include "chessboard/pieces/Piece.h"
#include "engines/player/Player.h"
#include "engines/random/RandomEngine.h"

int checkMoves(const Board &board) {
    auto &pieces = board.isWhiteToMove() ? board.getWhitePieces() : board.getBlackPieces();
    for (auto piece : pieces) {
        auto moves = piece->pseudoLegalMoves(&board);
        if (!moves.empty()) return 0;
    }
    return 1;
}

int checkKings(const Board &board) {
    bool whiteKing = false;
    bool blackKing = false;
    auto &whitePieces = board.getWhitePieces();
    for (auto &piece : whitePieces) {
        if (piece->getChar() == 'K') {
            whiteKing = true;
            break;
        }
    }
    auto &blackPieces = board.getBlackPieces();
    for (auto &piece : blackPieces) {
        if (piece->getChar() == 'k') {
            blackKing = true;
            break;
        }
    }

    if (!whiteKing) return -1;
    if (!blackKing) return 1;
    return 0;
}

int main() {
    std::string fen = START_POSITION;

    Board board;
    board.setBoard(fen);
    board.printBoard();

    Engine* white = new RandomEngine(true);
    Engine* black = new RandomEngine(false);

    while (true) {
        Move move;
        if (board.isWhiteToMove()) {
            move = white->move(&board);
        } else {
            move = black->move(&board);
        }

        if (move.isExit()) {
            break;
        }

        board.move(move);
        board.printBoard();

        int kings = checkKings(board);
        if (kings == -1) {
            std::cout << "black wins!" << std::endl;
            break;
        }
        if (kings == 1) {
            std::cout << "white wins!" << std::endl;
            break;
        }
        int moves = checkMoves(board);
        if (moves == 1) {
            std::cout << "no moves, draw!" << std::endl;
            break;
        }
    }

    return 0;
}

