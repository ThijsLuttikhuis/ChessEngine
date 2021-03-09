//
// Created by thijs on 18-02-21.
//

#ifndef THEEMBOT_BOARD_H
#define THEEMBOT_BOARD_H


#include <string>
#include <vector>
#include <bitset>

#define START_POSITION "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

#define CASTLE_WHITE_K 0b0010u
#define CASTLE_WHITE_Q 0b0001u
#define CASTLE_BLACK_K 0b1000u
#define CASTLE_BLACK_Q 0b0100u

class Piece;

class Move {
public:
    explicit Move(int from = -1, int to = -1) : from(from), to(to) { }

    int from;
    int to;

    bool operator==(Move &other) {
        return this->from == other.from && this->to == other.to;
    }
    bool isExit() const {
        return from == -27 && to == -27;
    }
    void setExit() {
        from = -27;
        to = -27;
    }
};

class Board {
private:
    std::bitset<64> kingDanger = {0};

    std::vector<Piece*> whitePieces;
    std::vector<Piece*> blackPieces;
    std::vector<Piece*> capturedPieces;

    //int intboard[64];
    std::vector<Piece*> board = std::vector<Piece*>(64, nullptr);

    bool whiteToMove = true;

private:
    int enPassant = -1;
    unsigned int castle = 0;
    unsigned int movesWithoutCaptures = 0;
    unsigned int moveCount = 0;
    std::string fenAtCreation;

    static int getPositionFromString(const std::string &posStr, unsigned long &index);

    static unsigned int getUintFromString(const std::string &str, unsigned long &index);

    static Piece* charToPiece(char c, int pos);

    bool setPieces(const std::string &fen, unsigned long &index);

    bool setWhiteToMove(const std::string &fen, unsigned long &index);

    bool setCastle(const std::string &fen, unsigned long &index);

    bool setMoves(const std::string &fen, unsigned long &index);

    bool setEnPassant(const std::string &fen, unsigned long &index);

    bool setMovesWithoutCaptures(const std::string &fen, unsigned long &index);

    static void printBitBoard(std::bitset<64> bitBoard);
public:
    Board() = default;

    Board deepCopy();

    explicit Board(const std::string &fen);

    static Move getMoveFromString(const std::string &moveStr);

    static int getPositionFromRankFile(int rank, int file);

    static int getRank(int pos);

    static int getFile(int pos);

    const std::vector<Piece*> &getWhitePieces() const;
    std::vector<Piece*> &getEditableWhitePieces();

    const std::vector<Piece*> &getBlackPieces() const;
    std::vector<Piece*> &getEditableBlackPieces();

    const std::vector<Piece*> &getCapturedPieces() const;
    std::vector<Piece*> &getEditableCapturedPieces();

    const std::vector<Piece*> &getBoard() const;
    std::vector<Piece*> &getEditableBoard();

    bool isWhiteToMove() const;

    int getEnPassant() const;

    unsigned int getCastle() const;

    unsigned int getMovesWithoutCaptures() const;

    unsigned int getMoves() const;

    void setEnPassant(int enPassant);

    void setCastle(unsigned int castle);

    void printBoard();

    void setBoard(const std::string &fen);

    Piece* move(int from, int to);
    Piece* move(Move m);

    Piece* forceMove(Piece* &from, int to);
    Piece* forceMove(int from, int to);

    void removeWhitePiece(const Piece* pPiece);

    void removeBlackPiece(const Piece* pPiece);

    std::string createFEN() const;

    bool updateCheck();
    void forceSetWhiteToMove(bool whiteToMove);


    void setKingDanger();
};


#endif //THEEMBOT_BOARD_H
