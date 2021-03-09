//
// Created by thijs on 18-02-21.
//

#ifndef THEEMBOT_PIECE_H
#define THEEMBOT_PIECE_H


#include <utility>
#include <vector>

class Board;

class Piece {
protected:
    bool white;
    int pos;
public:
    Piece(int pos, bool white) : pos(pos), white(white) {};

    virtual ~Piece() = default;

    virtual void setPos(int pos, Board* board);

    bool isWhite() const;

    virtual char getChar() const = 0;

    int getPos() const;

    virtual std::vector<int> pseudoLegalMoves(const Board* board) const = 0;
};


#endif //THEEMBOT_PIECE_H
