//
// Created by thijs on 18-02-21.
//

#include <iostream>
#include "Board.h"
#include "pieces/Pawn.h"
#include "pieces/Knight.h"
#include "pieces/Bishop.h"
#include "pieces/Queen.h"
#include "pieces/Rook.h"
#include "pieces/King.h"

Board::Board(const std::string &fen) {
    setBoard(fen);
}

Piece* Board::charToPiece(char c, int pos) {
    Piece* piece = nullptr;
    if (c == 'p') {
        piece = new Pawn(pos, false);
    } else if (c == 'P') {
        piece = new Pawn(pos, true);
    } else if (c == 'n') {
        piece = new Knight(pos, false);
    } else if (c == 'N') {
        piece = new Knight(pos, true);
    } else if (c == 'b') {
        piece = new Bishop(pos, false);
    } else if (c == 'B') {
        piece = new Bishop(pos, true);
    } else if (c == 'r') {
        piece = new Rook(pos, false);
    } else if (c == 'R') {
        piece = new Rook(pos, true);
    } else if (c == 'q') {
        piece = new Queen(pos, false);
    } else if (c == 'Q') {
        piece = new Queen(pos, true);
    } else if (c == 'k') {
        piece = new King(pos, false);
    } else if (c == 'K') {
        piece = new King(pos, true);
    }
    return piece;
}


void Board::setBoard(const std::string &fen) {
    fenAtCreation = fen;
    unsigned long index = 0;
    bool success;

    success = setPieces(fen, index);
    if (!success) return;

    success = setWhiteToMove(fen, index);
    if (!success) return;

    success = setCastle(fen, index);
    if (!success) return;

    success = setEnPassant(fen, index);
    if (!success) return;

    success = setMovesWithoutCaptures(fen, index);
    if (!success) return;

    success = setMoves(fen, index);
    if (!success) return;

    if (index != fen.size() + 1) {
        std::cerr << "setBoard(): invalid fen (stringSize)" << std::endl;
        return;
    }
}

bool Board::setPieces(const std::string &fen, unsigned long &index) {
    int pos = 0;
    for (; index < fen.size(); index++) {
        auto &f = fen[index];

        if (f - '0' > 0 && f - '0' < 9) {
            pos += f - '0';
        } else if (f == '/') {
            if (pos % 8 != 0) {
                std::cerr << "setPieces(): invalid fen (/)" << std::endl;
                return false;
            }
        } else if (f == ' ') {
            if (pos != 64) {
                std::cerr << "setPieces(): invalid fen (board)" << std::endl;
                return false;
            }
            index++;
            return true;
        } else {
            auto* piece = charToPiece(f, pos);
            if (piece) {
                piece->isWhite() ? whitePieces.emplace_back(piece) : blackPieces.emplace_back(piece);
                board[pos++] = piece;
            } else {
                std::cerr << "setPieces(): invalid fen (piece)" << std::endl;
                return false;
            }
        }
    }
    std::cerr << "setPieces(): invalid fen (endOfString)" << std::endl;

    return false;
}

bool Board::setWhiteToMove(const std::string &fen, unsigned long &index) {
    if (fen[index] == 'w') {
        whiteToMove = true;
        index += 2;
        return true;
    }
    if (fen[index] == 'b') {
        whiteToMove = false;
        index += 2;
        return true;
    }
    std::cerr << "setWhiteToMove(): invalid fen" << std::endl;
    return false;
}

bool Board::setCastle(const std::string &fen, unsigned long &index) {
    castle = 0;
    if (fen[index] != '-') {
        if (fen[index] == 'K') {
            castle |= CASTLE_WHITE_K;
            index++;
        }
        if (fen[index] == 'Q') {
            castle |= CASTLE_WHITE_Q;
            index++;
        }
        if (fen[index] == 'k') {
            castle |= CASTLE_BLACK_K;
            index++;
        }
        if (fen[index] == 'q') {
            castle |= CASTLE_BLACK_Q;
            index++;
        }
        if (fen[index] != ' ') {
            std::cerr << "setCastle(): invalid fen" << std::endl;
            return false;
        }
        index++;
    } else {
        index += 2;
    }
    return true;
}

bool Board::setEnPassant(const std::string &fen, unsigned long &index) {
    if (fen[index] != '-') {
        enPassant = getPositionFromString(fen, index);
    } else {
        index++;
    }
    index++;
    return true;
}

bool Board::setMoves(const std::string &fen, unsigned long &index) {
    moveCount = getUintFromString(fen, index);
    index++;
    return true;
}

bool Board::setMovesWithoutCaptures(const std::string &fen, unsigned long &index) {
    movesWithoutCaptures = getUintFromString(fen, index);
    index++;
    return true;
}

unsigned int Board::getUintFromString(const std::string &str, unsigned long &index) {
    unsigned int num = 0;
    while (index < str.size() && str[index] != ' ') {
        auto s = str[index++] - '0';
        num = num * 10 + s;
    }
    return num;
}

int Board::getPositionFromString(const std::string &posStr, unsigned long &index) {
    int x = posStr[index++] - 'a';
    int y = posStr[index++] - '0';
    int pos = x + 8 * (8 - y);
    if (pos < 0 || pos >= 64) {
        std::cerr << "getPositionFromString(): invalid position" << std::endl;
        return -1;
    }
    return pos;
}

int Board::getPositionFromRankFile(int rank, int file) {
    int pos = 63 + file;
    pos -= 8 * rank;
    return pos;
}

Move Board::getMoveFromString(const std::string &moveStr) {
    unsigned long index = 0;
    int p1 = getPositionFromString(moveStr, index);
    while (moveStr[index] == ' ') {
        index++;
    }

    int p2 = getPositionFromString(moveStr, index);
    if (index != moveStr.size()) {
        std::cerr << "getMoveFromString(): invalid move string" << std::endl;
        return Move(-1, -1);
    }
    return Move(p1, p2);
}

void Board::printBoard() {
    int i = 0;
    std::cout << " ---------------------------------" << std::endl;
    for (auto &piece : board) {
        if (piece) {
            std::cout << " | " << piece->getChar();
        } else {
            std::cout << " |  ";
        }

        if (++i > 7) {
            i = 0;
            std::cout << " |\n ---------------------------------" << std::endl;
        }
    }
}
Piece* Board::move(int from, int to) {
    Move m(from, to);
    return move(m);
}

Piece* Board::move(Move m) {
    updateCheck();

    if (m.from == -1 || m.to == -1) {
        std::cerr << "" << std::endl;
        return nullptr;
    }
    auto &fromPiece = board[m.from];
    if (fromPiece) {
        // check if piece is the right color
        if ((whiteToMove && fromPiece->isWhite()) || (!whiteToMove && !fromPiece->isWhite())) {

            auto legalMoves = fromPiece->pseudoLegalMoves(this);

            // check if it is a legal move
            for (auto legalMove : legalMoves) {
                if (m.to == legalMove) {
                    return forceMove(fromPiece, m.to);
                }
            }
            std::cerr << "move(): that is not a legal move!" << std::endl;
            return nullptr;
        } else {
            std::cerr << "move(): that is not your piece!" << std::endl;
            return nullptr;
        }
    } else {
        std::cerr << "move(): there is no piece there!" << std::endl;
        return nullptr;
    }
}

const std::vector<Piece*> &Board::getWhitePieces() const {
    return whitePieces;
}

const std::vector<Piece*> &Board::getBlackPieces() const {
    return blackPieces;
}

const std::vector<Piece*> &Board::getBoard() const {
    return board;
}

std::vector<Piece*> &Board::getEditableBoard() {
    return board;
}

int Board::getFile(int pos) {
    if (pos < 0 || pos >= 64) return 255;
    return (pos % 8) + 1;
}

int Board::getRank(int pos) {
    if (pos < 0 || pos >= 64) return 255;
    return 8 - pos / 8;
}

bool Board::isWhiteToMove() const {
    return whiteToMove;
}

int Board::getEnPassant() const {
    return enPassant;
}

unsigned int Board::getCastle() const {
    return castle;
}

unsigned int Board::getMovesWithoutCaptures() const {
    return movesWithoutCaptures;
}

unsigned int Board::getMoves() const {
    return moveCount;
}

void Board::removeWhitePiece(const Piece* piece) {
    for (auto it = whitePieces.begin(); it != whitePieces.end(); it++) {
        if (*it == piece) {
            whitePieces.erase(it);
            return;
        }
    }
    std::cerr << "removeWhitePiece(): piece does not exist" << std::endl;
}

void Board::removeBlackPiece(const Piece* piece) {
    for (auto it = blackPieces.begin(); it != blackPieces.end(); it++) {
        if (*it == piece) {
            blackPieces.erase(it);
            return;
        }
    }
    std::cerr << "removeBlackPiece():piece does not exist" << std::endl;
}

void Board::setEnPassant(int enPassant_) {
    enPassant = enPassant_;
}

void Board::setCastle(unsigned int castle_) {
    castle = castle_;
}

Board Board::deepCopy() {
    Board copy;

    const std::string &fen = createFEN();
    copy.setBoard(fen);

    return copy;
}

std::string Board::createFEN() const {
    std::string fen;

    for (int i = 0; i < 8; i++) {
        char noPiece = '0';
        for (int j = 0; j < 8; j++) {
            auto* piece = board[i * 8 + j];
            if (piece) {
                if (noPiece > '0') {
                    fen.push_back(noPiece);
                }

                char c = piece->getChar();
                fen.push_back(c);
                noPiece = '0';
            } else {
                noPiece++;
            }
        }
        if (noPiece > '0') {
            fen.push_back(noPiece);
        }
        if (i != 7) fen.push_back('/');
    }

    fen += whiteToMove ? " w " : " b ";
    if (CASTLE_WHITE_K & castle) fen.push_back('K');
    if (CASTLE_WHITE_Q & castle) fen.push_back('Q');
    if (CASTLE_BLACK_K & castle) fen.push_back('k');
    if (CASTLE_BLACK_Q & castle) fen.push_back('q');
    if (enPassant == -1) fen += " - ";
    else {
        fen += ' ';
        fen.push_back(getFile(enPassant) + 'a' - 1);
        fen.push_back(getRank(enPassant) + '0');
        fen += ' ';
    }
    std::string mwc = std::to_string(movesWithoutCaptures);
    std::string m = std::to_string(moveCount);
    fen += mwc + ' ' + m;

    return fen;
}

Piece* Board::forceMove(Piece* &fromPiece, int to) {
    auto &toPiece = board[to];
    Piece* capturedPiece = nullptr;
    // delete captured piece
    if (toPiece) {
        whiteToMove ? removeBlackPiece(toPiece) : removeWhitePiece(toPiece);
        capturedPieces.emplace_back(toPiece);
        capturedPiece = toPiece;
    } else if (to == enPassant && (fromPiece->getChar() == 'p' || fromPiece->getChar() == 'P')) {
        int toEnPassant = enPassant + (whiteToMove ? 8 : -8);
        auto &toPieceEnPassant = board[toEnPassant];

        whiteToMove ? removeBlackPiece(toPieceEnPassant) : removeWhitePiece(toPieceEnPassant);
        capturedPieces.emplace_back(toPieceEnPassant);
        capturedPiece = toPieceEnPassant;
    }

    // move piece
    toPiece = fromPiece;
    toPiece->setPos(to, this);

    fromPiece = nullptr;

    whiteToMove = !whiteToMove;

    return capturedPiece;
}

Piece* Board::forceMove(int from, int to) {
    auto &toPiece = board[to];
    auto &fromPiece = board[from];

    Piece* capturedPiece = nullptr;
    // delete captured piece
    if (toPiece) {
        whiteToMove ? removeBlackPiece(toPiece) : removeWhitePiece(toPiece);
        capturedPieces.emplace_back(toPiece);
        capturedPiece = toPiece;
    } else if (to == enPassant && (fromPiece->getChar() == 'p' || fromPiece->getChar() == 'P')) {
        int toEnPassant = enPassant + (whiteToMove ? 8 : -8);
        auto &toPieceEnPassant = board[toEnPassant];

        whiteToMove ? removeBlackPiece(toPieceEnPassant) : removeWhitePiece(toPieceEnPassant);
        capturedPieces.emplace_back(toPieceEnPassant);
        capturedPiece = toPieceEnPassant;
    }

    // move piece
    toPiece = fromPiece;
    toPiece->setPos(to, this);

    fromPiece = nullptr;

    whiteToMove = !whiteToMove;

    return capturedPiece;
}
bool Board::updateCheck() {
    setKingDanger();

    return false;

}

void Board::setKingDanger() {
    kingDanger.reset();
    Piece* king = nullptr;
    char kingChar = whiteToMove ? 'K' : 'k';
    for (auto &piece : board) {
        if (piece && piece->getChar() == kingChar) {
            king = piece;
            piece = nullptr;
        }
    }
    if (!king) {
        std::cerr << "setKingDanger(): king does not exist!" << std::endl;
        return;
    }

    auto &pieces = whiteToMove ? blackPieces : whitePieces;
    for (auto* piece : pieces) {
        auto moves = piece->pseudoLegalMoves(this);
        for (auto &move : moves) {
            kingDanger[move] = true;
        }
    }
    //printBitBoard(kingDanger);
    board[king->getPos()] = king;

}

void Board::forceSetWhiteToMove(bool whiteToMove_) {
    whiteToMove = whiteToMove_;
}

std::vector<Piece*> &Board::getEditableWhitePieces() {
    return whitePieces;
}

std::vector<Piece*> &Board::getEditableBlackPieces() {
    return blackPieces;
}

const std::vector<Piece*> &Board::getCapturedPieces() const {
    return capturedPieces;
}

std::vector<Piece*> &Board::getEditableCapturedPieces() {
    return capturedPieces;
}

void Board::printBitBoard(std::bitset<64> bitBoard) {
    int i = 0;
    std::cout << " ---------------------------------" << std::endl;
    for (int j = 0; j < 64; j++) {
        if (bitBoard[j]) {
            std::cout << " | x";
        } else {
            std::cout << " |  ";
        }

        if (++i > 7) {
            i = 0;
            std::cout << " |\n ---------------------------------" << std::endl;
        }
    }
    std::cout << std::endl;
}



