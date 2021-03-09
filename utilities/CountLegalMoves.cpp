//
// Created by thijs on 23-02-21.
//

#include <iostream>
#include "CountLegalMoves.h"
#include "../chessboard/pieces/Piece.h"

int CountLegalMoves::count(Board* board, int depth) {
    int moveCount = 0;
    auto fen = board->createFEN();

//                Board newBoard = board->deepCopy();
//                newBoard.move(piece->getPos(), move);
//                moveCount += count(&newBoard, depth - 1);

    bool whiteToMove = board->isWhiteToMove();
    auto &pieces = whiteToMove ? board->getEditableWhitePieces() : board->getEditableBlackPieces();
    auto &opponentPieces = !whiteToMove ? board->getEditableWhitePieces() : board->getEditableBlackPieces();

    auto &capturedPieces = board->getEditableCapturedPieces();

    auto &editableBoard = board->getEditableBoard();
    //board->updateCheck();
    for (auto* piece : pieces) {

        int from = piece->getPos();


        auto moves = piece->pseudoLegalMoves(board);
        if (depth <= 1) {
            moveCount += moves.size();
        } else {
            for (auto &to : moves) {
                // move
                Piece* capturedPiece = board->forceMove(from, to);

                moveCount += count(board, depth - 1);

                // undo move
                board->forceMove(to, from);
                if (capturedPiece) {
                    opponentPieces.emplace_back(capturedPiece);
                    capturedPieces.erase(capturedPieces.end()-1, capturedPieces.end());

                    board->forceMove(capturedPiece, capturedPiece->getPos());
                    //TODO: En Passant?
                }
                board->forceSetWhiteToMove(whiteToMove);
            }
        }
    }

    return moveCount;
}
